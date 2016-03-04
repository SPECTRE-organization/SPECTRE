#include <SoftwareSerial.h>
SoftwareSerial ESPserial(10,11); // RX | TX
String Data;
void setup() {
  // put your setup code here, to run once:
  ESPserial.begin(115200); 
  Serial.begin(9600);
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9,HIGH);
  
  if ( ESPserial.available() )   
  {     
      Serial.write( ESPserial.read() );     
  }

  // listen for user input and send it to the ESP8266
  if ( Serial.available() )       
  {  
      char cstr[100];
      Data = Serial.readString();

      if(Data != "$")
      {
      Data.toCharArray(cstr,100);
      Serial.write( "SEND: " );  
      Serial.write( cstr );  
      Serial.write( "\n" );    
      ESPserial.write(cstr);  
      }else{
        digitalWrite(9,LOW);
        delay(200);
      }
  }
}
