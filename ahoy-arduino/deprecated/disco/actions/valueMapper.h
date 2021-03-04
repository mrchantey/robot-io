

template <typename dataT1, typename dataT2>
class ValueMapper : public ActionBase<dataT1>
{

public:
  dataT1 min1;
  dataT1 max1;
  dataT2 min2;
  dataT2 max2;
  ActionBase<dataT2> *onData;

  ValueMapper(dataT1 _min1, dataT1 _max1, dataT2 _min2, dataT2 _max2)
  {
    min1 = _min1;
    max1 = _max1;
    min2 = _min2;
    max2 = _max2;
  }

  void Invoke(dataT1 data)
  {
    dataT2 newData = Math::Map(data, min1, max1, min2, max2);
    onData->Invoke(newData);
    // onData->Invoke((inst.*propRef));
    // onData->Invoke((*inst.*propRef));
  }
};