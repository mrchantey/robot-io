#pragma once

#include "./ledStrip.h"
#include "./ledPattern.h"
#include "../definitions.h"
#include "../../utility/vector3.h"

class LedSegment
{
private:
public:
	LED_SHAPE shape = LED_SHAPE_LINE;
	int ledIndexMin = 0;
	int ledIndexMax = 0;
	Vector3 posA = Vector3();
	Vector3 posB = Vector3();
	float radius;

public:
	LedSegment()
	{
	}

	void Reset()
	{
		shape = LED_SHAPE_LINE;
		ledIndexMin = 0;
		ledIndexMax = 0;
		posA = Vector3();
		posB = Vector3();
	}

	//TODO Implement Circle Shape

	void Update(LedStrip *strip, LedPattern *pattern)
	{
		int max = ledIndexMax < (MAX_LED_COUNT - 1) ? ledIndexMax : MAX_LED_COUNT - 1;
		int denomenator = (ledIndexMax - ledIndexMin - 1);
		for (int i = ledIndexMin; i <= max; i++)
		{
			float t = denomenator == 0 ? 0 : (float)(i - ledIndexMin) / denomenator;
			Vector3 pos = Vector3::Lerp(posA, posB, t);
			// Serial.print(String() + "x: " + pos.x + " y: " + pos.y + "z: " + pos.z + "\t");
			strip->leds[i] = pattern->CalculateColor(pos);
		}
	}

	int ParseValues(char **values, int index = 0)
	{
		// shape = static_cast<LED_SHAPE>(atoi(values[index++]));
		// ledIndexMin = atoi(values[index++]);
		// ledIndexMax = atoi(values[index++]);
		// posA.x = atof(values[index++]);
		// posA.y = atof(values[index++]);
		// posA.z = atof(values[index++]);
		// posB.x = atof(values[index++]);
		// posB.y = atof(values[index++]);
		// posB.z = atof(values[index++]);
		// if (shape == LED_SHAPE_LINE)
		// {
		// }
		// else if (shape == LED_SHAPE_CIRCLE)
		// {
		// 	radius = atof(values[index++]);
		// }

		return index;
	}
};
