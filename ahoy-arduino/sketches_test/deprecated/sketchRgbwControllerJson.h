// #define ARDUINO_DEBUG //uncomment this line for production

// #include "../ahoy/ahoy.h"
#include "../ahoy/led/includeLed.h"
#include "../ahoy/jsonIO/jsonDeserializer.h"
#include "../ahoy/jsonIO/jsonSerializer.h"
#include "../ahoy/jsonIO/ledIO.h"

LedStripRgbw *ledStrip;
LedControllerRgbw *controller;
JsonDeserializer *jsonDeserializer;
#ifdef ARDUINO_DEBUG
JsonSerializer *serializer;
#endif
LedIO *ledIO;

void setup()
{
    Serial.begin(115200);
    // Serial.setTimeout(10);
    while (!Serial)
        continue;
    ledStrip = new LedStripRgbw();
    controller = new LedControllerRgbw(ledStrip);

    jsonDeserializer = new JsonDeserializer();
    ledIO = new LedIO(controller);

    jsonDeserializer->onMessage->AddAction(new Action<LedIO, char **>(ledIO, &LedIO::ReceiveMessage));

    // controller->segments[0]->SetIndicies(0, 6);
    controller->segments[0]->SetIndicies(0, 114);
    controller->segments[0]->SetBrightness(1);

    controller->segments[0]->SetWhiteness(64);
    controller->segments[0]->animationMode = ANIM_FADE;
    controller->segments[0]->colorsUsed = 2;
    controller->segments[0]->SetColor(Color::Green(), 0);
    controller->segments[0]->SetColor(Color::Blue(), 1);
    controller->segments[0]->speed = 2;
    controller->segments[0]->period = 2;
#ifdef ARDUINO_DEBUG
    Serial.println(String() + "DEBUG");
    // Serial.println(RemainingMemory());
    serializer = new JsonSerializer();
    Serial.println(String() + "MEM: " + RemainingMemory());
    // serializer->BeginSerializeMessage();
    // serializer->Serialize(MKEY_LED_SET_COLOR);
    // serializer->Serialize(0);   //segment
    // serializer->Serialize(0);   //color index
    // serializer->Serialize(255); //r
    // serializer->Serialize(0);   //g
    // serializer->Serialize(0);   //b
    // serializer->Serialize(0);   //w
    // serializer->EndSerializeMessage();
    // jsonDeserializer->Receive(serializer->buffer);
    serializer->BeginSerializeMessage();
    serializer->Serialize(MKEY_CONNECTION_CONNECTING);
    serializer->EndSerializeMessage();
    jsonDeserializer->Receive(serializer->buffer);
#endif
}

void loop()
{

#ifdef ARDUINO_DEBUG
    if (LoopSystem::loopCount == 100)
    {
        serializer->BeginSerializeMessage();
        serializer->Serialize(MKEY_CONNECTION_CONNECTED);
        serializer->EndSerializeMessage();
        jsonDeserializer->Receive(serializer->buffer);
        Serial.println();
    }
#endif
    LoopSystem::Update();
}
