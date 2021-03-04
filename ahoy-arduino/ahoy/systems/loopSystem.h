// #pragma once

// class LoopSystem
// {
// public:
// 	static unsigned long elapsedMillis;
// 	static unsigned long loopCount;
// 	static unsigned long deltaMillis;

// private:
// public:
// 	static float ElapsedSeconds()
// 	{
// 		return (float)elapsedMillis / 1000;
// 	}
// 	static float DeltaSeconds()
// 	{
// 		return (float)deltaMillis / 1000;
// 	}

// 	static void Update()
// 	{
// 		unsigned long lastMillis = elapsedMillis;
// 		elapsedMillis = millis();
// 		deltaMillis = elapsedMillis - lastMillis;
// 		loopCount++;
// 	}
// };

// unsigned long LoopSystem::loopCount = 0;
// unsigned long LoopSystem::elapsedMillis = 0;
// unsigned long LoopSystem::deltaMillis = 0;
// // Event<NoType, MAX_LOOP_LISTENERS> *LoopSystem::onLoop = new Event<NoType, MAX_LOOP_LISTENERS>();
