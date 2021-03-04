

class TimeLapseAction : public ActionBase<NoType>
{
  public:
    ActionArray<NoType> *onEnd;
    ActionArray<float> *onUpdate;
    Action<TimeLapseAction, NoType> *doReset;
    ulong durationMillis;

  private:
    ulong startMillis;
    bool isRunning = false;

  public:
    TimeLapseAction()
    {
        durationMillis = 1000;

        LoopSystem::AddListener(this);
        doReset = new Action<TimeLapseAction, NoType>(this, &TimeLapseAction::Reset);
        onEnd = new ActionArray<NoType>();
        onUpdate = new ActionArray<float>();
    }

    void Start()
    {
        Reset();
    }

    void Reset()
    {
        isRunning = true;
        startMillis = millis();
    }

    void Invoke(NoType data)
    {
        if (!isRunning)
            return;
        ulong elapsedMillis = millis() - startMillis;
        float t = (float)elapsedMillis / durationMillis;
        // Serial.print("time lapsing: ");
        // Serial.print(t);
        // Serial.print("\t");
        if (t >= 1)
        {
            isRunning = false;
            startMillis = -1;
            onEnd->Invoke(NoType());
        }
        else
        {
            onUpdate->Invoke(t);
        }
    }
};