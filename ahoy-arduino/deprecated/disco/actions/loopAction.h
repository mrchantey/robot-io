// #pragma once

class LoopAction : public ActionBase<NoType>
{

  public:
    ulong numLoops = 1;
    bool infinite = false;
    ActionArray<NoType> *onLoop;
    ActionArray<NoType> *onEnd;

  private:
    ulong loopCount = 0;

  public:
    LoopAction()
    {
        onLoop = new ActionArray<NoType>();
        onEnd = new ActionArray<NoType>();
        Reset();
    }
    void Reset()
    {
        loopCount = 0;
    }

    void Invoke(NoType data)
    {
        if (loopCount < numLoops || infinite)
        {
            onLoop->Invoke(NoType());
        }
        else
        {
            onEnd->Invoke(NoType());
        }
        loopCount++;
    }
};