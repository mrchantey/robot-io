

template <typename dataT>
class FilterZeroAction : public ActionBase<dataT>
{

  public:
    ActionArray<dataT> *onData;

    FilterZeroAction()
    {
        onData = new ActionArray<dataT>();
    }

    void Invoke(dataT data)
    {
        if (data != 0)
            onData->Invoke(data);
    }
};