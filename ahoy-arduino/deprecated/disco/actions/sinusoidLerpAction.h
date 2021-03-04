

template <typename dataT>
class SinusoidLerpAction : public ActionBase<dataT>
{

  public:
    ActionArray<dataT> *onData;

    SinusoidLerpAction()
    {
        onData = new ActionArray<dataT>();
    }

    void Invoke(dataT data)
    {
        // dataT newData = 0.5 - cos(data * PI) / 2;
        dataT newData = -cos(data * PI) * 0.5 + 0.5;
        onData->Invoke(newData);
    }
};