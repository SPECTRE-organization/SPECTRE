FALLDETECT FALLDETECT;

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
    Serial.println(FALLDETECT.Detect()); 
}
