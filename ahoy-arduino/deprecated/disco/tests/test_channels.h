#pragma once
#include "ColorLightChannelBank.h"
#include "colorLight.h"

ColorLight *colorLight;
ColorLightChannelBank *colorChannels;

void setup()
{
    Serial.begin(115200);
    colorLight = new ColorLight(11, 10, 9);
    colorChannels = new ColorLightChannelBank(colorLight);
    colorChannels->yellowChannel->Start();
}

void loop()
{
    colorLight->Update();
}