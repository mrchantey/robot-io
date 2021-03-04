

template <typename dataT>
class DataGetterAction : ActionBase<NoType>
{
  public:
    // ActionArray<dataT> *onData;
    ActionBase<dataT> *onData;

    DataGetterAction(bool autoRepeat = true)
    {
        // onData = new ActionArray<dataT>();
        if (autoRepeat)
            LoopSystem::AddListener(this);
    }
};