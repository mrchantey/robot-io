#pragma once
#include "discoChannel.h"
#include "colorLight.h"
#include "color.h"
#include "Arduino.h"

class FixedColorChannel : public DiscoChannel
{

  public:
    FixedColorChannel(ColorLight *_colorLight, Color _color)
    {
        colorLight = _colorLight;
        color = _color;
    }
    void Start()
    {

        colorLight->FadeColor(color);
    }

    void End()
    {
        colorLight->FadeColor(Color(0));
    }

  private:
    ColorLight *colorLight;
    Color color;
};