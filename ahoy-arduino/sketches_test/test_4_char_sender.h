
#include "../ahoy/modules/rootModule.h"
#include "../ahoy/dataIO/charSender.h"


RootModule *rootModule;
CharSender *charSender;

static void HandlePublishTelemetry(char *data, int length)
{
	#ifdef ARDUINO_DEBUG
	// String data = String(data,)
	Serial.println("publishing data!");
	Serial.println(String() + "test_3_char_sender - data: " + data);
	#endif
}

static void HandlePublish(long val) {
	charSender->Serialize(val);
}
static void HandlePublish(double val) {
	charSender->Serialize(val);
}


void setup() {
	Serial.begin(115200);
	Serial.println();
	Serial.println("TEST 3");
	rootModule = new RootModule();
	rootModule->onPublishDouble = HandlePublish;
	rootModule->onPublishLong = HandlePublish;

	charSender = new CharSender();
	charSender->onPublish = HandlePublishTelemetry;
}

void loop() {
	rootModule->Update();
	charSender->Publish();
}