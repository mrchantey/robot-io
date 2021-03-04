#pragma once
#include "./color.h"
//base class for SK812, WS2812, APA102 & pwm
#ifndef MAX_LED_COUNT
#define MAX_LED_COUNT 127
#endif

class LedStrip
{
protected:
public:
	Color leds[MAX_LED_COUNT] ={};

	void SetRange(Color col, int imin = 0, int imax = MAX_LED_COUNT)
	{
		for (int i = imin; i < imax; i++)
		{
			leds[i] = col;
		}
	}

	virtual	void Render() = 0;

};