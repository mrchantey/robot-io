#pragma once
#include "dataTransmitter.h"
#include "mpu6050.h"
DataTransmitter *dataTransmitter;
MPU6050 *mpu;
#include "discoMath.h"
void setup()
{

    Serial.begin(9600);
    dataTransmitter = new DataTransmitter();
    mpu = new MPU6050;
    Serial.println("hello");
}

int count = 0;

void loop()
{
    MPU_Data data = mpu->GetData();
    uint8_t ax = Math::MapInt16To8(data.acc.x);
    uint8_t ay = Math::MapInt16To8(data.acc.y);
    uint8_t az = Math::MapInt16To8(data.acc.z);
    uint8_t gx = Math::MapInt16To8(data.gyro.x);
    uint8_t gy = Math::MapInt16To8(data.gyro.y);
    uint8_t gz = Math::MapInt16To8(data.gyro.z);
    data.acc.Print();
    // const uint8_t msg[] = {8, count++, data.acc.x, data.acc.y, data.acc.z, data.gyro.x, data.gyro.y, data.gyro.z};
    const uint8_t msg[] = {8, count++, ax, ay, az, gx, gy, gz};
    dataTransmitter->SendBytes(msg, sizeof(msg) / sizeof(*msg));
    delay(10);
}