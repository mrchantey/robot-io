
const uint MAX_JSON_BYTES = 128;
class JsonReceive
{
public:
    Action<JsonReceive, NoType> *doReceiveSerial;
    Event<JsonArray, 4> *onMessage;
    char recv[MAX_JSON_BYTES];
    int recvIndex = 0;
    int depth = 0;

    char objOpen = '{';
    char objClose = '}';
    char arrOpen = '[';
    char arrClose = ']';

    JsonReceive()
    {
        doReceiveSerial = new Action<JsonReceive, NoType>(this, &JsonReceive::ReceiveSerial);
        LoopSystem::AddListener(doReceiveSerial);

        onMessage = new Event<JsonArray, 4>();
    }

    void ReceiveSerial()
    {
        while (Serial.available())
        {
            char c = Serial.read();
            Receive(c);
        }
    }

    void ReceiveString(String str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            Receive(str.charAt(i));
        }
    }

    void ReceiveCharArray(char *str, uint len)
    {
        for (int i = 0; i < len; i++)
        {
            Serial.println(String() + "receiving: " + str[i]);
            Receive(str[i]);
        }
    }

    void Receive(char c)
    {
        if ((c == objOpen || c == arrOpen) && depth == 0)
        {
            Serial.println(String() + "begin recv!");
            memset(recv, 0x00, MAX_JSON_BYTES);
            recvIndex = 0;
            recv[recvIndex++] = c;
            depth = 1;
        }
        else if ((c == objClose || c == arrClose) && depth == 1)
        {
            // Serial.println(String() + "end recv!");
            depth = 0;
            recv[recvIndex++] = c;
            OnMessage();
        }

        else if ((c == objOpen || c == arrOpen) && depth >= 1)
        {
            // Serial.println(String() + "go deeper!");
            recv[recvIndex++] = c;
            depth++;
        }
        else if ((c == objClose || c == arrClose) && depth > 1)
        {
            // Serial.println(String() + "go shallower!");
            recv[recvIndex++] = c;
            depth--;
        }
        else if (depth > 0)
        {
            // Serial.println(String() + "keep receiving!");
            recv[recvIndex++] = c;
        }
    }

    void OnMessage()
    {
        Serial.println("message received!!");
        DeserializationError error = deserializeJson(JsonDoc, recv, recvIndex);
        if (error)
        {
            Serial.println(error.c_str());
            return;
        }
        // Serial.println(recv);
        onMessage->Invoke(JsonDoc.as<JsonArray>());
    }
};