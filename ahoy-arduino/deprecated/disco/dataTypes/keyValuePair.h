

template <typename dataT>
class KeyValuePair
{

  public:
    String key;
    dataT value;
    KeyValuePair(String _key, dataT _value)
    {
        key = _key;
        value = _value;
    }

    String ToJson()
    {
        ubyte keyLen = key.length();
        String valStr = String(value);
        ubyte valLen = valStr.length();

        ubyte dataLen = keyLen + valLen + 6;
        ubyte data[dataLen];

        data[0] = '{';
        data[1] = '"';
        for (int i = 0; i < keyLen; i++)
        {
            data[i + 2] = key[i];
        }
        data[keyLen + 2] = '"';
        data[keyLen + 3] = ':';

        for (int i = 0; i < valLen; i++)
        {
            data[keyLen + 4 + i] = valStr[i];
        }
        data[keyLen + valLen + 4] = '}';
        //important to null terminate
        data[keyLen + valLen + 5] = '\0';

        char charData[dataLen];
        for (int i = 0; i < dataLen; i++)
        {
            charData[i] = data[i];
        }
        return String(charData);
    }
};

//     Serial.println(dataLen);
//     Serial.println(charData);
// }

// void setup()
// {
//     Serial.begin(9600);
//     String key = "Acc value";
//     float value = 42.434;
//     PrintData(key, value);
// }

// void loop()
// {
// }