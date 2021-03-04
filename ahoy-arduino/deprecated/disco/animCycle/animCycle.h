
// #pragma once
// // #include "disco.h"

// class AnimCycle
// {

// public:
//   //calling start will cleanly restart the animation
//   ActionBase<NoType> *endListener;
//   AnimActionBase *animAction;
//   Action<AnimCycle, NoType> *onUpdate;
//   ubyte numLoops = 1;
//   bool infinite = false;
//   bool toggleReverse = true;
//   unsigned long durationMillis = 0;

// private:
//   ubyte loopCount = 0;
//   bool isAnimating = false;
//   bool reverse = false;
//   unsigned long startMillis = 0;

// public:
//   // AnimCycle()
//   // {
//   // }
//   AnimCycle(AnimActionBase *_animAction)
//   {
//     animAction = _animAction;
//     onUpdate = new Action<AnimCycle, NoType>(this, &AnimCycle::Update);
//     LoopSystem::AddListener(onUpdate);
//   }

//   void Start(unsigned long _durationMillis = 1000, bool _reverse = false)
//   {
//     loopCount = 0;
//     startMillis = millis();
//     durationMillis = _durationMillis;
//     isAnimating = true;
//     reverse = _reverse;
//   }

//   void Update()
//   {
//     // Serial.println("updating..");
//     if (!isAnimating)
//       return;
//     unsigned long elapsedMillis = millis() - startMillis;
//     float linearT = (float)elapsedMillis / durationMillis;
//     linearT = reverse ? 1 - linearT : linearT;

//     float t = 0.5 - cos(linearT * PI) / 2;
//     Serial.print("in animation update\t");
//     Serial.print(t);
//     Serial.print("\t");
//     // Serial.print("reverse:");
//     // Serial.println();
//     if ((reverse && linearT <= 0) || (!reverse && linearT >= 1))
//       EndCycle();
//     else
//       animAction->Animate(t);
//   }

//   void EndCycle()
//   {
//     loopCount++;
//     Serial.println(loopCount);
//     if (infinite || loopCount < numLoops)
//     {
//       if (toggleReverse)
//         reverse = !reverse;
//       startMillis = millis();
//     }
//     else
//     {
//       Stop();
//     }
//     // Serial.println();
//   }

//   void Stop()
//   {
//     loopCount = 0;
//     startMillis = 0;
//     durationMillis = 0;
//     isAnimating = false;
//     Serial.println("animation ended");
//     if (endListener != NULL)
//       endListener->Invoke(NoType());
//   }
// };