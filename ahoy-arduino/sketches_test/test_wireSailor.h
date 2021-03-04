#include "../ahoy/dataIO/charReceiver.h"
#define ARDUINO_DEBUG

CharReceiver *receiver;

void setup()
{
	Serial.begin(115200);
#ifdef ARDUINO_DEBUG
	receiver = InitializeWireCharReceiver();
	Serial.println("Begin wire sailor test");
#endif
}

void loop()
{
	delay(100);
}