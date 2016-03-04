/*
  SLEEP_15Ms,
  SLEEP_30MS, 
  SLEEP_60MS,
  SLEEP_120MS,
  SLEEP_250MS,
  SLEEP_500MS,
  SLEEP_1S,
  SLEEP_2S,
  SLEEP_4S,
  SLEEP_8S,
  SLEEP_FOREVER
*/

#include "LowPower.h"

void setup()
{
    Serial.begin(115200);
}

void loop() 
{
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
}
