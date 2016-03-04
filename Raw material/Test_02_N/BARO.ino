void BARO::compute()
{
  while (BME280.isMeasuring());
  BME280.readMeasurements();
}

void BARO::printFormattedFloat(float x, uint8_t precision) {
char buffer[10];

  dtostrf(x, 7, precision, buffer);
  #ifdef PRINT
    Serial.print(buffer);
  #endif
}

double BARO::printCompensatedMeasurements(short mode) {

float temp, humidity,  pressure, pressureMoreAccurate;
double tempMostAccurate, humidityMostAccurate, pressureMostAccurate;
char buffer[80];

  temp      = BME280.getTemperature();
  humidity  = BME280.getHumidity();
  pressure  = BME280.getPressure();
  
  pressureMoreAccurate = BME280.getPressureMoreAccurate();  // t_fine already calculated from getTemperaure() above
  
  tempMostAccurate     = BME280.getTemperatureMostAccurate();
  humidityMostAccurate = BME280.getHumidityMostAccurate();
  pressureMostAccurate = BME280.getPressureMostAccurate();

  if(mode == 1)
     return pressureMostAccurate;
  else if(mode == 2)
     return tempMostAccurate;
}

float BARO::getPressure()
{    
     pressure = printCompensatedMeasurements(1);
     #ifdef PRINT
            Serial.print("time: ");
            Serial.print((unsigned long)(_time  - prev_time));
            Serial.print("  interval: ");
            Serial.print(_time_update_pressure);

            Serial.print("  Al_Threshold: ");
            Serial.print(altitude_threshold);
            Serial.print("  pressure: ");
            Serial.print(pressure);
            Serial.print("  initial_pressure: ");
            Serial.print(initial_pressure); 
            Serial.print("  Al_handup: ");
            Serial.print(altitude_handup); 
            Serial.print("  Al_Resultant: ");
            Serial.print(resultant_altitude); 
            Serial.print(" ");
     #endif           
           
    //Update altitude.
    if(stop_timer == false)
    {
      _time = millis();
    }else{
       pressure = printCompensatedMeasurements(1); 
    }
    
    if((unsigned long)(_time  - prev_time) >= _time_update_pressure)
    {           
      initial_pressure = pressure;
      prev_time = _time;
    }   
        
    if(Handup == true)                                    //Push your hand up.
    {         
         stop_timer = true;
         if(initial_pressure-pressure <= altitude_handup)
         {
                resultant_altitude = initial_pressure-pressure;            //This is a maximum altitude that can be increase.
                if(resultant_altitude <= -0.01)
                {
                   stop_timer = false;
                }
         }else{
                resultant_altitude = altitude_handup;
         }
    }

    if(Handup == false)
    {
         stop_timer = false;
         resultant_altitude = initial_pressure-pressure;  //If your hand are locate at initial position, altitude will set a value to zero.
    }

    if(resultant_altitude < altitude_threshold)    //Fall.
    {
       stop_timer = true;
    }

    return initial_pressure-pressure;               
}

float BARO::getTemperature()
{
  double temperature = printCompensatedMeasurements(2);
  return temperature;
}

void BARO::initial()
{
    uint8_t chipID;
  #ifdef PRINT
    Serial.println("Welcome to the BME280 MOD-1022 weather multi-sensor test sketch!");
    Serial.println("Embedded Adventures (www.embeddedadventures.com)");
  #endif
  chipID = BME280.readChipId();
  
  // find the chip ID out just for fun
  #ifdef PRINT
    Serial.print("ChipID = 0x");
    Serial.print(chipID, HEX);
  #endif
  
 
  // need to read the NVM compensation parameters
  BME280.readCompensationParams();
  
  // Need to turn on 1x oversampling, default is os_skipped, which means it doesn't measure anything
  BME280.writeOversamplingPressure(os1x);  // 1x over sampling (ie, just one sample)
  BME280.writeOversamplingTemperature(os1x);
  BME280.writeOversamplingHumidity(os1x);
  
  // example of a forced sample.  After taking the measurement the chip goes back to sleep
  BME280.writeMode(smForced);
  while (BME280.isMeasuring()) {
    #ifdef PRINT
      Serial.println("Measuring...");
    #endif
  }
  #ifdef PRINT
    Serial.println("Done!");
  #endif
  
  // read out the data - must do this before calling the getxxxxx routines
  BME280.readMeasurements();

  #ifdef PRINT
    Serial.print("Temp=");
    Serial.println(BME280.getTemperature());  // must get temp first
    Serial.print("Humidity=");
    Serial.println(BME280.getHumidity());
    Serial.print("Pressure=");
    Serial.println(BME280.getPressure());
    Serial.print("PressureMoreAccurate=");
    Serial.println(BME280.getPressureMoreAccurate());  // use int64 calculcations
    Serial.print("TempMostAccurate=");
    Serial.println(BME280.getTemperatureMostAccurate());  // use double calculations
    Serial.print("HumidityMostAccurate=");
    Serial.println(BME280.getHumidityMostAccurate()); // use double calculations
    Serial.print("PressureMostAccurate=");
    Serial.println(BME280.getPressureMostAccurate()); // use double calculations
  #endif
  
  // Example for "indoor navigation"
  // We'll switch into normal mode for regular automatic samples
  
  BME280.writeStandbyTime(tsb_0p5ms);        // tsb = 0.5ms
  BME280.writeFilterCoefficient(fc_16);      // IIR Filter coefficient 16
  BME280.writeOversamplingPressure(os16x);    // pressure x16
  BME280.writeOversamplingTemperature(os2x);  // temperature x2
  BME280.writeOversamplingHumidity(os1x);     // humidity x1
   
  BME280.writeMode(smNormal);

  initial_pressure = BME280.getPressureMostAccurate();
}
