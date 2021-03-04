#pragma once

class Throttle
{

public:
	ulong lastTrigger;
	ulong interval;

	void (*onTrigger)();

	Throttle(int _interval = 60000)
	{
		lastTrigger = 0;
		interval = _interval;
	}

	void Update()
	{
		long now = millis();
		if (now - lastTrigger >= interval)
		{
			lastTrigger = now;
			onTrigger();
		}
	}
};
