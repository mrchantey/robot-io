#pragma once
#include "./moduleParent.h"
#include "./boolModule.h"
#include "./heartbeatModule.h"

class StatusModule;

StatusModule *_statusModule;

class StatusModule : public ModuleParent<2>
{
public:
	BoolModule * enabledModule;
	HeartbeatModule * heartbeatModule;

	StatusModule()
	{
		_statusModule = this;
		enabledModule = new BoolModule();
		heartbeatModule = new HeartbeatModule();
		Module* children[2] ={
			enabledModule,
			heartbeatModule
		};
		SetChildren(children);
	}

};