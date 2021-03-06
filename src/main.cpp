#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <Button.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

//TTGO 0.91s OLED connection:
//SDA -- D4
//SCL -- D5
//RST -- D2

/*
 SDA = 2;
 SCL = 14;
 D0   = 16;
 D1   = 5;
 D2   = 4;
 D3   = 0;
 D6   = 12;
 D7   = 13;
 D8   = 15;
 RX   = 3;
 TX   = 1;
*/

ESP8266WebServer httpServer(80);
ESP8266WiFiMulti WiFiMulti;
WiFiManager wifiManager;

WebSocketsClient webSocket;
StaticJsonBuffer<512> jsonBuffer;

char buff[128];
char httpBuff[4096];
const char *host = "crypto_tracker";
const char *title = "Crypto Tracker v1.2";

double prices[3];

int crypto = 0;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED: {
            jsonBuffer.clear();
            JsonObject &jsonObject = jsonBuffer.createObject();
            jsonObject["type"] = "subscribe";
            JsonArray &sub = jsonObject.createNestedArray("product_ids");
            switch (crypto) {
                case 0:
                    sub.add("LTC-USD");
                    break;
                case 1:
                    sub.add("BTC-USD");
                    break;
                case 2:
                    sub.add("ETH-USD");
                    break;
            }
            jsonObject.createNestedArray("channels").add("matches");

            Serial.printf("[WSc] Connected to url: %s\n", payload);
            jsonObject.printTo(Serial);
            size_t l = jsonObject.printTo(buff, 128);
            webSocket.sendTXT(buff, l);
        }
            break;
        case WStype_TEXT:
            jsonBuffer.clear();
            JsonObject &jsonObject = jsonBuffer.parseObject(payload);

            if (jsonObject.success()) {

                Serial.print("[WSC] : ");
                jsonObject.printTo(Serial);
                Serial.println();
                if (strncmp("match", jsonObject["type"], 5) == 0) {
                    switch (crypto) {
                        case 0:
                            strcpy(buff, "Litecoin");
                            prices[0] = jsonObject["price"];
                            break;
                        case 1:
                            strcpy(buff, "Bitcoin");
                            prices[1] = jsonObject["price"];
                            break;
                        case 2:
                            strcpy(buff, "Ethereum");
                            prices[2] = jsonObject["price"];
                            break;
                    }

                    display.clearDisplay();
                    display.setTextSize(1);
                    display.setTextColor(WHITE);
                    display.setCursor(0, 0);
                    display.print(buff);

                    dtostrf(prices[crypto], 10, 2, buff);
                    display.setTextSize(2);
                    display.setTextColor(WHITE);
                    display.setCursor(0, 15);
                    display.print(buff);
                    display.display();
                }

            } else {
                Serial.println("json error");
            }
            break;
    }
}

void track() {
    webSocket.beginSSL("ws-feed.gdax.com", 443, "/");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
}

void handleRoot() {
    sprintf(httpBuff,
            "%s<br><a href=\"/ltc\">LTC</a><br><a href=\"/btc\">BTC</a><br><a href=\"/eth\">ETH</a>\0",
            title);
    httpServer.send(200, "text/html", httpBuff);
}

void handleReset() {
    wifiManager.resetSettings();
    httpServer.send(200, "text/text", "OK please reboot");
}

void handleLtc() {
    crypto = 0;
    webSocket.disconnect();
    track();
    httpServer.send(200, "text/text", "Tracker set to LTC");
}

void handleBtc() {
    crypto = 1;
    webSocket.disconnect();
    track();
    httpServer.send(200, "text/text", "Tracker set to BTC");
}

void handleEth() {
    crypto = 2;
    webSocket.disconnect();
    track();
    httpServer.send(200, "text/text", "Tracker set to ETH");
}


void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(title);
    display.display();

    pinMode(D3, INPUT);

    Serial.begin(115200);

    wifiManager.autoConnect(host);

    MDNS.begin(host);

    httpServer.on("/", handleRoot);
    httpServer.on("/ltc", handleLtc);
    httpServer.on("/btc", handleBtc);
    httpServer.on("/eth", handleEth);
    httpServer.on("/reset", handleReset);
    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
    Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);

    httpServer.begin();

    MDNS.addService("http", "tcp", 80);

    //WiFi.disconnect();
    while (WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }
    Serial.println(WiFi.localIP());

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(WiFi.localIP());
    display.display();

    track();
}

void loop() {
    httpServer.handleClient();
    webSocket.loop();
}