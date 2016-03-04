void ACCELEROMETER::initial()
{
   #ifdef PRINT
      Serial.println("Initialize MPU6050");
   #endif
   
   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
   {
     #ifdef PRINT
        Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
     #endif
     delay(500);
   }
   checkSettings();
}

void ACCELEROMETER::compute()
{
  ScaledAccel = mpu.readScaledAccel();

  if(getACCX() > 0.78)
  {
      Handup = true;
  }else{
      Handup = false;
  }
  
}

float ACCELEROMETER::getACCX()
{
  return ScaledAccel.XAxis;
}
float ACCELEROMETER::getACCY()
{
  return ScaledAccel.YAxis;
}
float ACCELEROMETER::getACCZ()
{
  return ScaledAccel.ZAxis;
}

float ACCELEROMETER::getResultant()
{
  float VectorResultant = sqrt(ScaledAccel.XAxis*ScaledAccel.XAxis + ScaledAccel.YAxis*ScaledAccel.YAxis + ScaledAccel.ZAxis*ScaledAccel.ZAxis);
  return VectorResultant;
}
float ACCELEROMETER::getAngleofResultant()
{
  float angle = atan(ScaledAccel.YAxis*ScaledAccel.YAxis/ScaledAccel.XAxis*ScaledAccel.XAxis);
  return angle;
}

void ACCELEROMETER::checkSettings()
  {
    #ifdef PRINT
      Serial.println();          
      Serial.print(" * Sleep Mode:            ");
      Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");          
      Serial.print(" * Clock Source:          ");
    #else
      mpu.getSleepEnabled();
    #endif
    
    switch(mpu.getClockSource())
    {
      case MPU6050_CLOCK_KEEP_RESET:    
                #ifdef PRINT
                    Serial.println("Stops the clock and keeps the timing generator in reset");
                #endif 
                break;
      case MPU6050_CLOCK_EXTERNAL_19MHZ:
                #ifdef PRINT
                    Serial.println("PLL with external 19.2MHz reference");
                    #endif 
                    break;
      case MPU6050_CLOCK_EXTERNAL_32KHZ: 
                #ifdef PRINT
                    Serial.println("PLL with external 32.768kHz reference");
                    #endif 
                    break;
      case MPU6050_CLOCK_PLL_ZGYRO:     
                #ifdef PRINT
                    Serial.println("PLL with Z axis gyroscope reference");
                    #endif 
                    break;
      case MPU6050_CLOCK_PLL_YGYRO:   
                #ifdef PRINT
                    Serial.println("PLL with Y axis gyroscope reference");
                    #endif 
                    break;
      case MPU6050_CLOCK_PLL_XGYRO:    
                #ifdef PRINT
                    Serial.println("PLL with X axis gyroscope reference");
                    #endif 
                    break;
      case MPU6050_CLOCK_INTERNAL_8MHZ:
                #ifdef PRINT
                    Serial.println("Internal 8MHz oscillator");
                    #endif 
                    break;
    }
    
    #ifdef PRINT
      Serial.print(" * Accelerometer:         ");
    #endif
    switch(mpu.getRange())
    {
      case MPU6050_RANGE_16G: 
                  #ifdef PRINT 
                      Serial.println("+/- 16 g"); 
                  #endif   
                  break;
      case MPU6050_RANGE_8G: 
                  #ifdef PRINT
                      Serial.println("+/- 8 g");
                  #endif
                  break;
      case MPU6050_RANGE_4G: 
                  #ifdef PRINT
                      Serial.println("+/- 4 g"); 
                  #endif
                  break;
      case MPU6050_RANGE_2G:
                  #ifdef PRINT
                      Serial.println("+/- 2 g");
                  #endif
                  break;
    }  

    #ifdef PRINT
      Serial.print(" * Accelerometer offsets: ");
      Serial.print(mpu.getAccelOffsetX());
      Serial.print(" / ");
      Serial.print(mpu.getAccelOffsetY());
      Serial.print(" / ");
      Serial.println(mpu.getAccelOffsetZ());            
      Serial.println();
    #endif
}
