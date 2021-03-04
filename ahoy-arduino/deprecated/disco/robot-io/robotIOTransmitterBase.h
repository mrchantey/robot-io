
class RobotIOTransmitterBase
{

  public:
    bool dataHasUpdated = false;
    ubyte id;

  private:
  public:
    RobotIOTransmitterBase()
    {
    }
    RobotIOTransmitterBase(ubyte _id)
    {
        id = _id;
    }
    virtual void PrintData()
    {
    }
};
