#include "pot.h"

const int MIN_VALUE_DELTA = 2;

Pot::Pot(int _pin)
{
    OnValueChanged = new ArduinoEvent<Pot>(this, &Pot::ValueChangedPredicate);
    pin = _pin;
    pinMode(pin, INPUT);
    value = analogRead(pin);
}

bool Pot::ValueChangedPredicate()
{
    return (abs(value - lastValue) >= MIN_VALUE_DELTA);
}

void Pot::Update()
{
    lastValue = value;
    value = analogRead(pin);
    OnValueChanged->Update();
}
