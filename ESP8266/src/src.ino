/*
 * ESP8266
 * Writed by Jatupon Hongweing CEO SPECTRE INDUSTRIES.
 * AUTHENTICATED BY SPECTRE INDUSTRIES.
*/
#include <stdio.h>
#include <ESP8266WiFi.h>
#define errorPin 13

String idvariable="";
String token="";

String ubidata;

bool _config = true;
short _a = 0;
String raw_data[5];
String data[5];
const unsigned long sleepTimeS = 200000000;

char charBuf[100];
char charBuf2[100];

void setup()
{
   Serial.begin(115200);
   Serial.print("1");     //Tell the main that i have already to use.
   
   while(_config)
   {
      if(Serial.available() > 0)
      {
        char c = Serial.read();

        switch(c)
        {
          case ';': //Do something.
                    data[_a] = raw_data[_a];
                    _a++;
                    break;
          case '#': //Do something.
                    _a=0;
                    _config = false;
                    break;
                    
          default:  raw_data[_a] += c;
                    break;
        }        
      }     
   }

   for(int i=0;i<5;i++)
   {
      switch(i)
      {
        case 0: 
                  data[i].toCharArray(charBuf, 100);                  
                  break;
                  
        case 1: 
                  data[i].toCharArray(charBuf2, 100);   
                  break;
                  
        case 2:
                  token    = data[i];
                  break;
        case 3:
                  idvariable = data[i];
                  break;
        case 4:
                  ubidata  = data[i];
                  break;
                  
        default : break;
      }
      
      //Serial.print(i);
      //Serial.print("\t");
      //Serial.println(data[i]);
   }

   Initial();
   ubiSave_value(ubidata);
}

void loop()
{
   ESP.deepSleep(sleepTimeS * 1000000);//one or other  
}
