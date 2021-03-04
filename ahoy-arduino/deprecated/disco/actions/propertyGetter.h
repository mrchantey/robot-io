

template <typename instT, typename dataT>
class PropertyGetter : public ActionBase<instT>
{

public:
  ActionBase<dataT> *onData;
  dataT(instT::*propRef);

  PropertyGetter(dataT(instT::*_propRef))
  {
    propRef = _propRef;
  }

  void Invoke(instT inst)
  {
    onData->Invoke((inst.*propRef));
    // onData->Invoke((*inst.*propRef));
  }
};