
#include "./ledStrip.h"
#include "./color.h"
#include "./ledPattern.h"
#include "../definitions.h"
#include "../../utility/math.h"
#include "../../utility/vector3.h"

class LedPatternSet
{
public:
	static const int MAX_PATTERNS = 1;
	LedPattern *patterns[MAX_PATTERNS];

	// LedPattern *currentPattern

	LedPatternSet()
	{
		for (int i = 0; i < MAX_PATTERNS; i++)
		{
			patterns[i] = new LedPattern();
		}
	}
	int ParseValues(char **values, int index = 0)
	{
		int numPatterns = atoi(values[index++]);
		for (int i = 0; i < MAX_PATTERNS; i++)
		{
			if (i < numPatterns)
				index = patterns[i]->ParseValues(values, index);
			else
				patterns[i]->Reset();
		}
		return index;
	}
};