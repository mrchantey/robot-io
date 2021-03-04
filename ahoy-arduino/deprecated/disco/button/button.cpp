#include "button.h"

Button::Button(int _pin)
{
    OnButtonPressed = new Event<Button, NoType>(this, &Button::ButtonPressedPredicate);
    OnButtonReleased = new Event<Button, NoType>(this, &Button::ButtonReleasedPredicate);
    // OnButtonPressed = new Event();
    // OnButtonPressed->predicate = this->ButtonPressedPredicate;
    value = false;
    pin = _pin;
    pinMode(pin, INPUT);
}

bool Button::ButtonPressedPredicate()
{
    return (value == true && lastValue == false);
}

bool Button::ButtonReleasedPredicate()
{
    return (value == false && lastValue == true);
}

void Button::Update()
{
    lastValue = value;
    value = (digitalRead(pin) == 1);
    OnButtonPressed->Update();
    OnButtonReleased->Update();
}