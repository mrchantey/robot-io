
const cstring<10> loopPrefix = cstring<10>("<{\"data\":[");

const uint MAX_TRANSMITTERS = 8;
class RobotIOSystem
{

  public:
    static StaticAction<NoType> *doTransmitData;
    static RobotIOTransmitterBase *transmitters[MAX_TRANSMITTERS];
    static ubyte transmitterIndex;

  private:
    static ubyte uuidCount;
    static bool firstObjectInitialized;

  public:
    static void BeginInitTransmission()
    {
        Serial.print("\r\n<{\"init\":[");
    }

    static ubyte InitChart(const char *name = "Data Chart")
    {
        ubyte id = GetUUID();
        char str[64];
        sprintf(str, "{\"id\":%d,\"type\":\"chart\",\"name\":\"%s\"}", id, name);
        CheckFirstObjectInitialized();
        Serial.print(str);
        return id;
    }

    template <typename dataT>
    static RobotIOTransmitter<dataT> *InitTransmitter(const char *name = "data", const ubyte chartId = 0, const char *tracMode = "lines")
    {
        // Serial.println();
        // Serial.println(chartId);
        if (transmitterIndex >= MAX_TRANSMITTERS)
        {
            Serial.println("max transmitter count reached!");
            return -1;
        }

        ubyte id = GetUUID();
        char str[64];
        sprintf(str, "{\"id\":%d,\"type\":\"trace\",\"name\":\"%s\",\"chartId\":%d}", id, name, chartId);
        CheckFirstObjectInitialized();
        Serial.print(str);
        RobotIOTransmitter<dataT> *transmitter = new RobotIOTransmitter<dataT>(id);
        transmitters[transmitterIndex++] = transmitter;
        return transmitter;
    }

    static void EndInitTransmission()
    {
        Serial.println("]}>");
    }

    static void CheckFirstObjectInitialized()
    {
        if (firstObjectInitialized)
            Serial.print(',');
        else
            firstObjectInitialized = true;
    }

    static ubyte GetUUID()
    {
        return uuidCount++;
    }

    static void TransmitData()
    {
        // Serial.print("transmitting data, index count: ");
        // Serial.print(transmitterIndex);
        // Serial.println();
        if (transmitterIndex == 0)
            return;
        char prefix[38];

        sprintf(prefix, "<{\"timeStamp\":%lu,\"data\":[", LoopSystem::elapsedMillis);
        Serial.print(prefix);

        bool prevTransmitted = false;
        for (int i = 0; i < transmitterIndex; i++)
        {
            if (transmitters[i]->dataHasUpdated)
            {
                // Serial.print("index: ");
                // Serial.print(i);
                // Serial.print("\tprev transmitted: ");
                // Serial.println(prevTransmitted);
                if (prevTransmitted)
                    Serial.print(",");
                else
                    prevTransmitted = true;
                transmitters[i]->PrintData();
            }
        }
        Serial.println("]}>");
    }
};
RobotIOTransmitterBase *RobotIOSystem::transmitters[MAX_TRANSMITTERS] = {};
bool RobotIOSystem::firstObjectInitialized = false;
ubyte RobotIOSystem::uuidCount = 0;
ubyte RobotIOSystem::transmitterIndex = 0;

StaticAction<NoType> *RobotIOSystem::doTransmitData = new StaticAction<NoType>(&RobotIOSystem::TransmitData);