
struct ByteArray
{
    uint8_t *arr;
    int length;
};

class DataParser
{
public:
    static const int RECV_BUFF_LEN = 128;
    static const int FLOAT_SCALAR = 1000;
    // static const int FLOAT_SCALAR = 10000;
    static const uint32_t TERM_START_LONG = 696969696;
    static const uint8_t TERM_START_BYTE_0 = 41;
    static const uint8_t TERM_START_BYTE_1 = 138;
    static const uint8_t TERM_START_BYTE_2 = 233;
    static const uint8_t TERM_START_BYTE_3 = 224;

    static const uint32_t TERM_END_LONG = 969696969;
    static const uint8_t TERM_END_BYTE_0 = 57;
    static const uint8_t TERM_END_BYTE_1 = 204;
    static const uint8_t TERM_END_BYTE_2 = 102;
    static const uint8_t TERM_END_BYTE_3 = 201;

    uint8_t termBuff[4] = {0};
    uint8_t recv[RECV_BUFF_LEN] = {0};
    int recvIndex = 0;

    bool isReceiving = false;

    virtual void OnMessage()
    {
#ifdef GPP_DEBUG
        std::cout << "message!\n";
        for (int i = 0; i < recvIndex; i++)
        {
            std::cout << "\tbyte: ";
            std::cout << unsigned(recv[i]);
            std::cout << "\tint: ";
            std::cout << BytesToInt16(recv, i);
            std::cout << "\tfloat: ";
            std::cout << BytesToFloat(recv, i);
            std::cout << "\n";
        }
        std::cout << "\n";
#endif
    }

    void ReceiveFloat(float val)
    {
        uint8_t bytes[2] = {0};
        FloatToBytes(val, bytes);
        ReceiveByte(bytes[0]);
        ReceiveByte(bytes[1]);
    }

    void ReceiveInt16(int16_t val)
    {
        uint8_t bytes[2] = {0};
        Int16ToBytes(val, bytes);
        ReceiveByte(bytes[0]);
        ReceiveByte(bytes[1]);
    }
    void ReceiveInt32(int32_t val)
    {
        uint8_t bytes[4] = {0};
        Int32ToBytes(val, bytes);
        ReceiveByte(bytes[0]);
        ReceiveByte(bytes[1]);
        ReceiveByte(bytes[2]);
        ReceiveByte(bytes[3]);
    }

    void ReceiveByteArray(uint8_t *arr, int len)
    {
        for (int i = 0; i < len; i++)
        {
            ReceiveByte(arr[i]);
        }
    }
    void ReceiveByte(uint8_t b)
    {
        //BEGIN TERM CHECK--------------------------------------
        if (!isReceiving)
        {
            if (termBuff[0] == TERM_START_BYTE_0 && termBuff[1] == TERM_START_BYTE_1 && termBuff[2] == TERM_START_BYTE_2 && b == TERM_START_BYTE_3)
            {
                isReceiving = true;
                recvIndex = 0;
                memset(termBuff, 0x00, 4);
                memset(recv, 0x00, RECV_BUFF_LEN);
            }
            else if (termBuff[0] == TERM_START_BYTE_0 && termBuff[1] == TERM_START_BYTE_1 && b == TERM_START_BYTE_2)
                termBuff[2] = b;
            else if (termBuff[0] == TERM_START_BYTE_0 && b == TERM_START_BYTE_1)
                termBuff[1] = b;
            else if (b == TERM_START_BYTE_0)
                termBuff[0] = b;
            else //DIDNT ULT, CLEAR TERMINATION BUFFER
                memset(termBuff, 0x00, 4);
        }
        //END TERM CHEACK
        else if (isReceiving)
        {
            if (termBuff[0] == TERM_END_BYTE_0 && termBuff[1] == TERM_END_BYTE_1 && termBuff[2] == TERM_END_BYTE_2 && b == TERM_END_BYTE_3)
            {
                isReceiving = false;
                memset(termBuff, 0x00, 4);
                OnMessage();
                memset(recv, 0x00, RECV_BUFF_LEN);
            }
            else if (termBuff[0] == TERM_END_BYTE_0 && termBuff[1] == TERM_END_BYTE_1 && b == TERM_END_BYTE_2)
                termBuff[2] = b;
            else if (termBuff[0] == TERM_END_BYTE_0 && b == TERM_END_BYTE_1)
                termBuff[1] = b;
            else if (b == TERM_END_BYTE_0)
                termBuff[0] = b;
            else //CONTINUE RECEIVE MESSAGE, CLEAR TERMINATION BUFFER
            {
                recv[recvIndex++] = b;
                memset(termBuff, 0x00, 4);
            }
        }
    }

    // private:
    static void Int16ToBytes(int16_t val, uint8_t *bytes, int index = 0)
    {
        bytes[index] = ((val >> 8) & 0xFF);
        bytes[index + 1] = ((val >> 0) & 0xFF);
    }

    static void FloatToBytes(float val, uint8_t *bytes, int index = 0)
    {
        int16_t valInt = val * FLOAT_SCALAR;
        Int16ToBytes(valInt, bytes, index);
    }

    static void Int32ToBytes(int32_t val, uint8_t *bytes, int index = 0)
    {
        bytes[index] = ((val >> 24) & 0xFF);
        bytes[index + 1] = ((val >> 16) & 0xFF);
        bytes[index + 2] = ((val >> 8) & 0xFF);
        bytes[index + 3] = ((val >> 0) & 0xFF);
    }

    static uint16_t BytesToInt16(uint8_t *bytes, int index = 0)
    {
        return (int16_t)bytes[index] << 8 |
               (int16_t)bytes[index + 1] << 0;
    }
    static int32_t BytesToInt32(uint8_t *bytes, int index = 0)
    {
        return (int32_t)bytes[index] << 24 |
               (int32_t)bytes[index + 1] << 16 |
               (int32_t)bytes[index + 2] << 8 |
               (int32_t)bytes[index + 3] << 0;
    }

    static float BytesToFloat(uint8_t *bytes, int index = 0)
    {
        int16_t valInt = BytesToInt16(bytes, index);
        return (float)valInt / FLOAT_SCALAR;
    }
};