
#include "../ahoy/led/ledStripAPA102.h" //when done testing do not include
#include "../ahoy/led/ledController.h"

LedController *controller;
LedStripAPA102 *strip;

void setup()
{
    Serial.begin(115200);
    strip = new LedStripAPA102();
    controller = new LedController(strip);

    controller->segments[0]->SetIndicies(0, 6);
    // controller->segments[0]->SetBrightness(1);
    // controller->segments[0]->animationMode = ANIM_RAINBOW;
    controller->segments[0]->animationMode = ANIM_SOLID;
    controller->segments[0]->colorsUsed = 1;
    controller->segments[0]->speed = 1;
    controller->segments[0]->SetWhiteness(255);
    controller->segments[0]->SetColor(Color::Blue(), 0);
}

void loop()
{
    LoopSystem::Update();
}