#pragma once

#include "./ledStrip.h"
#include "./color.h"
#include "../definitions.h"
#include "../../utility/math.h"
#include "../../utility/vector3.h"

class LedPattern
{
public:
	LED_PATTERN_TYPE type;
	LED_SHAPE shape;
	float speed;//cycles / second
	float frequency;//cycles/ meter
	float brightness;
	Color colorA;
	Color colorB;

	LedPattern()
	{
		Reset();
	}

	void Reset()
	{
		type = LED_PATTERN_TYPE_SOLID;
		shape = LED_SHAPE_LINE;
		speed = 1;
		brightness = 1;
		frequency = 1;
		colorA = Color();
		colorB = Color();
	}


	float GetT(Vector3 pos)
	{
		switch (shape)
		{
		case LED_SHAPE_LINE:
			return pos.x * frequency;
		case LED_SHAPE_CIRCLE:
			return pos.Length() * frequency;
		}
	}

	Color GetRawColor(Vector3 pos)
	{
		float time = speed * millis() * 0.001;
		float t = GetT(pos) + time;
		Color col;
		switch (type)
		{
		case LED_PATTERN_TYPE_SOLID:
			return colorA;
		case LED_PATTERN_TYPE_RAINBOW:
			t = fmod(t, 1);
			col = Color::FromHSV(t);
			col.w = colorA.w;
			return col;
		case LED_PATTERN_TYPE_TWOTONE:
			float s = sin(t * TWO_PI) * 0.5 + 0.5;
			return Color::Lerp(colorA, colorB, s);
		}
	}

	Color CalculateColor(Vector3 pos)
	{
		Color raw = GetRawColor(pos);
		return Color::Scale(raw, brightness);
	}

	int ParseValues(char **values, int index = 0)
	{
		// type = static_cast<LED_PATTERN_TYPE>(atoi(values[index++]));
		// brightness = atof(values[index++]);
		// if (type == LED_PATTERN_TYPE_SOLID)
		// {
		// 	colorA.r = atoi(values[index++]);
		// 	colorA.g = atoi(values[index++]);
		// 	colorA.b = atoi(values[index++]);
		// 	colorA.w = atof(values[index++]);
		// }
		// else if (type == LED_PATTERN_TYPE_RAINBOW)
		// {
		// 	shape = static_cast<LED_SHAPE>(atoi(values[index++]));
		// 	frequency = atof(values[index++]);
		// 	speed = atof(values[index++]);
		// 	colorA.w = atof(values[index++]);
		// }
		// else if (type == LED_PATTERN_TYPE_TWOTONE)
		// {
		// 	shape = static_cast<LED_SHAPE>(atoi(values[index++]));
		// 	frequency = atof(values[index++]);
		// 	speed = atof(values[index++]);
		// 	colorA.r = atoi(values[index++]);
		// 	colorA.g = atoi(values[index++]);
		// 	colorA.b = atoi(values[index++]);
		// 	colorA.w = atof(values[index++]);
		// 	colorB.r = atoi(values[index++]);
		// 	colorB.g = atoi(values[index++]);
		// 	colorB.b = atoi(values[index++]);
		// 	colorB.w = atof(values[index++]);
		// }
		return index;
	}
};