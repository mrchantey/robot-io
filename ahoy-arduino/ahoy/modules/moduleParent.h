#pragma once
#include "./module.h"

template <int NUM_MODULES>
class ModuleParent : public Module
{

public:
	Module *modules[NUM_MODULES];
	static const int numModules = NUM_MODULES;

protected:
	void SetChildren(Module** _modules)
	{
		for (int i = 0; i < numModules; i++)
		{
			modules[i] = _modules[i];
			modules[i]->parent = this;
			modules[i]->childIndex = i;
		}
	}


public:
	void OnUpdate()
	{
		for (int i = 0; i < numModules; i++)
		{
			modules[i]->Update();
		}
	}

	// CLOUD TO DEVICE
	int ParseValues(char **values, int index)
	{
		#ifdef ARDUINO_DEBUG
		Serial.println(String() + "moduleParent - parsing value at index: " + index);
		#endif
		int moduleIndex = atoi(values[index++]);
		if (moduleIndex < numModules)
			return modules[moduleIndex]->ParseValues(values, index);
		else
			return -1;
	}

};