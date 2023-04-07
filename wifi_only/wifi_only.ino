#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h> 
#include <WiFiClient.h> 

const char *host = "appname.herokuapp.com";
const char* serverName = "https://appname.herokuapp.com";
const char* ssid = "vaka_viking_2g"; 
const char* password = "batataquente";

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if(WiFi.status()== WL_CONNECTED) {
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setInsecure();
     
      HTTPClient https;

      DynamicJsonDocument doc(512);
      JsonObject object = doc.to<JsonObject>();
      object["temperature"] = 30;
      String data;
      serializeJsonPretty(object, data);

      Serial.println(data);

      https.addHeader("Accept:", "application/json");
      https.addHeader("Host:", host);

      if (https.begin(*client, serverName)) {
          Serial.print("[HTTPS] POST...\n");
          int httpCode = https.POST(data);

          if (httpCode > 0) {
            Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
            
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
              String payload = https.getString();
              Serial.println(payload);

            } else {
              Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
            }

          } else  {
            Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
          }
          https.end();

    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    } 
  }
  delay(5000);
}