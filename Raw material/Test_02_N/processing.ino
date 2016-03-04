BARO BARO;
ACCELEROMETER ACCELEROMETER;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  
  BARO.initial();
  ACCELEROMETER.initial();
}

void loop()
{
    BARO.compute();
    ACCELEROMETER.compute();
    
    Serial.print(BARO.getPressure());
    Serial.print("\t");
    Serial.print(BARO.getTemperature());
    Serial.print("\t");
    Serial.print(ACCELEROMETER.getACCX());
    Serial.print("\t");
    Serial.print(ACCELEROMETER.getACCY());
    Serial.print("\t");
    Serial.println(ACCELEROMETER.getACCZ());
}
