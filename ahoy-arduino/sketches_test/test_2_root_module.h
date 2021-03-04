
#include "../ahoy/modules/rootModule.h"


static void HandlePublish(long val) {
	#ifdef ARDUINO_DEBUG
	Serial.println(String() + "test_2_root_module - val: " + val);
	#endif
}
static void HandlePublish(double val) {
	#ifdef ARDUINO_DEBUG
	Serial.println(String() + "test_2_root_module - val: " + val);
	#endif
}

RootModule *rootModule;

void setup() {
	Serial.begin(115200);
	Serial.println();
	rootModule = new RootModule();
	rootModule->onPublishDouble = HandlePublish;
	rootModule->onPublishLong = HandlePublish;
}

void loop() {
	rootModule->Update();
}
