#include "discoChannelSwitcher.h"

DiscoChannelSwitcher::DiscoChannelSwitcher(Event<Button, NoType> *OnButtonPressed, DiscoChannel *_channels[], int _numChannels)
{
    numChannels = _numChannels;
    for (int i = 0; i < numChannels; i++)
    {
        channels[i] = _channels[i];
    }
    // channels = _channels;
    currentChannel = 0;
    buttonPressedAction = new Action<DiscoChannelSwitcher, NoType>(this, &DiscoChannelSwitcher::SwitchChannel);
    OnButtonPressed->action = buttonPressedAction;
}

void DiscoChannelSwitcher::SwitchChannel()
{
    channels[currentChannel]->End();
    ++currentChannel = currentChannel % numChannels;
    Serial.print("switching channels to ");
    Serial.println(currentChannel);
    channels[currentChannel]->Start();
}

void DiscoChannelSwitcher::Update()
{
    channels[currentChannel]->Update();
}