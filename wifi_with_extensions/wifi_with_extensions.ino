#include "SoftwareSerial.h"
#include <Regexp.h>

SoftwareSerial esp(10, 11);  // RX, TX

String uri = "/bin.json";
String port = "80";
String data;

String temp, hum;
void setup() {
  Serial.println("Inicializando...");

  Serial.begin(9600);
  esp.begin(9600);

  connect_to_wifi();
}
MatchState ms;

void loop() {
  Serial.println("Starting loop!");

  //String host = "eogg0iqtwmn3wfn.m.pipedream.net";
  //String host = "api.notifications.codelitt.dev";
  //data = "{\"temperature\"=\"12\", \"humidity\"=\"30\"}";
  String host = "0946-2804-14c-bba4-8b74-48d1-ee4-4d7c-85b1.ngrok-free.app";
  //String response = post(host, data);
  String response = get(host);

  Serial.println("-------------- RESPONSE --------------");
  Serial.println(response);
  Serial.println("-------------- RESPONSE --------------");

  ms.Target(response.c_str());

  char result = ms.Match("{.*}");

  if (result > 0) {
    Serial.print("Found match at: ");
    Serial.println(ms.MatchStart);  // 16 in this case
    Serial.print("Match length: ");
    Serial.println(ms.MatchLength);  // 3 in this case
    char jsonChar[ms.MatchLength] = "";
    int a = 0;
    for (int i = ms.MatchStart; i < ms.MatchLength; i++) {
      jsonChar[a] = response[i];
          Serial.println("Json char: " + jsonChar[a]);

      a++;
    }
    Serial.println("-------------- POTAAATO --------------");
    Serial.println(jsonChar);
    Serial.println("-------------- POTAAATO --------------");
  } else Serial.println("No match.");
  // String result = ms.Match ("a", 0);
  delay(5000);
}


void sendCommand(String cmd) {
  esp.println(cmd);
}