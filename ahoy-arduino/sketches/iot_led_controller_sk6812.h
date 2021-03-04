#define PIN_SK6812_DATA 13
#define PIN_SETUP_MODE 4
#define MAX_LED_COUNT 300

#include "../ahoy/iotController.h"
#include "../ahoy/led/ledStripSK6812.h"
#include "../ahoy/led/ledController.h"

IotController *iotController;
LedStripSK6812 *strip;
LedController *ledController;

void setup()
{
	Serial.begin(115200);
#ifdef ARDUINO_DEBUG
	Serial.println();
	Serial.println("Beginning Debug mode");
#endif
	strip = new LedStripSK6812();
	ledController = new LedController(strip);
	iotController = new IotController();
	iotController->charReceiver->ledController = ledController;
	iotController->Begin();
}

void loop()
{
	iotController->Update();
	ledController->Update();
}