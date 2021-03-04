#pragma once

//could be declared in template
// const ubyte DATA_COUNT = 100;
// template class DataSmoother<int>;
// template class DataSmoother<ubyte>;
template <typename dataT, int DATA_COUNT = 128>
// template <class dataT,int DATA_COUNT>
class SmoothAction : public ActionBase<dataT>
{

public:
  ActionArray<dataT> *onData;

private:
  ubyte currentIndex;
  dataT data[DATA_COUNT];
  double runningTotal;

public:
  SmoothAction()
  {
    // static_assert(DATA_COUNT < 255, "data count too large");
    onData = new ActionArray<dataT>();
    // dataCount = _dataCount;
    currentIndex = 0;
    runningTotal = 0;
    for (int i = 0; i < DATA_COUNT; i++)
    {
      data[i] = 0;
    }
  };

  // void Initialize(dataT initData)
  // {
  //   for (int i = 0; i < DATA_COUNT; i++)
  //   {
  //     UpdateAverage(initData);
  //   }
  // };

  void Invoke(dataT newData)
  {
    currentIndex = (currentIndex + 1) % DATA_COUNT;
    runningTotal -= data[currentIndex];
    runningTotal += newData;
    data[currentIndex] = newData;

    dataT smoothData = runningTotal / DATA_COUNT;
    // Serial.print("\trunning total:");
    // Serial.print(runningTotal);
    // Serial.print("\tsmooth data:");
    // Serial.print(smoothData);
    // Serial.print("\t");
    onData->Invoke(smoothData);
  }
};