// #define MAX_LED_COUNT 5

#include "../ahoy/modules/led/ledStripFull.h"
#include "../ahoy/modules/led/color.h"

LedStripFull *strip;

void setup()
{
	strip = new LedStripFull();
	Serial.begin(115200);
	// Serial.println("\nbeginning led test..");
	strip->SetStripType(LED_STRIP_APA102);
}

void loop()
{
	// strip->SetRange(Color::Cyan());
	// strip->Render();
}