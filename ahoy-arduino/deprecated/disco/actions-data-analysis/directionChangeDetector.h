

template <typename dataT>
class DirectionChangeDetector : public ActionBase<dataT>
{

  public:
    ActionBase<dataT> *onDirectionChange;
    dataT threshold;
    dataT lastData;

    DirectionChangeDetector(dataT _threshold = 0)
    {
        threshold = _threshold;
    }

    void Invoke(dataT newData)
    {
        // Serial.println(newData);
        if (newData >= threshold &&
            newData >= lastData &&
            lastData < threshold)
            onDirectionChange->Invoke(newData);
        lastData = newData;
    }
};