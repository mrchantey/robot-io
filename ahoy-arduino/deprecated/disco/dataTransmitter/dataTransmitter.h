#pragma once

#include "Arduino.h"
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

class DataTransmitter
{
public:
  DataTransmitter();
  void SendBytes(uint8_t *msg, uint8_t len);
  RH_ASK driver;

private:
};
