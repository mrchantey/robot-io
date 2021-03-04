#pragma once
#include "../definitions.h"
#include "../../utility/vector3.h"
#include "./ledSegment.h"
#include "./ledStrip.h"
#include "./ledPattern.h"

class LedSegmentSet
{
public:
	static const int MAX_SEGMENTS = 4;
	LedSegment *segments[MAX_SEGMENTS];

	LedSegmentSet()
	{
		for (int i = 0; i < MAX_SEGMENTS; i++)
		{
			segments[i] = new LedSegment();
		}
	}

	void Update(LedStrip *strip, LedPattern *pattern)
	{
		for (int i = 0; i < MAX_SEGMENTS; i++)
		{
			segments[i]->Update(strip, pattern);
		}
	}

	int ParseValues(char **values, int index = 0)
	{
		int numSegments = atoi(values[index++]);
		for (int i = 0; i < MAX_SEGMENTS; i++)
		{
			if (i < numSegments)
				index = segments[i]->ParseValues(values, index);
			else
				segments[i]->Reset();
		}
		return index;
	}
};
