#pragma once

#include "./ledPattern.h"
#include "./ledStrip.h"
#include "../definitions.h"

class LedStatusIndicator
{
private:
	LedPattern *pattern;
	LedStrip *strip;

public:
	bool isEnabled = true;

	LedStatusIndicator(LedStrip *_strip)
	{
		strip = _strip;
		pattern = new LedPattern();
		SetStatus(MKEY_AFK);
	}

	void SetStatus(MessageKey status)
	{
		// isEnabled = true;
		switch (status)
		{
		case MKEY_AFK:
			pattern->colorA = Color::Yellow();
			break;
		case MKEY_AWAKE:
			pattern->colorA = Color::Green();
			break;
		case MKEY_WIFI_CONNECTING:
			pattern->colorA = Color::Cyan();
			break;
		case MKEY_MQTT_CONNECTING:
			pattern->colorA = Color::Blue();
			break;
		case MKEY_CONFIG_MODE:
			pattern->colorA = Color::Magenta();
			break;
		case MKEY_OTA_BEGIN:
			pattern->colorA = Color::Red();
			pattern->colorB = Color::Red();
			break;
		case MKEY_OTA_END:
			pattern->colorA = Color::Green();
			pattern->colorB = Color::Green();
			break;
		case MKEY_CONNECTED:
			isEnabled = false;
			pattern->colorA = Color::Black();
			break;
		}
	}

	void Update()
	{
		if (isEnabled)
		{
			strip->leds[0] = pattern->CalculateColor(Vector3());
			strip->leds[1] = pattern->CalculateColor(Vector3());
			strip->leds[2] = pattern->CalculateColor(Vector3());
		}
	}
};
