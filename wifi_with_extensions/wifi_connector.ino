String rede = "vaka_viking_2g";
String senha = "batataquente";

//String rede = "Kaio";
//String senha = "frangofrito";


void connect_to_wifi() {
  white();
  delay(100);
  turnLightsOff();
  delay(100);
  white();
  turnLightsOff();

  reset();

  Serial.println("Conectando a rede...");

  sendCommand(get_connection_string());
  readResponse(3000);

  if (resposta.indexOf("OK") == -1) {
    Serial.println("Atencao: Nao foi possivel conectar a rede WiFi. \r\nTrying again.");
    connect_to_wifi();
  } else {
    Serial.println("Conectato!");
  }
}

void sendCommand(String cmd) {
  esp.println(cmd);
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
  resposta = "";
  unsigned long timeIn = millis();
  while (timeIn + timeout > millis()) {
    while (esp.available()) {
      char c = esp.read();
      resposta += c;
      delay(1);
    }
  }
  return resposta;
}

void reset() {
  esp.println("AT+RST");
  readResponse(1000);
  if (esp.find("OK")) Serial.println("Module Reset");
}

void closeRequest() {
  Serial.println("Closing the request:" + readResponse(1000));
  esp.println("AT+CIPCLOSE");
  readResponse(1000);
}
