#pragma once

#include "./led/ledSegmentSet.h"
#include "./led/ledPatternSet.h"
#include "./led/ledStrip.h"
#include "./module.h"

class LedModule : public Module
{
private:
public:
	LedStrip *strip;
	LedPatternSet *patternSet;
	LedSegmentSet *segmentSet;

	bool isEnabled = true;

	LedModule(LedStrip *_strip)
	{
		strip = _strip;
		patternSet = new LedPatternSet();
		segmentSet = new LedSegmentSet();
	}

	void Update()
	{
		if (isEnabled)
			segmentSet->Update(strip, patternSet->patterns[0]); //TODO PATTERN TRANSITION
		else
		{
			strip->SetRange(Color::Black());
		}
		strip->Render();
	}

	int ParseValues(char **values, int index)
	{
		// if (key == MKEY_ENABLE_ALL)
		// 	isEnabled = true;
		// else if (key == MKEY_DISABLE_ALL)
		// 	isEnabled = false;
		// else if (key == MKEY_LED_PATTERNS)
		// 	index = patternSet->ParseValues(values, index);
		// else if (key == MKEY_LED_SEGMENTS)
		// {
		// 	strip->SetRange(Color::Black()); //Any change to led segments, set all to black first
		// 	index = segmentSet->ParseValues(values, index);
		// }
		// return index;
		return index;
	}
};
