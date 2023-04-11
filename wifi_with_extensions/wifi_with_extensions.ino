#include "SoftwareSerial.h"
#include <Regexp.h>

SoftwareSerial esp(10, 11);  // RX, TX

String resposta = "";
String host = "kaio-calendar.herokuapp.com";
String uri = "/kaio/isinmeeting";
int port = 80;
MatchState ms;
int status;



void setup() {

  Serial.begin(9600);
  esp.begin(9600);

  Serial.println("Inicializando...");

  setupLED();

  connect_to_wifi();
}

void loop() {
  blink();

  Serial.println("Starting loop!");
  get();
  Serial.println("------------ Response ------------");
  Serial.println(resposta);
  Serial.println("-----------/ Response ------------");

  ms.Target(resposta.c_str());
  char matchResult = ms.Match("HTTP\/1.1(%s%d+)");
  if (matchResult > 0) {
    int start = ms.MatchStart;  // 16 in this case
    int end = ms.MatchLength;   // 3 in this case
    String statusLine = resposta.substring(start - 1, start + end);
    Serial.println("------------ Status Line ------------");
    Serial.println(statusLine);
    Serial.println("------------ Status Line ------------");

    if (statusLine != "") {
      ms.Target(statusLine.c_str());
      matchResult = ms.Match("%d+$");
      if (matchResult > 0) {
        start = ms.MatchStart;  // 16 in this case
        end = ms.MatchLength;   // 3 in this case
        status = statusLine.substring(start, start + end).toInt();
        Serial.println("------------ Status ------------");
        Serial.println(status);

        Serial.println("------------ Status ------------");
      } else {
        Serial.println("No match 2!");
      }
    } else {
      Serial.println("not that different it sounds like");
    }

  } else {
    Serial.println("No match 1!");
  }

  blink();
  //Serial.println("The status is: " + status);

  //int status = getStatus();

  //Serial.println("Staaatus: " + String(status));
}

/*
int getStatus() {
  String lineStatus = match(resposta, 50);
  Serial.println("------------ Line Status ------------");
  Serial.println(lineStatus);
  Serial.println("-----------/ Line Status ------------");

  return 0;
  /*
  if (result > 0) {
    int start = ms.MatchStart;  // 16 in this case
    int end = ms.MatchLength;   // 3 in this case
    String statusLine = response.substring(start - 1, start + end);
    Serial.println("------------ JSON ------------");
    Serial.println(statusLine);
    Serial.println("------------ JSON ------------");

    if (result > 0) {
      int status = match(String(statusLine), "%d+$", 100).toInt();
      return status;
    }
  } else {
    return 0;
  }
  
}

String match(String &base, int expectedSize) {
  ms.Target(base.c_str());
  Serial.println("------------ BASE ------------");
  Serial.println(base);
  Serial.println("-----------/ BASE ------------");

  char matchResult = ms.Match("HTTP\/1.1(%s%d{3})");
  if (matchResult > 0) {
    char buf[expectedSize];
    return String(ms.GetMatch(buf));
  } else {
    Serial.println("No Match");
    return "";
  }
}
*/