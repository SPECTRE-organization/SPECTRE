BARO BARO;
ACCELEROMETER ACCELEROMETER;

class FALLDETECT
{
    public:
        short Detect()
        {
            //0 = Normal , 2 = Body Damage , 3 = Dangerous.
//             if(BARO.getPressure() < -0.01)
//             {
//                currentMillis = millis();
//                if(BARO.getPressure() < -0.06)
//                {
//                  if(currentMillis-previousMillis < threshold)
//                      return 1;
//                  else
//                      return 0;
//                }                
//                                            
//            }          
//            else if((unsigned long)(currentMillis  - previousMillis) >= interval)
//            {           
//                  previousMillis = currentMillis;
//            }   
               
            #ifdef PRINT
               Serial.print("PRESSURE");
               Serial.print(BARO.getPressure());
               Serial.print("\tTIME\t");
               Serial.print(currentMillis-previousMillis);
               Serial.print("\t");
             #endif

//            return 0;
        }
                        
    private:     
        unsigned long currentMillis  = 0;
        unsigned long previousMillis = 0;
        int interval = 3000;
        int threshold = 1500;
};
