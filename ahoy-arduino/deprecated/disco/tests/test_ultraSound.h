#pragma once
// #include "ultraSound.h"
// #include "smoothAction.h"
UltraSound *ultraSound;
SmoothAction<ulong> *smoothAction;

void setup()
{
    Serial.begin(115200);
    Serial.println("initializing");
    ultraSound = new UltraSound(4, 2);
    ultraSound->onData->AddAction(new DataLogger<ulong>("distance: "));
    // ultraSound->onData->AddAction(new DataLogger<ulong>("distance: ", true));

    smoothAction = new SmoothAction<ulong>();
    ultraSound->onData->AddAction(smoothAction);
    smoothAction->onData->AddAction(new DataLogger<ulong>("smooth distance: ", true));

    // for (int i = 0; i < 1000; i++)
    // {
    //     Serial.print("distance: ");
    //     Serial.println(ultraSound->Invoke(NoType()));
    // }
}
