#include "LowPower.h"
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#define IMPACT_THRESHOLD 100
#define FALL_THRESHOLD 6
#define FALL_TIME 150
#define ACTIVITY_THRESHOLD 15
#define ACTIVITY_COUNT 100
#define UNCONSCIOUS_TIME 60000

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
bool TIMER01 = false;
bool TIMER02 = false;
unsigned long interval = 500;
int ACTIVITY = 0;


#define ENERGY_interval  60000
unsigned long ENERGY_currentMillis = 0;
unsigned long ENERGY_previousMillis = 0;
int ENERGY_ACTIVITY = 0;
int return_activity = 100;
short more_saver = 0;
int sleep_time = 0;
bool slept = false;

void setup() 
{
  Serial.begin(115200);
    
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{
    FALLDETECT();
    ENERGY_SAVE();
}

void ENERGY_SAVE()
{
    CURRENT_ACTIVITY();
    if(return_activity < 36)
    {
        Serial.println("rest detect!");   
        Serial.println("ENERGY SAVE");     
        sleep(sleep_time);         
        return_activity = 100;
        more_saver++;
        slept = true;
    }else{
      if(slept != true)
      {
        sleep_time = 0;
        more_saver = 0;
      }
    }
    
    if(more_saver > 4)
    {
      sleep_time = 1;
    }
    if(more_saver > 10)
    {
      sleep_time = 2;
    }
    
//    Serial.print(return_activity);
//    Serial.print("\t");
//    Serial.print(more_saver);
//    Serial.print("\t");
//    Serial.println(sleep_time);
}

void sleep(short mode)
{
    switch (mode)
    {
      case 0:
        LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);    
        break;
      case 1:
        LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
        break;
      case 2:
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
        break;
    }
}


int CURRENT_ACTIVITY()
{
    ENERGY_currentMillis = millis();

    if ((unsigned long)(ENERGY_currentMillis - ENERGY_previousMillis) >= ENERGY_interval) {
      return_activity = ENERGY_ACTIVITY;
      ENERGY_ACTIVITY = 0;
      slept = false;
      ENERGY_previousMillis = ENERGY_currentMillis;
    }
}

void FALLDETECT()
{
  Vector normAccel = mpu.readNormalizeAccel();
  float VectorResultant = sqrt(normAccel.XAxis*normAccel.XAxis + normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis);
  float angle = atan(normAccel.YAxis*normAccel.YAxis/normAccel.XAxis*normAccel.XAxis);
  Serial.println(VectorResultant);
  
  if(VectorResultant < FALL_THRESHOLD)
  {
      TIMER01 = true;
  }
  if(TIMER01 == true && VectorResultant > IMPACT_THRESHOLD)
  {
     if ((unsigned long)(currentMillis - previousMillis) >= FALL_TIME)
     {
        Serial.println("FALL DETECTED !");
        ACTIVITY = 0;
        TIMER02 = true;
        interval = UNCONSCIOUS_TIME;
     }else{
        Serial.println("IMPACTED !");
     }
     previousMillis = currentMillis;
     TIMER01 = false;
  }

  if(VectorResultant > ACTIVITY_THRESHOLD)
  {
    if(ACTIVITY < 1000)
    {
      ACTIVITY++;
      ENERGY_ACTIVITY++;
      //Serial.println(ACTIVITY);
    }else{
      ACTIVITY = 0;
      ENERGY_ACTIVITY = 0;
    }
  }  
  if(TIMER01 || TIMER02)
  {
      currentMillis = millis();
  } 
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {        //TIME OUT.
      if(ACTIVITY < ACTIVITY_COUNT && TIMER02 == true)
      {
        Serial.println("Unconcious");
        delay(2000);
      }     
      previousMillis = currentMillis;
      TIMER01 = false;
      TIMER02 = false;
      interval = 500;
  }
  delay(20);
}

