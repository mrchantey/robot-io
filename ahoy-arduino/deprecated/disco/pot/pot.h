#pragma once

#include "Arduino.h"
#include "ArduinoEvent.h"

class Pot
{
public:
  Pot(int _pin);
  ArduinoEvent<Pot> *OnValueChanged;
  void Update();
  int value;
  int lastValue;

private:
  int pin;
  bool ValueChangedPredicate();
};