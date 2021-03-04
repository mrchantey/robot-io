

class LoopDataLogger : public ActionBase<NoType>
{

  public:
    LoopDataLogger()
    {
        LoopSystem::onLoop->AddAction(this);
    }

    void Invoke(NoType nt = noType)
    {
        String str = String();
        str += "elapsed millis: ";
        str += LoopSystem::elapsedMillis;
        str += "\tdelta millis: ";
        str += LoopSystem::deltaMillis;
        str += "\tloop count: ";
        str += LoopSystem::loopCount;
        str += "\n";
        Serial.print(str);
    }
};