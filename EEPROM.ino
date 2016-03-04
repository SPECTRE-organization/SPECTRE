#include <EEPROM.h>

struct MyObject {
  char SSID[15];
  char PASS[15];
  char TOKEN[35];
  char VARIABLE01[35];
  char VARIABLE02[35];
  char VARIABLE03[35];
  char VARIABLE04[35];
  char VARIABLE05[35];
  char VARIABLE06[35];
  char VARIABLE07[35];
};

MyObject customVar;

class Storage{
      public:
         void Initial()
         {
            float f = 0.00f;   //Variable to store data read from EEPROM.
            int eeAddress = 0; //EEPROM address to start reading from
            EEPROM.get(eeAddress, f);
            eeAddress = sizeof(float); //Move address to the next byte after float 'f'.
            EEPROM.get(eeAddress, customVar);

            #ifdef DEVELOPER
            Serial.println("INSIDE EEPROM: ");
            Serial.println(customVar.SSID);
            Serial.println(customVar.PASS);
            Serial.println(customVar.TOKEN);
            Serial.println(customVar.VARIABLE01);
            Serial.println(customVar.VARIABLE02);
            Serial.println(customVar.VARIABLE03);
            Serial.println(customVar.VARIABLE04);
            Serial.println(customVar.VARIABLE05);
            Serial.println(customVar.VARIABLE06);
            Serial.println(customVar.VARIABLE07);
            #endif
         }      

         void Configuration()
         {
            if(Serial.available() > 0)
            {
                String str = Serial.readString();

                while(str == "WiFi")
                {
                  if(Serial.available() > 0)
                  {
                    String _str = Serial.readString();
                    Serial.println(_str);

                    switch(i) {
                      case 0:
                              _str.toCharArray(customVar.SSID,15);
                              break;
                      case 1:
                              _str.toCharArray(customVar.PASS,15);
                              break;
                    }

                    if(i == 1)
                    {
                      save();
                      str = "";
                      i = 0;
                      resetFunc();  //call reset
                      break; 
                    }else i++;
                  }
                }

                while(str == "CONFIG")
                {
                  if(Serial.available() > 0)
                  {
                    String _str = Serial.readString();
                    Serial.println(_str);

                    switch(i) {
                      case 0:
                              _str.toCharArray(customVar.SSID,15);
                              break;
                      case 1:
                              _str.toCharArray(customVar.PASS,15);
                              break;
                      case 2:
                              _str.toCharArray(customVar.TOKEN,35);
                              break;
                      case 3:
                              _str.toCharArray(customVar.VARIABLE01,35);
                              break;
                      case 4:
                              _str.toCharArray(customVar.VARIABLE02,35);
                              break;
                      case 5:
                              _str.toCharArray(customVar.VARIABLE03,35);
                              break;
                      case 6:
                              _str.toCharArray(customVar.VARIABLE04,35);
                              break;
                      case 7:
                              _str.toCharArray(customVar.VARIABLE05,35);
                              break;
                      case 8:
                              _str.toCharArray(customVar.VARIABLE06,35);
                              break;
                      case 9:
                              _str.toCharArray(customVar.VARIABLE07,35);
                              break;
                    }

                    if(i == 9)
                    {
                      save();
                      str = "";
                      i = 0;
                      resetFunc();  //call reset
                      break; 
                    }else i++;
                  }
               }
            }
         }
          
      private:
         short i = 0;
         
         void save()
         {
              float f = 123.456f;
              int eeAddress = 0;   
              EEPROM.put(eeAddress, f);
              eeAddress += sizeof(float);
              EEPROM.put(eeAddress, customVar);
         }
};

