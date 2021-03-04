#define PIN_SETUP_MODE 4

#include "../ahoy/iotController.h"
#include "../ahoy/modules/relayController.h"
//relay pin: D7/13

IotController *iotController;
RelayController *relayController;

void setup()
{
#ifdef ARDUINO_DEBUG
	Serial.begin(115200);
	Serial.println();
	Serial.println("Beginning Debug mode");
#endif
	relayController = new RelayController(13);
	iotController = new IotController();
	iotController->charReceiver->relayController = relayController;
	iotController->Begin();
}

void loop()
{
	iotController->Update();
}