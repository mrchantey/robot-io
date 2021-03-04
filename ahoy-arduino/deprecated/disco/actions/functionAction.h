

template <typename dataT>
class FunctionAction : public ActionBase<dataT>
{

public:
  dataT (*function)(dataT);
  ActionBase<dataT> *onData;

  FunctionAction(dataT (*_function)(dataT))
  {
    function = _function;
  }

  void Invoke(dataT data)
  {
    dataT newData = (*function)(data);
    onData->Invoke(newData);
    // onData->Invoke((inst.*propRef));
    // onData->Invoke((*inst.*propRef));
  }
};