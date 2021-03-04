// #define ARDUINO_DEBUG //uncomment this line for production

#include "../ahoy/ahoy.h"
#include "../ahoy/led/includeLed.h"

LedStripRgbw *ledStrip;
LedControllerRgbw *controller;

void setup()
{
    ledStrip = new LedStripRgbw();
    controller = new LedControllerRgbw(ledStrip);
    controller->segments[0]->SetIndicies(2, 68);
    controller->segments[0]->SetBrightness(1);

    // controller->segments[0]->SetWhiteness(0);
    // controller->segments[0]->animationMode = ANIM_SOLID;
    controller->segments[0]->animationMode = ANIM_RAINBOW;
    // controller->segments[0]->colorsUsed = 2;
    // controller->segments[0]->SetColor(Color::Green(), 0);
    // controller->segments[0]->SetColor(Color::Blue(), 1);
    controller->segments[0]->speed = 4;
    // controller->segments[0]->period = 2;
    // controller->segments[0]->period = 1;
}

void loop()
{
    LoopSystem::Update();
}
