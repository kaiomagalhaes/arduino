#include "SoftwareSerial.h"
#include <Regexp.h>

SoftwareSerial esp(10, 11);  // RX, TX


void setup() {
  Serial.println("Inicializando...");

  Serial.begin(9600);
  esp.begin(9600);

  connect_to_wifi();
}

void loop() {
  Serial.println("Starting loop!");

  String host = "eogg0iqtwmn3wfn.m.pipedream.net";
  String uri = "/";
  int port = 80;
  //String host = "api.notifications.codelitt.dev";
  //data = "{\"temperature\"=\"12\", \"humidity\"=\"30\"}";
  //String host = "api.notifications.codelitt.dev";
  //String response = post(host, data);
  String response = get(host, uri, port);
  Serial.println("------------ Response ------------");
  Serial.println(response);
  Serial.println("-----------/ Response ------------");

  int status = getStatus(response);

  Serial.println("Staaatus: " + String(status));
}

int getStatus(String httpResponse) {
  Serial.println("------------ Response Start ------------");
  Serial.println(httpResponse);
  Serial.println("-----------/ Response End ------------");

  MatchState ms;
  ms.Target(httpResponse.c_str());

  String lineRegex = "HTTP\/1.1(%s%d{3})";
  char lineStatus = ms.Match(lineRegex.c_str());
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
  */
}

String match(String base, String reg, int expectedSize) {
  MatchState mst;
  mst.Target(base.c_str());
  char matchResult = mst.Match(reg.c_str());
  if (matchResult > 0) {
    char buf[expectedSize];
    return String(mst.GetMatch(buf));
  } else {
    return "";
  }
}

void sendCommand(String cmd) {
  esp.println(cmd);
}