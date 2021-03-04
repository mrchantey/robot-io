#pragma once

#include "../utility/utility.h"
#include "./definitions.h"
#include "./module.h"

#define PIN_RELAY 3

class RelayModule : public Module
{
private:
public:
	byte pinRelay;

	RelayModule()
	{
		pinRelay = PIN_RELAY;
		pinMode(pinRelay, OUTPUT);
		SetEnabled(false);
	}

	void SetEnabled(bool val)
	{
		if (val == true)
			digitalWrite(pinRelay, HIGH);
		else
			digitalWrite(pinRelay, LOW);
	}

	int ParseValues(char **values, int index)
	{
		bool val = atoi(values[index++]) == 0 ? false : true;
		SetEnabled(val);
		return index;
	}
};
