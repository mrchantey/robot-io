#pragma once

#include "./ledStrip.h"


//APA102 clones called SK9822

// Uno clock = 13
// Uno data = 11
// apa clock next to -
// apa data next to +

#ifndef APA102_CLOCK_PIN
#define APA102_CLOCK_PIN 5
#endif
#ifndef APA102_DATA_PIN
#define APA102_DATA_PIN 4
#endif

#include "./ledStrip.h"
// APA102 LEDS, the very fast rgb ones

class LedStripAPA102 : public LedStrip
{
public:
	// may be possible to point to the original led array
	CRGB ledsRGB[MAX_LED_COUNT];

	// LedStripAPA102(NoType tt) : LedStrip()
	LedStripAPA102()
	{
		pinMode(APA102_CLOCK_PIN, OUTPUT);
		pinMode(APA102_DATA_PIN, OUTPUT);
		// FastLED.addLeds<APA102>(ledsRGB, LedStrip::MAX_LED_COUNT);
		//reverse led order
		FastLED.addLeds<APA102, APA102_DATA_PIN, APA102_CLOCK_PIN, BGR, DATA_RATE_MHZ(24)>(ledsRGB, MAX_LED_COUNT);
	}

	void DoRender()
	{
		for (int i = 0; i < MAX_LED_COUNT; i++)
		{
			int r = leds[i].r;
			int g = leds[i].g;
			int b = leds[i].b;
			ledsRGB[i].setRGB(r, g, b);
		}
		FastLED.show();
	}
};