/*
 * ESP8266
 * Writed by Jatupon Hongweing CEO SPECTRE INDUSTRIES.
 * AUTHENTICATED BY SPECTRE INDUSTRIES.
*/
long lastReadingTime = 0;
WiFiClient client;
char results[4];

void Initial()
{  
  pinMode(errorPin, OUTPUT);

  for (int i=0;i<4; i++){   // let know we are working
    digitalWrite(errorPin ,HIGH);
    delay(200);
    digitalWrite(errorPin ,LOW);
    delay(200);
  }

  WiFiServer server(80);
  delay(10);
  
  // Connect to WiFi network
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();

  if (n == 0)
  {
    Serial.println("0");  //connection fail.
    ESP.deepSleep(sleepTimeS * 1000000);//one or other
  }

  WiFi.begin(charBuf, charBuf2);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("1");  //connected.

  // Start the server
  server.begin();
  WiFi.localIP();
}

void ubiSave_value(String value) {
  // if you get a connection, report back via serial:
  int num=0;
  String var = "{\"value\": " + String(value)+"}";
  num = var.length();
  if (client.connect("things.ubidots.com", 80)) {
    //Serial.println("connected ubidots");
    delay(100);
    client.println("POST /api/v1.6/variables/"+idvariable+"/values HTTP/1.1");
    //Serial.println("POST /api/v1.6/variables/"+idvariable+"/values HTTP/1.1");
    client.println("Content-Type: application/json");
    //Serial.println("Content-Type: application/json");
    client.println("Content-Length: "+String(num));
    //Serial.println("Content-Length: "+String(num));
    client.println("X-Auth-Token: "+token);
    //Serial.println("X-Auth-Token: "+token);
    client.println("Host: things.ubidots.com\n");
    //Serial.println("Host: things.ubidots.com\n");
    client.print(var);
    //Serial.print(var+"\n");
    Serial.println("1");  //sent data to ubidots.
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("0");
    ESP.deepSleep(sleepTimeS * 1000000);//one or other
  }

  if (!client.connected()) {
    Serial.println("0");
    //Serial.println("disconnecting ubidots.");
    client.stop();
    // do nothing forevermore:
    ESP.deepSleep(sleepTimeS * 1000000);//one or other
  }

  if (client.available()) {
    char c = client.read();
    //Serial.print(c);
  }
}
