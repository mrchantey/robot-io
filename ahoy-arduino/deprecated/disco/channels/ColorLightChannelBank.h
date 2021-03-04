#pragma once
#include "discoChannel.h"
#include "colorLight.h"
#include "fixedColorChannel.h"

class ColorLightChannelBank
{
  public:
    FixedColorChannel *blackChannel;
    FixedColorChannel *whiteChannel;
    FixedColorChannel *redChannel;
    FixedColorChannel *greenChannel;
    FixedColorChannel *blueChannel;
    FixedColorChannel *yellowChannel;
    FixedColorChannel *magentaChannel;
    FixedColorChannel *cyanChannel;
    ColorLightChannelBank(ColorLight *_colorLight)
    {
        blackChannel = new FixedColorChannel(_colorLight, Color(0, 0, 0));
        whiteChannel = new FixedColorChannel(_colorLight, Color(255, 255, 255));
        redChannel = new FixedColorChannel(_colorLight, Color(255, 0, 0));
        greenChannel = new FixedColorChannel(_colorLight, Color(0, 255, 0));
        blueChannel = new FixedColorChannel(_colorLight, Color(0, 0, 255));
        yellowChannel = new FixedColorChannel(_colorLight, Color(255, 255, 0));
        magentaChannel = new FixedColorChannel(_colorLight, Color(255, 0, 255));
        cyanChannel = new FixedColorChannel(_colorLight, Color(0, 255, 255));
    }
};
