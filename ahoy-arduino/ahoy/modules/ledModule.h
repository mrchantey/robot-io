#pragma once

#include "./led/ledSegmentSet.h"
#include "./led/ledPatternSet.h"
#include "./led/ledStripFull.h"
#include "./module.h"

class LedModule : public Module
{
private:
public:
	LedStripFull *strip;
	LedPatternSet *patternSet;
	LedSegmentSet *segmentSet;


	LedModule()
	{
		strip = new LedStripFull();
		patternSet = new LedPatternSet();
		segmentSet = new LedSegmentSet();
		segmentSet->segments[0]->ledIndexMax = MAX_LED_COUNT-1;
		patternSet->patterns[0]->colorA = Color::White();
		patternSet->patterns[0]->brightness = 0.2;
		strip->SetStripType(LED_STRIP_SK6812);
		// module->segmentSet->segments[0]->posB = Vector3(1, 0, 0);
	}

	void OnUpdate()
	{
		// #ifdef ARDUINO_DEBUG
		// Serial.println(String() + "ledModule - updating!!");
		// #endif
		segmentSet->Update(strip, patternSet->patterns[0]); //TODO PATTERN TRANSITION
		strip->Render();
	}

	void OnDisable() {
		// #ifdef ARDUINO_DEBUG
		// Serial.println(String() + "ledModule - disabled!");
		// #endif
		strip->SetRange(Color::Black());
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
		return index;
	}
};
