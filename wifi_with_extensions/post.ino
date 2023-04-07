String post(String host, String data) {
  Serial.println("Starting post!");

  esp.println("AT+CIPSTART=\"TCP\",\"" + host + "\",80");  //start a TCP connection.

  delay(1000);

  String postRequest =
    "POST " + uri + " HTTP/1.0\r\n" +

    "Host: " + host + "\r\n" +

    "Accept: *" + "/" + "*\r\n" +

    "Content-Length: " + data.length() + "\r\n" +

    "Content-Type: application/json\r\n" +

    "\r\n" + data;

  String sendCmd = "AT+CIPSEND=";  //determine the number of caracters to be sent.

  esp.print(sendCmd);

  esp.println(postRequest.length());

  delay(500);

  Serial.println("Making post request");
  esp.print(postRequest);
  String response;
  if (esp.find("SEND OK")) {
    Serial.println("Request sent.");
    if (esp.available()) {
      Serial.println("potaaaato");
      response = esp.readString();
    }

    esp.println("AT+CIPCLOSE");
    return response;
  }
}