#define PIN_SETUP_MODE 4

#include "../ahoy/iotController.h"
//relay pin: D7/13

IotController *iotController;

void setup()
{
#ifdef ARDUINO_DEBUG
	Serial.begin(115200);
	Serial.println();
	Serial.println("Beginning Debug mode");
#endif
	iotController = new IotController();
	iotController->Begin();
}

ulong lastSend = 0;
ulong interval = 10000;

void loop()
{
	iotController->Update();
	const char *data = "hello world";
	long now = millis();
	if (now - lastSend >= interval)
	{
		long nowSecs = now / 1000;
		lastSend = millis();
		iotController->charSender->Serialize(now);
		iotController->charSender->Serialize(nowSecs);
		iotController->charSender->Publish();
	}
}