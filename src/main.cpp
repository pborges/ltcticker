#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <ArduinoOTA.h>
#include <Hash.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


const char *WIFI_NETWORK = "*****";
const char *WIFI_PASSWORD = "*****";

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



ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

StaticJsonBuffer<512> jsonBuffer;

char buff[128];

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

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

    Serial.begin(115200);

    WiFiMulti.addAP(WIFI_NETWORK, WIFI_PASSWORD);

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

    ArduinoOTA.onStart([]() {
        Serial.println("Start updating ");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
}

void loop() {
    ArduinoOTA.handle();
    webSocket.loop();
}