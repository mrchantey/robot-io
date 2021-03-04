#include "../ahoy/sensors/hallTachometer.h"

HallTachometer *tach;

void setup()
{
	Serial.begin(115200);
	Serial.println("begin tach test");
	tach = CreateHallTachometer(2);
}

void loop()
{
	tach->Update();
}