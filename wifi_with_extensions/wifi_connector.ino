String rede = "Kaio";
String senha = "frangofrito";

void connect_to_wifi() {
  delay(1000);
  reset();

  Serial.println("Conectando a rede...");

  sendCommand(get_connection_string());
  String resposta = readResponse(10000);

  delay(2000);  //espera de seguranca

  if (resposta.indexOf("OK") == -1) {
    Serial.println("Atencao: Nao foi possivel conectar a rede WiFi. \r\nTrying again.");
    connect_to_wifi();
  } else {
    Serial.println("Conectato!");
  }
}

String get_connection_string() {
  String CWJAP = "\"AT+CWJAP=\"";
  CWJAP += rede;
  CWJAP += "\",\"";
  CWJAP += senha;
  CWJAP += "\"";

  return CWJAP;
}

String readResponse(unsigned int timeout) {
  unsigned long timeIn = millis();  //momento que entramos nessa funcao é salvo
  String resposta = "";
  //cada comando AT tem um tempo de resposta diferente...
  while (timeIn + timeout > millis()) {
    while (esp.available()) {
      char c = esp.read();
      resposta += c;
      delay(1);
    }
  }
  return resposta;
}

String getBody(String response) {
  MatchState ms;
  ms.Target("{.*}");
}

void reset() {
  esp.println("AT+RST");
  delay(1000);
  if (esp.find("OK")) Serial.println("Module Reset");
}

void closeRequest() {
  Serial.println("Closing the request:" + readResponse(1000));
  esp.print("AT+CIPCLOSE");
  delay(1000);
}
