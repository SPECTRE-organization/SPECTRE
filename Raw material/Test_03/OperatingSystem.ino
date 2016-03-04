BARO BARO;
ACCELEROMETER ACCELEROMETER;

class FALLDETECT
{
    public:
        short Detect()
        {            
             for (i = 0; i < 7; i++){    // substitute some different filter values
                filterVal = i * .15; 
            
            
                for (j = 0; j< 60; j++){      
            
                  if (j < 30){            // generate a simulated square wave
                    sensVal = 1023;
                  }
                  else
                  {
                    sensVal = 0; 
                  }
            
                  sensVal = BARO.getPressure()*100;   //this is what one would do normally
                  smoothedVal =  smooth(sensVal, filterVal, smoothedVal);   // second parameter determines smoothness  - 0 is off,  .9999 is max smooth 
            
                  Serial.print(sensVal);
                  Serial.print("   ");
                  Serial.println(smoothedVal, DEC);
                  delay(30); 
                }
             }
        }
                                
    private:     
        unsigned long currentMillis  = 0;
        unsigned long previousMillis = 0;
        int interval = 3000;
        
        int i, j;              // loop counters 
        long sensVal;           // for raw sensor values 
        float filterVal;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)
        float smoothedVal;     // this holds the last loop value just use a unique variable for every different sensor that needs smoothing
        float smoothedVal2;   // this would be the buffer value for another sensor if you needed to smooth two different sensors - not used in this sketch


        long smooth(long data, float filterVal, float smoothedVal)
        {
          if (filterVal > 1){      // check to make sure param's are within range
            filterVal = .99;
          }
          else if (filterVal <= 0){
            filterVal = 0;
          }
        
          smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
        
          return (long)smoothedVal;
        }
        
};
