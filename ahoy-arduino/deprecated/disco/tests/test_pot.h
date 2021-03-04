
#include "pot.h"
#include "ArduinoEventSubscriber.h"

Pot *pot;
LoggerEventSubscriber *sub;
// ArduinoEventSubscriberTemplate<EventLogger>

void setup()
{
    Serial.begin(115200);
    pot = new Pot(A0);
    sub = new LoggerEventSubscriber("Pot Value Changed");
    pot->OnValueChanged->subscriber = sub;
}

void loop()
{
    pot->Update();
    Serial.println(pot->value);
}