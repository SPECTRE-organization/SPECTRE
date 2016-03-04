#include "LowPower.h"
#include <Wire.h>
#include <MPU6050.h>

class MotionAndEnergy{
    public:
        void Initial() 
        {    
          while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
          {
            #ifdef PRINT
            Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
            #endif
            delay(500);
          }
        }        
          
        bool IMPACTED()
        {
          Vector normAccel = mpu.readNormalizeAccel();
          VectorResultant = sqrt(normAccel.XAxis*normAccel.XAxis + normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis);
         
          if(VectorResultant > IMPACT_THRESHOLD)
          {          
                #ifdef PRINT
                Serial.println("FALL DETECTED !");
                #endif
                return 1;
          }else{
                return 0;
          }
        }

        bool UNCONCIOUS()
        {          
          if(VectorResultant > 9 && VectorResultant < 13)
          {
              c_t = millis();
              if ((unsigned long)(c_t - p_t) >= unconcious_t) 
              {              
                 p_t = c_t;   
                 return 1;                 
              } 
          }else{
             p_t = c_t;   
             return 0;      
          }
        }


    private:
        MPU6050 mpu;   
        float VectorResultant = 0;
        const int IMPACT_THRESHOLD =100;
        unsigned long p_t = 0;
        unsigned long c_t = 0;
};

