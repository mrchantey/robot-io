#define ARDUINO_DEBUG
#include "../ahoy/motors/motorDualController.h"
#include "../ahoy/dataIO/charReceiver.h"
#include "../ahoy/led/definitions.h"

int pinLF = 5;
int pinLR = 6;
int pinRF = 10;
int pinRR = 11;

MotorDualController *controller;

CharReceiver *charReceiver;

void onValues(char **values)
{
	controller->ParseValuesBuffer(values, 0);
}

void setup()
{
	Serial.begin(115200);
	charReceiver = new CharReceiver();
	controller = new MotorDualController(pinLF, pinLR, pinRF, pinRR);
	charReceiver->onValues = onValues;
	charReceiver->Receive("[32,-0.7]");
	delay(1000);
	charReceiver->Receive("[32,0.7]");
	delay(1000);
	charReceiver->Receive("[32,0]");
}

void loop()
{
	// controller->SetSpeeds(1, 1);
	// 	int count = 100;
	// 	for (int i = 0; i <= count; i++)
	// 	{
	// 		float speed = ((float)i / count) * 2 - 1;
	// #ifdef ARDUINO_DEBUG
	// 		Serial.print("setting speeds: ");
	// 		Serial.println(speed);
	// #endif
	// 		controller->SetSpeeds(speed, speed);
	// 		delay(100);
	// 	}
}