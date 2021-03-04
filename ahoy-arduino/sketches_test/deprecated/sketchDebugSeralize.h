// #define ARDUINO_DEBUG //uncomment this line for production

#include "../ahoy/ahoy.h"
// #include "../ahoy/dataIO/includeDataIO.h"
#include "../ahoy/led/definitions.h"
#include "../ahoy/jsonIO/includeJson.h"

JsonSerializer *serializer;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        continue;
    Serial.println();
    delay(1000);
#ifdef ARDUINO_DEBUG
#endif
    serializer = new JsonSerializer();
    serializer->SerializeMessageI(MKEY_CONNECTION_CONNECTING);
    serializer->PrintToSerial();
    serializer->SerializeMessageIII(MKEY_LED_MODE, 0, ANIM_FADE);
    serializer->PrintToSerial();
    serializer->SerializeMessageIIF(MKEY_LED_SPEED, 0, 3.0);
    serializer->PrintToSerial();
    serializer->SerializeMessageIIII(MKEY_LED_INDICIES, 0, 0, 12);
    serializer->PrintToSerial();
    delay(5000);
    serializer->SerializeMessageI(MKEY_CONNECTION_CONNECTED);
    serializer->PrintToSerial();
}

void loop()
{
    serializer->SerializeMessageIIF(MKEY_LED_SPEED, 0, LoopSystem::ElapsedSeconds());
    serializer->PrintToSerial();
    // LoopSystem::Update();
}
