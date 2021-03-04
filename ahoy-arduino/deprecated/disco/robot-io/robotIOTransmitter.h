

template <typename dataT>
class RobotIOTransmitter : public RobotIOTransmitterBase
{

  public:
  private:
    dataT data;

  public:
    Action<RobotIOTransmitter, dataT> *doUpdateData;
    RobotIOTransmitter(ubyte _id) : RobotIOTransmitterBase(_id)
    {
        doUpdateData = new Action<RobotIOTransmitter, dataT>(this, &RobotIOTransmitter::UpdateData);
    }

    void UpdateData(dataT newData)
    {
        data = newData;
        dataHasUpdated = true;
    }

    void PrintData()
    {
        if (!dataHasUpdated)
            return;
        char str[32];
        sprintf(str, "{\"id\":%d,\"value\":%d}", id, data);
        Serial.print(str);
        dataHasUpdated = false;
    }
};