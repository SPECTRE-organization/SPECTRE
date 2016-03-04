#include <SoftwareSerial.h>
SoftwareSerial ESPserial(serial_rx,serial_tx); // RX | TX

class Wireless
{
  public:
    void Initial() {
      ESPserial.begin(115200); 
    }

    char Receive()
    {
      if ( ESPserial.available() )   
      {            
          return ESPserial.read();
      }
      else{
          return  RecentlyData;
      }
    }

    void Send(short variable,int data) 
    {      
      if(variable != lastvar || data != lastdata)
      {
          reset();
          Command = "";
          Command +=  customVar.SSID;
          Command +=  ";";
          Command +=  customVar.PASS;
          Command +=  ";";
          Command +=  customVar.TOKEN;
          Command +=  ";";
          switch(variable){
              case 1:
                      Command += customVar.VARIABLE01;
                      break;
              case 2:
                      Command += customVar.VARIABLE02;
                      break;
              case 3:
                      Command += customVar.VARIABLE03;
                      break;
              case 4:
                      Command += customVar.VARIABLE04;
                      break;
              case 5:
                      Command += customVar.VARIABLE05;
                      break;
              case 6:
                      Command += customVar.VARIABLE06;
                      break;
              case 7:
                      Command += customVar.VARIABLE07;
                      break;
              default:
                      #ifdef PRINT
                      Serial.println("Unknow variable!");
                      #endif
                      break;     
          }
    
          Command +=  ";";
          Command +=  data;
          Command +=  ";";
          Command +=  "#";
          
    //      Command -> SPECTRE;SPECTRE8056;4McsyuvZzaosvlhjH1kdpW6lifg3cR;56b2cfb97625427d54dfb149;1;#
          char cstr[100];
          Command.toCharArray(cstr,100);
          #ifdef DEVELOPER
            Serial.write( "SEND: " );  
            Serial.write( cstr );  
            Serial.write( "\n" );  
          #endif  
          ESPserial.write(cstr);  
    
          lastvar = variable;
          lastdata = data;
        }else{
              #ifdef PRINT
                Serial.print(variable);
                Serial.print("  <->  ");
                Serial.println(lastvar);
                
                Serial.print(data);
                Serial.print("  <->  ");
                Serial.println(lastdata);  
              #endif              
        }
        delay(5000);
    }

  private:
    String Data;  
    char RecentlyData = '-';
    short lastvar = 0;
    int lastdata = 0;
    String Command = "c";

    void reset()
    {
      digitalWrite(9,LOW);
      delay(200);
      digitalWrite(9,HIGH);
      delay(5000);
    }

};
