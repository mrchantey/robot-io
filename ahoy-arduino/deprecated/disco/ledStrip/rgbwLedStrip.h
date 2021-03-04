
// SK6812 aka ws2812b RGBW strips
//SK6812 is slightly faster
//fyi https://cpldcpu.wordpress.com/2016/03/09/the-sk6812-another-intelligent-rgb-led/

template <uint ledPin, uint numLeds>
class RgbwLedStrip : public RgbwLedStripBase
{
public:
protected:
    CRGBW leds[numLeds];
    CRGB *ledsRGB = (CRGB *)&leds[0];

public:
    RgbwLedStrip()
    {
        FastLED.addLeds<WS2812, ledPin, RGB>(ledsRGB, getRGBWsize(numLeds));
        for (int i = 0; i < numLeds; i++)
        {
            leds[i] = CRGBW(0, 0, 0, 0);
        }
        FastLED.show();
    }

    void SetLed(uint index, CRGBW col, bool render = true)
    {
        leds[index] = col;
        if (render)
            FastLED.show();
    }

    void SetFromNormal(float val, CRGBW col, bool render = true)
    {
        int index = (int)(val * (numLeds - 1)) % numLeds;
        leds[index] = col;
        if (render)
            FastLED.show();
    }

    void SetAllLeds(CRGBW col, bool render = true)
    {
        for (int i = 0; i < numLeds; i++)
        {
            leds[i] = col;
        }
        if (render)
            FastLED.show();
    }
};