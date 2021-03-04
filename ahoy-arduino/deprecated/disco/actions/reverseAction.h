

template <typename dataT>
class ReverseAction : public ActionBase<dataT>
{

  public:
    dataT max;
    Action<ReverseAction, NoType> *doToggleReverse;
    ActionArray<dataT> *onData;
    bool isReversing;
    ReverseAction(dataT _max = 1)
    {
        max = _max;
        isReversing = false;
        doToggleReverse = new Action<ReverseAction, NoType>(this, &ReverseAction::ToggleReverse);
        onData = new ActionArray<dataT>();
    }

    void ToggleReverse()
    {
        isReversing = !isReversing;
    }

    void Invoke(dataT data)
    {
        dataT newData = isReversing ? (max - data) : data;
        onData->Invoke(newData);
    }
};