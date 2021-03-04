#pragma once

const uint MAX_LOOP_LISTENERS = 16;

class LoopSystem
{
public:
  static bool isRunning;
  static uint delayMillis;
  static ulong elapsedMillis;
  static ulong deltaMillis;
  static ActionArray<NoType, MAX_LOOP_LISTENERS> *onLoop;
  static ulong loopCount;

private:
public:
  static void AddListener(ActionBase<NoType> *listener)
  {
    onLoop->AddAction(listener);
  }

  static void Update()
  {
    if (!isRunning)
      return;
    ulong lastMillis = elapsedMillis;
    elapsedMillis = millis();
    deltaMillis = elapsedMillis - lastMillis;

    onLoop->Invoke(NoType());
    loopCount++;
    delay(delayMillis);
  }
};

class LoopSystemHalt : public ActionBase<NoType>
{

public:
  void Invoke(NoType data)
  {
    LoopSystem::isRunning = false;
  }
};

class PrintLine : public ActionBase<NoType>
{
public:
  void Invoke(NoType data)
  {
    Serial.println();
  }
};

ulong LoopSystem::loopCount = 0;
ulong LoopSystem::elapsedMillis = 0;
ulong LoopSystem::deltaMillis = 0;
bool LoopSystem::isRunning = true;
// bool LoopSystem::doPrint = false;
uint LoopSystem::delayMillis = 0;
ActionArray<NoType, MAX_LOOP_LISTENERS> *LoopSystem::onLoop = new ActionArray<NoType, MAX_LOOP_LISTENERS>();
