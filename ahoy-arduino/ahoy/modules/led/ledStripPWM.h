#pragma once

#define MAX_LED_COUNT 1
#include "./ledStrip.h"

class LedStripPWM : public LedStrip
{
public:
	byte pinR;
	byte pinG;
	byte pinB;
	LedStripPWM(byte _pinR, byte _pinG, byte _pinB)
	{
		pinR = _pinR;
		pinG = _pinG;
		pinB = _pinB;
		pinMode(pinR, OUTPUT);
		pinMode(pinG, OUTPUT);
		pinMode(pinB, OUTPUT);
	}

	void DoRender()
	{
		analogWrite(pinR, leds[0].r);
		analogWrite(pinG, leds[0].g);
		analogWrite(pinB, leds[0].b);
	}
};