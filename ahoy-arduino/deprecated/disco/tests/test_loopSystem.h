
#include "disco.h"

LoggerAction *action;

void setup()
{
    Serial.begin(115200);
    Serial.println("initializing");
    action = new LoggerAction("event happened");
    LoopSystem::AddListener(action);
    // LoopSystem::Init();
}

void loop()
{
    LoopSystem::Update();
}
