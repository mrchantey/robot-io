#pragma once
#include "./module.h"
#include "../utility/throttle.h"


class HeartbeatModule;

HeartbeatModule * _heartbeatModule;

class HeartbeatModule : public Module {

public:
	Throttle *heartbeat;

	HeartbeatModule() {
		heartbeat = new Throttle(3000);
		heartbeat->onTrigger = HandleHeartbeat;
		_heartbeatModule = this;
	}

	void OnUpdate() {
		heartbeat->Update();
	}

	static void HandleHeartbeat()
	{
		_heartbeatModule->PublishLong(millis());
	}

};