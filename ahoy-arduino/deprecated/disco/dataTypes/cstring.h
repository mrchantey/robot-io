

template <int strLen>
class cstring
{

  public:
    const uint nullTermLength = strLen + 1;
    char str[strLen + 1];

  private:
    uint currentPosition = 0;

  public:
    cstring()
    {
        for (int i = 0; i < nullTermLength; i++)
        {
            str[i] = '\0';
        }
    }

    cstring(char *msg, uint len = strLen)
    {
        for (int i = 0; i < len; i++)
        {
            str[i] = msg[i];
        }
        str[nullTermLength - 1] = '\0';
    }

    void Append(char *msg, uint len)
    {
        if (currentPosition + len - 1 >= strLen)
        {
            Serial.println("error, max string nullTermLength reached");
            return;
        }
        for (int i = 0; i < len; i++)
        {
            str[currentPosition + i] = msg[i];
        }
        currentPosition += len;
    }

    template <int otherLen>
    cstring<strLen + otherLen> Add(cstring<otherLen> other)
    {

        const int newLen = strLen + otherLen;
        char newStr[newLen];

        for (int i = 0; i < nullTermLength - 1; i++)
        {
            newStr[i] = str[i];
        }
        for (int i = 0; i < other.nullTermLength - 1; i++)
        {
            newStr[i + nullTermLength - 1] = other.str[i];
        }

        cstring<newLen> newString = cstring<newLen>(newStr);
        // cstring<len + otherLen> newString = cstring<len + otherLen>("");
        return newString;
    }
};