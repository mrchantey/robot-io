#define ARDUINO_DEBUG //uncomment this line for production

#include "../ahoy/ahoy.h"

#include "../ahoy/jsonIO/jsonSerializer.h"

JsonSerializer *serializer;
int valuesI[4] = {0, 1, 2, 3};
float valuesF[4] = {0.01234, 100000, 20.3456, 3.45678901234};

void setup()
{
    Serial.begin(115200);
    serializer = new JsonSerializer();
    serializer->BeginSerializeMessage();
    serializer->Serialize(valuesI[0]);
    serializer->Serialize(valuesI[1]);
    serializer->Serialize(valuesI[2]);
    serializer->Serialize(valuesI[3]);
    serializer->Serialize(valuesF[0]);
    serializer->Serialize(valuesF[1]);
    serializer->Serialize(valuesF[2]);
    serializer->Serialize(valuesF[3]);
    serializer->EndSerializeMessage();
    Serial.print(serializer->buffer);
}

void loop()
{
}