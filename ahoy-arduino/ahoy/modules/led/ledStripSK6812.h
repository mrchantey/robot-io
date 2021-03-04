#include "./ledStrip.h"

// SK6812 aka ws2812b RGBW strips
//SK6812 is slightly faster
//fyi https://cpldcpu.wordpress.com/2016/03/09/the-sk6812-another-intelligent-rgb-led/

//3 wire interrupt problems
//https://github.com/FastLED/FastLED/wiki/Interrupt-problems

//WS2812 led data takes 30µs per pixel. If you have 100 pixels, then that means interrupts will be disabled for 3000µs, or 3ms.
#ifndef PIN_SK6812_DATA
#define PIN_SK6812_DATA 3
#endif
class LedStripSK6812 : public LedStrip
{
public:
	CRGB *ledsRGB = (CRGB *)&leds[0];

	LedStripSK6812()
	{
		pinMode(PIN_SK6812_DATA, OUTPUT);
		FastLED.addLeds<WS2812, PIN_SK6812_DATA, RGB>(ledsRGB, getRGBWsize(MAX_LED_COUNT));
	}

	void DoRender()
	{
		FastLED.show();
	}
};