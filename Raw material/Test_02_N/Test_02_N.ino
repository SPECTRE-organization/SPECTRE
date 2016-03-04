#include <Wire.h>
#define PRINT

bool Handup = false;
float max_altitude_handup = 0.07;
float medium_altitude_handup = 0.05;
float altitude_handup = 0.04;
float resultant_altitude = 0;

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
      float altitude_threshold = -0.04;
      double initial_pressure = 0;
      double pressure = 0;
      unsigned long _time = 0;
      unsigned long prev_time = 0;
      unsigned long _time_update_pressure = 1000;
      bool stop_timer = false;
      void printFormattedFloat(float x, uint8_t precision);
      double printCompensatedMeasurements(short mode);
};
