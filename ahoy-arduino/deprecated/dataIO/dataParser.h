#pragma once

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

protected:
    uint8_t termStartCount = 0;
    uint8_t termEndCount = 0;
    uint8_t dataBuff[RECV_BUFF_LEN] = {0};
    int dataBuffIndex = 0;
    bool isReceiving = false;

public:
    virtual void OnMessage()
    {
#ifdef GPP_DEBUG
        std::cout << "message!\n";
        for (int i = 0; i < dataBuffIndex; i++)
        {
            std::cout << "\tbyte: ";
            std::cout << unsigned(dataBuff[i]);
            std::cout << "\tint: ";
            std::cout << BytesToInt16(dataBuff, i);
            std::cout << "\tfloat: ";
            std::cout << BytesToFloat(dataBuff, i);
            std::cout << "\n";
        }
        std::cout << "\n";
#endif
    }

    void StartSerializeMessage()
    {
        memset(dataBuff, 0x00, RECV_BUFF_LEN);
        dataBuffIndex = 0;
        Int32ToBytes(TERM_START_LONG, dataBuff, dataBuffIndex);
        dataBuffIndex += 4;
    }

    void EndSerializeMessage()
    {
        Int32ToBytes(TERM_END_LONG, dataBuff, dataBuffIndex);
        dataBuffIndex += 4;
        Serial.write(dataBuff, dataBuffIndex);
        // for (int i = 0; i < dataBuffIndex; i++)
        // {
        //     Serial.write(dataBuff[i]);
        // }
        // Serial.flush();
    }

    void SerializeMessageB(byte v0)
    {
        StartSerializeMessage();
        dataBuff[dataBuffIndex++] = v0;
        EndSerializeMessage();
    }

    void SerializeMessageBB(byte v0, byte v1)
    {
        StartSerializeMessage();
        dataBuff[dataBuffIndex++] = v0;
        dataBuff[dataBuffIndex++] = v1;
        EndSerializeMessage();
    }
    void SerializeMessageBBB(byte v0, byte v1, byte v2)
    {
        StartSerializeMessage();
        dataBuff[dataBuffIndex++] = v0;
        dataBuff[dataBuffIndex++] = v1;
        dataBuff[dataBuffIndex++] = v2;
        EndSerializeMessage();
    }
    void SerializeMessageBBII(byte v0, byte v1, int v2, int v3)
    {
        StartSerializeMessage();
        dataBuff[dataBuffIndex++] = v0;
        dataBuff[dataBuffIndex++] = v1;
        Int16ToBytes(v2, dataBuff, dataBuffIndex);
        dataBuffIndex += 2;
        Int16ToBytes(v3, dataBuff, dataBuffIndex);
        dataBuffIndex += 2;
        EndSerializeMessage();
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
        //BEGIN TERM CHECK--CAN RESET IF TWO BEGIN MESSAGES SENT------------------------------------
        // if (!isReceiving)
        // {
        if (termStartCount == 3 && b == TERM_START_BYTE_3)
        {
            isReceiving = true;
            dataBuffIndex = 0;
            termStartCount = 0;
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "RECEIVE START");
#endif
            memset(dataBuff, 0x00, RECV_BUFF_LEN);
            return;
        }
        else if (termStartCount == 2 && b == TERM_START_BYTE_2)
            termStartCount++;
        else if (termStartCount == 1 && b == TERM_START_BYTE_1)
            termStartCount++;
        else if (b == TERM_START_BYTE_0)
            termStartCount++;
        else //DIDNT ULT, CLEAR START COUNT
            termStartCount = 0;
        // }
        //END TERM CHECK---ONLY IF IS RECEIVING
        if (isReceiving)
        {
            if (termEndCount == 3 && b == TERM_END_BYTE_3)
            {
                isReceiving = false;
                termEndCount = 0;
#ifdef ARDUINO_DEBUG
                Serial.println(String() + "RECEIVE END - LENGTH - " + dataBuffIndex);
#endif
                OnMessage();
                memset(dataBuff, 0x00, RECV_BUFF_LEN);
            }
            else if (termEndCount == 2 && b == TERM_END_BYTE_2)
                termEndCount++;
            else if (termEndCount == 1 && b == TERM_END_BYTE_1)
                termEndCount++;
            else if (b == TERM_END_BYTE_0)
                termEndCount++;
            else //CONTINUE RECEIVE MESSAGE, CLEAR TERMINATION BUFFER
            {
#ifdef ARDUINO_DEBUG
                Serial.println(String() + "BYTE RECEIVED! - " + b);
#endif
                dataBuff[dataBuffIndex++] = b;
                termEndCount = 0;
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