

class RadioTransmitter
{

  public:
    static StaticAction<String> *doTransmit;

    static void Init()
    {
        Radio::Init();
        Serial.println("radio transmitter initialized");
    }

    static void Transmit(String data)
    {

        int len = data.length();

        Serial.print("transmitting data: ");
        Serial.println(data);

        int maxLen = RH_ASK_MAX_MESSAGE_LEN;

        int numSubStrings = ((len - 1) / maxLen) + 1;

        ubyte subStrings[numSubStrings][maxLen];

        for (int i = 0; i < len; i++)
        {
            int subI = i / maxLen;
            int charI = i % maxLen;
            subStrings[subI][charI] = data[i];
        }
        //no need to null terminate

        for (int subI = 0; subI < numSubStrings - 1; subI++)
        {
            Transmit(subStrings[subI], maxLen);
        }
        int lastStrLen = len % maxLen == 0 ? maxLen : len % maxLen;
        Transmit(subStrings[numSubStrings - 1], lastStrLen);
    }

    static void Transmit(ubyte *bytes, ubyte len)
    {
        // Radio::driver.waitPacketSent();
        digitalWrite(Radio::ledPin, HIGH);
        // if (len > RH_ASK_MAX_MESSAGE_LEN)
        // {
        //     data = "message too long: " + len;
        //char newBytes[] = "message too long: " + len;
        // len = sizeof(newBytes) / sizeof(newBytes[0]);
        // Radio::driver.send(newBytes, len);
        // }
        Radio::driver.send(bytes, len);
        digitalWrite(Radio::ledPin, LOW);
    }
};

StaticAction<String> *RadioTransmitter::doTransmit = new StaticAction<String>(&RadioTransmitter::Transmit);
