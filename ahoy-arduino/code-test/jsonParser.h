

class JsonParser
{
private:
    const static uint16_t JSON_BUFFER_SIZE = 128;
    char buffer[JSON_BUFFER_SIZE];
    int bufferIndex = 0;
    int parseIndex = 0;
    bool isReceiving = false;

public:
    JsonParser()
    {
        ResetBuffer();
    }

    void ResetBuffer()
    {
        memset(buffer, 0x00, JSON_BUFFER_SIZE);
        bufferIndex = 0;
        parseIndex = 0;
    }

    void BeginMessage()
    {
        bufferIndex += sprintf(buffer + bufferIndex, "[");
    }

    void EndMessage()
    {
        //remove trailing comma
        if (buffer[bufferIndex - 1] == ',')
            sprintf(buffer + bufferIndex - 1, "]");
        else
            bufferIndex += sprintf(buffer + bufferIndex, "]");
    }

    void ReceiveInt(uint16_t v0)
    {
        bufferIndex += sprintf(buffer + bufferIndex, "%d,", v0);
    }

    void ReceiveFloat(float v0)
    {
        bufferIndex += sprintf(buffer + bufferIndex, "%f,", v0);
    }

    void ReceiveJsonCharArray(char *arr, size_t len)
    {
        for (int i = 0; i < len; i++)
        {
            ReceiveChar(arr[i]);
        }
    }

    virtual void OnMessage()
    {
#ifdef GPP_DEBUG
        std::cout << "message received!";
        std::cout << "\n";
        std::cout << buffer;
        std::cout << "\n";
#endif
    }

    void ReceiveChar(char c)
    {
        if (c == '[')
        {
            isReceiving = true;
            ResetBuffer();
        }
        else if (isReceiving && c == ']')
        {
            OnMessage();
        }
        else if (isReceiving)
        {
            buffer[bufferIndex++] = c;
        }
    }

    int ParseInt()
    {
        int val;
        sscanf(buffer + parseIndex, "%d", &val);
        char tempBuff[32] = {0};
        parseIndex += sprintf(tempBuff, "%d", val);
        parseIndex++; //add 1 for comma seperator
        return val;
    }
    float ParseFloat()
    {
        float val;
        sscanf(buffer + parseIndex, "%f", &val);
        char tempBuff[32] = {0};
        parseIndex += sprintf(tempBuff, "%f", val);
        parseIndex++; //add 1 for comma seperator
        return val;
    }
};