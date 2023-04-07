String get(String host) {
  Serial.println("Starting get!");

  esp.println("AT+CIPSTART=\"TCP\",\"" + host + "\",80");  //start a TCP connection.

  delay(1000);

  String getRequest =
    "GET " + uri + " HTTP/1.0\r\n" +

    "Host: " + host + "\r\n" +

    "Accept: *" + "/" + "*\r\n" +

    "Content-Type: application/json\r\n\r\n";


  String sendCmd = "AT+CIPSEND=";  //determine the number of caracters to be sent.

  esp.print(sendCmd);

  esp.println(getRequest.length());

  delay(500);

  Serial.println("Making get request");
  esp.print(getRequest);


  Serial.println("Request sent.");
  long int wait = 1000 * 12;
  Serial.println("Reading response");

  String resposta = readResponse(wait);

  closeRequest();

  return resposta;
}