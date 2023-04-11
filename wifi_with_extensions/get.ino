void get() {
  Serial.println("Starting get!");

  esp.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + String(port));  //start a TCP connection.

  readResponse(1000);

  String getRequest = getRequestString();

  String sendCmd = "AT+CIPSEND=";  //determine the number of caracters to be sent.
  readResponse(1000);

  esp.print(sendCmd);
  readResponse(1000);

  esp.println(getRequest.length());

  readResponse(1000);

  Serial.println("Making request");
  esp.print(getRequest);

  Serial.println("Reading response");
  readResponse(1000 * 3);

  //closeRequest();
  //return resposta;
}

String getRequestString() {
  return "GET " + uri + " HTTP/1.1\r\n" +

         "Host: " + host + "\r\n" +

         "Accept: */*\r\n" +

         "Content-Type: application/json\r\n\r\n";
}