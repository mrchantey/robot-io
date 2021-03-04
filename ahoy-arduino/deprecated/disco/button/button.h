#pragma once

#include "Arduino.h"
#include "discoEvent.h"
// #include "event.h"
#include "noType.h"
class Button
{
public:
  Button(int _pin);
  Event<Button, NoType> *OnButtonPressed;
  Event<Button, NoType> *OnButtonReleased;
  // Event *OnButtonPressed;
  void Update();
  bool value;
  bool lastValue;

private:
  bool ButtonPressedPredicate();
  bool ButtonReleasedPredicate();
  int pin;
};
