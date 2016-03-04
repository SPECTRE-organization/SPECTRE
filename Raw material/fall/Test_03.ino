#include <Wire.h>
#define PRINT

#include <MPU6050.h>
class ACCELEROMETER
{
    public:
        void initial();
        void compute();
        float getACCX();
        float getACCY();
        float getACCZ();
        float getResultant();
        float getAngleofResultant();

    private:
        MPU6050 mpu;         
        Vector ScaledAccel;
        void checkSettings();         
};

#include <BME280_MOD-1022.h>
class BARO
{
  public:
      void initial();
      void compute();
      float getPressure();
      float getTemperature();

   private:
      float  initial_pressure = 0;
      double pressure = 0;
      void   printFormattedFloat(float x, uint8_t precision);
      double printCompensatedMeasurements(short mode);
};
