/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Motion detection.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);

  mpu.setIntFreeFallEnabled(false);  
  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(false);
  
  mpu.setDHPFMode(MPU6050_DHPF_5HZ);

  mpu.setMotionDetectionThreshold(2);
  mpu.setMotionDetectionDuration(5);

  mpu.setZeroMotionDetectionThreshold(4);
  mpu.setZeroMotionDetectionDuration(2);	
  
  checkSettings();

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);  
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:                ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Motion Interrupt:     ");
  Serial.println(mpu.getIntMotionEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Zero Motion Interrupt:     ");
  Serial.println(mpu.getIntZeroMotionEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Free Fall Interrupt:       ");
  Serial.println(mpu.getIntFreeFallEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Motion Threshold:          ");
  Serial.println(mpu.getMotionDetectionThreshold());

  Serial.print(" * Motion Duration:           ");
  Serial.println(mpu.getMotionDetectionDuration());

  Serial.print(" * Zero Motion Threshold:     ");
  Serial.println(mpu.getZeroMotionDetectionThreshold());

  Serial.print(" * Zero Motion Duration:      ");
  Serial.println(mpu.getZeroMotionDetectionDuration());
  
  Serial.print(" * Clock Source:              ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:             ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets:     ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());

  Serial.print(" * Accelerometer power delay: ");
  switch(mpu.getAccelPowerOnDelay())
  {
    case MPU6050_DELAY_3MS:            Serial.println("3ms"); break;
    case MPU6050_DELAY_2MS:            Serial.println("2ms"); break;
    case MPU6050_DELAY_1MS:            Serial.println("1ms"); break;
    case MPU6050_NO_DELAY:             Serial.println("0ms"); break;
  }  
  
  Serial.println();
}

unsigned long interval=60000;
unsigned long previousMillis=0;
int Inactivity = 0;
int Activity = 0;

unsigned int InactivityPerHalfMinuted = 0;
unsigned int InactivityPerMinuted = 0;
unsigned int InactivityPerTwoMinuted = 0;

unsigned int ActivityPerHalfMinuted = 0;
unsigned int ActivityPerMinuted = 0;
unsigned int ActivityPerTwoMinuted = 0;


void loop()
{
  unsigned long currentMillis = millis();
  
  Activites act = mpu.readActivites();

  if (act.isActivity)
  {
    digitalWrite(13, HIGH);
    //Serial.println("Activity \t");
    Activity++;
  } else
  {
    digitalWrite(13, LOW);
    //Serial.println("Inactivity \t");
    Inactivity++;
  }

  delay(50);

  Serial.print("TIME: ");
  Serial.println((unsigned long)(currentMillis - previousMillis)/1000);

  if ((unsigned long)(currentMillis - previousMillis)/1000 == (interval/2)/1000) 
  {
      InactivityPerHalfMinuted = Inactivity;
      ActivityPerHalfMinuted = Activity;
      // It's time to do something!
      Serial.print("Inactivity per haf minuted is :\t");
      Serial.print(InactivityPerHalfMinuted);
      Serial.print("\t Activity per haf minuted is :\t");
      Serial.println(ActivityPerHalfMinuted);   
  }

  if ((unsigned long)(currentMillis - previousMillis)/1000 == (interval)/1000) 
  {
      InactivityPerMinuted = Inactivity;
      ActivityPerMinuted = Activity;
      // It's time to do something!
      Serial.print("Inactivity per minuted is :\t");
      Serial.print(InactivityPerMinuted);
      Serial.print("\t Activity per minuted is :\t");
      Serial.println(ActivityPerMinuted);   
  }
  
  if ((unsigned long)(currentMillis - previousMillis) >= interval*2) 
  {
      InactivityPerTwoMinuted = Inactivity;
      ActivityPerTwoMinuted = Activity;
      // It's time to do something!
      Serial.print("Inactivity per two minuted is :\t");
      Serial.print(InactivityPerTwoMinuted);
      Serial.print("\t Activity per two minuted is :\t");
      Serial.println(ActivityPerTwoMinuted);

      Inactivity=0;
      Activity=0;
      // Use the snapshot to set track time until next event
      previousMillis = currentMillis;

  }
}


