#pragma once
#include <Wire.h>

//default ranges
//accelerometer:  +- 2 g-force
//gyroscope:      +- 250 degrees per second

class MPU6050 : public DataGetterAction<MPUData>
{

private:
  const int MPU_addr = 0x68;

public:
  MPU6050(bool _autoRepeat = true) : DataGetterAction<MPUData>(_autoRepeat)
  {
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); //PWR_MGMT_1 register
    Wire.write(0);    //sets to 0, wakes up mpu6050
    Wire.endTransmission(true);
  }
  void Invoke(NoType nt = noType)
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);
    MPUData data = MPUData();
    data.acc.x = Wire.read() << 8 | Wire.read();
    data.acc.y = Wire.read() << 8 | Wire.read();
    data.acc.z = Wire.read() << 8 | Wire.read();
    data.temp = (Wire.read() << 8 | Wire.read()) / 340.00 + 36.53;
    data.gyro.x = Wire.read() << 8 | Wire.read();
    data.gyro.y = Wire.read() << 8 | Wire.read();
    data.gyro.z = Wire.read() << 8 | Wire.read();

    onData->Invoke(data);
  }
};
