#pragma once

#include "./module.h"

class BoolModule : public Module {
public:
	void (*onChange)(bool) = [](bool val) {};

	int ParseValues(char **values, int index)
	{
		bool val = atoi(values[index++]) == 0 ? false : true;
		#ifdef ARDUINO_DEBUG
		Serial.println(String() + "boolModule - val: "+ val);
		#endif
		onChange(val);
		return index;
	}
};