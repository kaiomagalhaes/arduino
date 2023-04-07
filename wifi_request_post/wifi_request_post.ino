#include "SoftwareSerial.h"

SoftwareSerial esp(10, 11);  // RX, TX

String rede = "vaka_viking_2g";
String senha = "batataquente";

String resposta = "";
String uri = "/";
String data;
String server = "api.notifications.codelitt.dev";  // www.example.com

String temp, hum;
void setup() {
  Serial.begin(9600);
  esp.begin(9600);

  Serial.println("Inicializando...");
  delay(1000);

  Serial.println("Conectando a rede...");
  String CWJAP = "\"AT+CWJAP=\"";
  CWJAP += rede;
  CWJAP += "\",\"";
  CWJAP += senha;
  CWJAP += "\"";
  sendCommand(CWJAP);
  readResponse(10000);

  delay(2000);  //espera de seguranca

  if (resposta.indexOf("OK") == -1) {  //procura na resposta se houve OK
    Serial.println("Atencao: Nao foi possivel conectar a rede WiFi.");
    Serial.println("Verifique se o nome da rede e senha foram preenchidos corretamente no codigo e tente novamente.");
  } else {
    Serial.println("Conectato!");
  }
}

void loop() {
  Serial.println("Starting loop!");

  data = "{\"temperature\"=\"12\", \"humidity\"=\"30\"}";  // data sent must be under this form //name1=value1&name2=value2.

  httppost();

  delay(5000);
}


void sendCommand(String cmd) {
  esp.println(cmd);
}

void readResponse(unsigned int timeout) {
  unsigned long timeIn = millis();  //momento que entramos nessa funcao é salvo
  resposta = "";
  //cada comando AT tem um tempo de resposta diferente...
  while (timeIn + timeout > millis()) {
    if (esp.available()) {
      char c = esp.read();
      resposta += c;
    }
  }
  Serial.println(resposta);
}


void httppost() {
  Serial.println("Starting httppost!");

  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");  //start a TCP connection.

  if (esp.find("OK")) {

    Serial.println("TCP connection ready");
  }
  delay(1000);

  String postRequest =

    "POST " + uri + " HTTP/1.0\r\n" +

    "Host: " + server + "\r\n" +

    "Accept: *" + "/" + "*\r\n" +

    "Content-Length: " + data.length() + "\r\n" +

    "Content-Type: application/json\r\n" +

    "\r\n" + data;

  String sendCmd = "AT+CIPSEND=";  //determine the number of caracters to be sent.

  esp.print(sendCmd);

  esp.println(postRequest.length());

  delay(500);

  Serial.println("Sending..");
  esp.print(postRequest);

  if (esp.find("SEND OK")) {
    Serial.println("Packet sent.");
    Serial.println("-------------- RESPONSE --------------");

    while (esp.available()) {

      String tmpResp = esp.readString();

      Serial.println(tmpResp);
    }
    Serial.println("-------------- RESPONSE --------------");

    Serial.println("closing connection");

    // close the connection

    esp.println("AT+CIPCLOSE");
  }
}
