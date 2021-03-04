#define PIN_RED 15
#define PIN_GREEN 13
#define PIN_BLUE 12

#include "../ahoy/led/color.h"
#include "../ahoy/led/ledStripPWM.h"
// #include "../ahoy/led/ledController.h"

// LedController *controller;
LedStripPWM *strip;

void setup()
{
	Serial.begin(115200);
	strip = new LedStripPWM();
	// controller = new LedController(strip);
	delay(1000);
	strip->SetRange(Color(255, 0, 0));
	strip->Render();
	delay(3000);
	strip->SetRange(Color(0, 255, 0));
	strip->Render();
	delay(2000);
	strip->SetRange(Color(0, 0, 255));
	strip->Render();
	delay(1000);
	strip->SetRange(Color(0, 0, 0));
	strip->Render();
	// controller->segments[0]->SetIndicies(0, 6);
	// // controller->segments[0]->SetBrightness(1);
	// // controller->segments[0]->animationMode = ANIM_RAINBOW;
	// controller->segments[0]->animationMode = ANIM_SOLID;
	// controller->segments[0]->colorsUsed = 1;
	// controller->segments[0]->speed = 1;
	// controller->segments[0]->SetWhiteness(255);
	// controller->segments[0]->SetColor(Color::Blue(), 0);
}

void loop()
{
	// LoopSystem::Update();
}