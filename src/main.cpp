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
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiManager.h>

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
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WiFiMulti WiFiMulti;
WiFiManager wifiManager;

WebSocketsClient webSocket;
StaticJsonBuffer<512> jsonBuffer;

char buff[128];
char httpBuff[128];
const char *host = "ltc_ticker";

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED: {
            jsonBuffer.clear();
            JsonObject &jsonObject = jsonBuffer.createObject();
            jsonObject["type"] = "subscribe";
            jsonObject.createNestedArray("product_ids").add("LTC-USD");
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
//            Serial.printf("[WSc] get text: %s\n", payload);
            if (jsonObject.success()) {
                strcpy(buff, "LTC: ");
                double price = jsonObject["price"];
                dtostrf(price, 5, 2, buff + 5);
                display.clearDisplay();
                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(5, 10);
                display.print(buff);
                display.display();
            } else {
                Serial.println("json error");
            }
            break;
    }
}

void handleRoot() {
    sprintf(httpBuff, "LTC tracker v1.0<br><a href=\"http://%s.local/update\">upload firmware</a>\0", host);
    httpServer.send(200, "text/html", httpBuff);
}

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("LTC Ticker");
    display.display();


    Serial.begin(115200);

    wifiManager.autoConnect(host);

    MDNS.begin(host);

    httpUpdater.setup(&httpServer);
    httpServer.on("/", handleRoot);
    httpServer.begin();

    MDNS.addService("http", "tcp", 80);
    Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);

    httpUpdater.setup(&httpServer);
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

    webSocket.beginSSL("ws-feed.gdax.com", 443, "/");
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(5000);
}

void loop() {
    httpServer.handleClient();
    webSocket.loop();
}