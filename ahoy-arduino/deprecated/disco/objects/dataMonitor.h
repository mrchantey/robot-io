

template <typename dataT>
class DataMonitor
{

public:
  DataGetterAction<dataT> *dataGetter;
  SmoothAction<dataT> *smoothAction;
  ValueChangeAction<dataT> *valueChangeAction;
  FilterZeroAction<dataT> *filterZeroAction;

private:
public:
  DataMonitor(DataGetterAction<dataT> *_dataGetter)
  {
    dataGetter = _dataGetter;

    filterZeroAction = new FilterZeroAction<dataT>();
    dataGetter->onData->AddAction(filterZeroAction);
    // filterZeroAction->onData->AddAction(new DataLogger<ulong>("distance: "));

    smoothAction = new SmoothAction<dataT>();
    filterZeroAction->onData->AddAction(smoothAction);
    // smoothAction->onData->AddAction(new DataLogger<ulong>("smooth distance: ", true));

    valueChangeAction = new ValueChangeAction<dataT>(20);
    smoothAction->onData->AddAction(valueChangeAction);
    valueChangeAction->onChange->AddAction(new Logger("value changed", true));
  }
};