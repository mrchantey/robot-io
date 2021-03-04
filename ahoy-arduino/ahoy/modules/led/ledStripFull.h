#pragma once

#include "./ledStrip.h"

#define PIN_LED_APA102_CLOCK 14
#define PIN_LED_APA102_DATA 2
#define PIN_LED_SK6812_DATA 0
#define PIN_LED_PWM_R 5
#define PIN_LED_PWM_G 4
#define PIN_LED_PWM_B 3

#include "./ledStrip.h"

enum LED_STRIP_TYPE
{
	LED_STRIP_PWM = 0,
	LED_STRIP_SK6812 = 1,
	LED_STRIP_APA102 = 2
};

class LedStripFull : public LedStrip
{
public:
	// may be possible to point to the original led array
	CRGB ledsRGB_APA102[MAX_LED_COUNT] ={};
	CRGB *ledsRGB_SK6812 = (CRGB *)&leds[0];

	LED_STRIP_TYPE stripType = LED_STRIP_PWM;

	CLEDController *controllerAPA102;
	CLEDController *controllerSK6812;

	LedStripFull()
	{
		pinMode(PIN_LED_APA102_CLOCK, OUTPUT);
		pinMode(PIN_LED_APA102_DATA, OUTPUT);
		pinMode(PIN_LED_SK6812_DATA, OUTPUT);
		pinMode(PIN_LED_PWM_R, OUTPUT);
		pinMode(PIN_LED_PWM_G, OUTPUT);
		pinMode(PIN_LED_PWM_B, OUTPUT);

		controllerAPA102 = &FastLED.addLeds<APA102, PIN_LED_APA102_DATA, PIN_LED_APA102_CLOCK, BGR, DATA_RATE_MHZ(24)>(ledsRGB_APA102, MAX_LED_COUNT);
		controllerSK6812 = &FastLED.addLeds<WS2812, PIN_LED_SK6812_DATA, RGB>(ledsRGB_SK6812, getRGBWsize(MAX_LED_COUNT));

		SetRange(Color::Black());
		RenderAll();
	}

	void SetStripType(LED_STRIP_TYPE _stripType) {
		SetRange(Color::Black());
		RenderAll();
		stripType = _stripType;
	}

	void Render()
	{
		switch (stripType)
		{
		case LED_STRIP_PWM:
			return RenderPWM();
		case LED_STRIP_SK6812:
			return RenderSK6812();
		case LED_STRIP_APA102:
			return RenderAPA102();
		}
	}
	void RenderAll() {
		RenderPWM();
		RenderAPA102();
		RenderSK6812();
	}

	void RenderPWM() {
		analogWrite(PIN_LED_PWM_R, leds[0].r);
		analogWrite(PIN_LED_PWM_G, leds[0].g);
		analogWrite(PIN_LED_PWM_B, leds[0].b);
	}

	void RenderSK6812() {
		controllerSK6812->showLeds();
	}

	void RenderAPA102() {
		for (int i = 0; i < MAX_LED_COUNT; i++)
		{
			ledsRGB_APA102[i].setRGB(leds[i].r, leds[i].g, leds[i].b);
		}
		controllerAPA102->showLeds();
	}

};