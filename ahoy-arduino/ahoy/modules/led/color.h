#pragma once;
#include <FastLED.h>
#include "../../utility/math.h"
// #include <cmath>
/* 
 * Hack to enable SK6812 RGBW strips to work with FastLED.
 *
 * Original code by Jim Bumgardner (http://krazydad.com).
 * Modified by David Madison (http://partsnotincluded.com).
 * https://www.partsnotincluded.com/fastled-rgbw-neopixels-sk6812/
*/

struct Color
{
	union {
		struct
		{
			union {
				uint8_t g;
				uint8_t green;
			};
			union {
				uint8_t r;
				uint8_t red;
			};
			union {
				uint8_t b;
				uint8_t blue;
			};
			union {
				uint8_t w;
				uint8_t white;
			};
		};
		uint8_t raw[4];
	};

	Color()
	{
		r = 0;
		g = 0;
		b = 0;
		w = 0;
	}

	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _w = 0)
	{
		r = _r;
		g = _g;
		b = _b;
		w = _w;
	}

	inline void operator=(const CRGB c) __attribute__((always_inline))
	{
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
		this->white = 0;
	}

	static Color Black()
	{
		return Color(0, 0, 0, 0);
	}
	static Color Red()
	{
		return Color(255, 0, 0, 0);
	}
	static Color Green()
	{
		return Color(0, 255, 0, 0);
	}
	static Color Blue()
	{
		return Color(0, 0, 255, 0);
	}
	static Color Yellow()
	{
		return Color(255, 255, 0, 0);
	}
	static Color Cyan()
	{
		return Color(0, 255, 255, 0);
	}
	static Color Magenta()
	{
		return Color(255, 0, 255, 0);
	}
	static Color White()
	{
		return Color(0, 0, 0, 255);
	}
	static Color FullWhite()
	{
		return Color(255, 255, 255, 255);
	}

	static Color Lerp(Color a, Color b, float t)
	{
		return Color(
			Math::Lerp(a.r, b.r, t),
			Math::Lerp(a.g, b.g, t),
			Math::Lerp(a.b, b.b, t),
			Math::Lerp(a.w, b.w, t));
	}

	static Color Scale(Color col, float t)
	{
		return Color(
			col.r * t,
			col.g * t,
			col.b * t,
			col.w * t);
	}

	static Color FromHSV(float hue, float sat = 1, float val = 1)
	{
		const float incr1 = (float)1 / 6;
		const float incr2 = incr1 * 2;
		const float incr3 = incr1 * 3;
		const float incr4 = incr1 * 4;
		const float incr5 = incr1 * 5;
		const float incr6 = incr1 * 6;

		const int deg = hue * 360;
		const float chroma = val * sat;
		// const int numerator = (hue / incr1) * 1000;
		// const float tempVal = ((float)(numerator % 2000) / 1000) - 1;
		// const float x = chroma * (1 - abs(tempVal));
		const float temp = fmod(deg / 60.0, 2);
		const float x = chroma * (1 - fabs(temp - 1));
		const float m = val - chroma;

		float colR, colB, colG;
		if (hue < incr1)
		{
			colR = chroma;
			colG = x;
			colB = 0;
		}
		else if (hue >= incr1 && hue < incr2)
		{
			colR = x;
			colG = chroma;
			colB = 0;
		}
		else if (hue >= incr2 && hue < incr3)
		{
			colR = 0;
			colG = chroma;
			colB = x;
		}
		else if (hue >= incr3 && hue < incr4)
		{
			colR = 0;
			colG = x;
			colB = chroma;
		}
		else if (hue >= incr4 && hue < incr5)
		{
			colR = x;
			colG = 0;
			colB = chroma;
		}
		else
		{
			colR = chroma;
			colG = 0;
			colB = x;
		}

		colR = (colR + m) * 255;
		colG = (colG + m) * 255;
		colB = (colB + m) * 255;
		return Color(colR, colG, colB);
	}
};

inline uint16_t getRGBWsize(uint16_t nleds)
{
	uint16_t nbytes = nleds * 4;
	if (nbytes % 3 > 0)
		return nbytes / 3 + 1;
	else
		return nbytes / 3;
}