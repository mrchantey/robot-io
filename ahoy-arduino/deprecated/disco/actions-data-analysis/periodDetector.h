

template <typename dataT>
class PeriodDetector : public ActionBase<dataT>
{

  public:
    ActionBase<ulong> *onUpdate;
    ulong lastPeriodMillis;
    PeriodDetector()
    {
        lastPeriodMillis = LoopSystem::elapsedMillis;
    }

    void Invoke(dataT newData)
    {
        ulong periodMillis = LoopSystem::elapsedMillis - lastPeriodMillis;
        onUpdate->Invoke(periodMillis);
    }
};