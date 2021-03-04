
#include "discoEvent.h"
#include "discoAction.h"

#include "noType.h"
class Pirate
{
  public:
    bool HasStartedSailing()
    {
        return true;
    }
    NoType SomeValueGetter()
    {
        return NoType();
    }
};

Pirate *pirate;
Event<Pirate, NoType> *event;
LoggerAction *action;

void setup()
{
    Serial.begin(115200);
    // Serial.begin(9600);
    // Serial.println("begin");
    pirate = new Pirate();
    action = new LoggerAction("Bang woo");
    event = new Event<Pirate, NoType>(pirate, &Pirate::HasStartedSailing);
    event->action = action;
    event->Update();
}

void loop()
{
}