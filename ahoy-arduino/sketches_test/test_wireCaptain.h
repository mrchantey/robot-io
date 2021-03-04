#define ARDUINO_DEBUG

#include "../ahoy/dataIO/wireCaptain.h"

#define SAILOR_ADDRESS 8

WireCaptain *captain;

// String testStr = "[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33]"; //92

void setup()
{
	Serial.begin(115200);
	Serial.println();
	Serial.println("Begin wire captain test");
	captain = InitializeWireCaptain(4, 2);
	// captain->Set(testStr);
	captain->SetAndSendAll("[32,0.7]");
	delay(1000);
	captain->SetAndSendAll("[32,-0.7]");
	delay(1000);
	captain->SetAndSendAll("[32,0]");
}

void loop()
{
	// captain->Send(SAILOR_ADDRESS);
	// delay(3000);
}