#pragma once

class DataIO : public DataParser
{
public:
    NullAction<DataIO> *doReceiveSerial;
    Event<uint8_t *, 4> *onMessage;
    DataIO()
    {
        doReceiveSerial = new NullAction<DataIO>(this, &DataIO::ReceiveSerial);
        LoopSystem::AddListener(doReceiveSerial);

        onMessage = new Event<uint8_t *, 4>();
    }

    void ReceiveSerial()
    {
        while (Serial.available())
        {
            uint8_t b = Serial.read();
            ReceiveByte(b);
        }
    }

    void OnMessage()
    {
#ifdef ARDUINO_DEBUG
        Serial.println(String() + "Data IO - Message Parsed!");
#endif
        onMessage->Invoke(dataBuff);
    }
};