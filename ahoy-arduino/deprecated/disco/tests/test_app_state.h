#include "app_state.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    AppState::Update();
    AppState::Print();
    // delay();
}