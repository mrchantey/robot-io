// #define ARDUINO_DEBUG //uncomment this line for production

#include "../ahoy/ahoy.h"
#include "../ahoy/led/includeLed.h"
#include "../ahoy/dataIO/includeDataIO.h"
#include "../ahoy/dataIO/ledIO.h"

// #include "../ahoy/json/includeJsonLed.h"

LedStripRgbw *ledStrip;
LedControllerRgbw *controller;
DataIO *dataIO;
LedIO *ledIO;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        continue;
    ledStrip = new LedStripRgbw();
    controller = new LedControllerRgbw(ledStrip);

    dataIO = new DataIO();
    ledIO = new LedIO(controller);

    dataIO->onMessage->AddAction(ledIO->doReceiveMessage);

#ifdef ARDUINO_DEBUG
    Serial.println(String() + "BEGIN PROGRAM -  DEBUG MODE");
#endif

    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveByte(MKEY_CONNECTION_CONNECTING);
    // dataIO->ReceiveInt32(DataIO::TERM_END_LONG);

    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveByte(MKEY_LED_INDICIES);
    // dataIO->ReceiveByte(0);
    // dataIO->ReceiveInt16(0);
    // dataIO->ReceiveInt16(12);
    // dataIO->ReceiveInt32(DataIO::TERM_END_LONG);

    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveByte(MKEY_LED_MODE);
    // dataIO->ReceiveByte(0);
    // dataIO->ReceiveByte(ANIM_SOLID);
    // dataIO->ReceiveInt32(DataIO::TERM_END_LONG);

    // dataIO->ReceiveByte(MKEY_LED_COLOR_COUNT);

    // dataIO->ReceiveByte(2);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveByte(MKEY_LED_PERIOD);
    // dataIO->ReceiveByte(0);
    // dataIO->ReceiveFloat(2);
    // dataIO->ReceiveInt32(DataIO::TERM_END_LONG);
    // dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    // dataIO->ReceiveByte(MKEY_LED_SPEED);
    // dataIO->ReceiveByte(0);
    // dataIO->ReceiveFloat(0.1);
    // dataIO->ReceiveInt32(DataIO::TERM_END_LONG);
}

void loop()
{

#ifdef ARDUINO_DEBUG
    // if (LoopSystem::elapsedMillis > 10000)
    // {
    //     dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    //     dataIO->ReceiveByte(MKEY_CONNECTION_CONNECTED);
    //     dataIO->ReceiveInt32(DataIO::TERM_END_LONG);
    // }
    // else if (LoopSystem::elapsedMillis > 5000)
    // {
    //     dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    //     dataIO->ReceiveByte(MKEY_CONNECTION_CONNECTING);
    //     dataIO->ReceiveInt32(DataIO::TERM_END_LONG);
    // }
    // else
    // {
    //     dataIO->ReceiveInt32(DataIO::TERM_START_LONG);
    //     dataIO->ReceiveByte(MKEY_CONNECTION_IDLE);
    //     dataIO->ReceiveInt32(DataIO::TERM_END_LONG);
    // }
#endif
    LoopSystem::Update();
}

// /* TEST*/
// controller->segments[0]->SetIndicies(0, 3);
// controller->segments[0]->animationMode = ANIM_SOLID;
// controller->segments[0]->SetIndicies(0, 6);
// controller->segments[0]->SetWhiteness(0);
// // controller->segments[0]->SetBrightness(0.5);
// controller->segments[0]->SetBrightness(0.1);
// controller->segments[0]->period = 1;
// // controller->segments[0]->fadeStanding = true;
// // controller->segments[0]->fadeSpeed = 0.1;
// controller->segments[0]->speed = 1;
// controller->segments[0]->SetColor(Color(255, 0, 0), 0);
// controller->segments[0]->SetColor(Color(0, 255, 0), 1);
// controller->segments[0]->SetColor(Color(0, 0, 255), 2);
// // controller->segments[0]->SetColor(Color(0, 0, 0, 255), 3);
// // controller->segments[0]->SetColor(Color(0, 0, 255), 1);
// controller->segments[0]->colorsUsed = 3;
// controller->segments[0]->animationMode = ANIM_FADE;
// controller->segments[0]->animationMode = ANIM_RAINBOW;
// controller->segments[1]->SetIndicies(12, 15);
// controller->segments[1]->SetAllColors(Color(0, 255, 0));
// controller->segments[1]->animationMode = ANIM_SOLID;