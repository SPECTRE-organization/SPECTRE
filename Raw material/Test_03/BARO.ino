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
  }
