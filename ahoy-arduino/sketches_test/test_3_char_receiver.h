
#include "../ahoy/modules/rootModule.h"
#include "../ahoy/dataIO/charReceiver.h"


RootModule *rootModule;
CharReceiver * charReceiver;

void HandleOnValues(char **values, int maxIndex) {
	rootModule->HandleOnValues(values, maxIndex);
}


void setup() {
	Serial.begin(115200);
	Serial.println();
	rootModule = new RootModule();

	charReceiver = new CharReceiver();
	charReceiver->onValues = HandleOnValues;
}

void loop() {
	charReceiver->Receive("[0,0,1]");
	rootModule->Update();
	delay(5000);
	charReceiver->Receive("[0,0,0]");
	rootModule->Update();
	delay(5000);
}
