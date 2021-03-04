

template <typename dataT>
class ValueChangeAction : public ActionBase<dataT>
{

  public:
    dataT threshold = 10;
    dataT lastData = 0;
    ActionArray<NoType> *onChange;

    ValueChangeAction(dataT _threshold = 10)
    {
        threshold = _threshold;
        onChange = new ActionArray<NoType>();
    }

    void Invoke(dataT data)
    {
        double deltaChange = data - lastData;
        // Serial.println(deltaChange);
        if (abs(deltaChange) > threshold)
        {
            onChange->Invoke(NoType());
            lastData = data;
        }
    }
};