

#include "../ahoy/modules/ledModule.h"

LedModule *module;


void setup()
{
	Serial.begin(115200);
	module = new LedModule();
}

void loop()
{
	module->Update();
}