#pragma once
#include "Arduino.h"
#include "discoEvent.h"
#include "button.h"
#include "discoChannel.h"
#include "noType.h"

const int MAX_CHANNELS = 32;

class DiscoChannelSwitcher
{
public:
  DiscoChannelSwitcher(Event<Button, NoType> *OnButtonPressed, DiscoChannel *_channels[], int _numChannels);
  void Update();

private:
  int numChannels;
  DiscoChannel *channels[MAX_CHANNELS] = {};

  int currentChannel = 0;

  Action<DiscoChannelSwitcher, NoType> *buttonPressedAction;
  void SwitchChannel();
};