
#include "button.h"
#include "discoChannelSwitcher.h"
#include "ColorLightChannelBank.h"
#include "colorLight.h"

ColorLight *colorLight;
ColorLightChannelBank *colorLightChannels;
Button *channelSwitchButton;
DiscoChannelSwitcher *channelSwitcher;

void setup()
{
    Serial.begin(115200);
    colorLight = new ColorLight(11, 10, 9);
    colorLightChannels = new ColorLightChannelBank(colorLight);
    channelSwitchButton = new Button(12);

    const int numChannels = 8;
    DiscoChannel *channels[numChannels] = {
        colorLightChannels->blackChannel,
        colorLightChannels->whiteChannel,
        colorLightChannels->redChannel,
        colorLightChannels->greenChannel,
        colorLightChannels->blueChannel,
        colorLightChannels->yellowChannel,
        colorLightChannels->magentaChannel,
        colorLightChannels->cyanChannel};

    channelSwitcher = new DiscoChannelSwitcher(channelSwitchButton->OnButtonPressed, channels, numChannels);
}

void loop()
{
    channelSwitchButton->Update();
    colorLight->Update();
}