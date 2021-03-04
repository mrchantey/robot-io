
#include "./statusModule.h"
#include "./ledModule.h"
#include "./relayModule.h"
#include "./moduleParent.h"

class RootModule;

RootModule * _rootModule;

class RootModule : public ModuleParent<3>
{
public:
	StatusModule *statusModule;
	LedModule *ledModule;
	RelayModule *relayModule;


	void (*onPublishLong)(long) = [](long val) {};
	void (*onPublishDouble)(double)=[](double val) {};

	RootModule()
	{
		_rootModule = this;
		statusModule = new StatusModule();

		statusModule->enabledModule->onChange = HandleStatusSetEnabled;

		relayModule = new RelayModule();
		ledModule = new LedModule();
		Module* children[3] ={
			statusModule,
			relayModule,
			ledModule
		};
		SetChildren(children);
	}

	// CLOUD TO DEVICE
	void HandleOnValues(char **valuesBuffer, int maxIndex)
	{
		int valueIndex = 0;
		while (
			valuesBuffer[valueIndex] != NULL &&
			valueIndex < maxIndex &&
			valueIndex != -1)
		{
			valueIndex = ParseValues(valuesBuffer, valueIndex);
		}
	}

	static void HandleStatusSetEnabled(bool val) {
		for (int i = 1; i < _rootModule->numModules; i++) {
			_rootModule->modules[i]->SetEnabled(val);
		}
	}

	void BeginPublish(int myChildIndex) {
		onPublishLong(myChildIndex);
	}

	void ContinuePublishLong(long val) {
		onPublishLong(val);
	}
	void ContinuePublishDouble(double val) {
		onPublishDouble(val);
	}
};