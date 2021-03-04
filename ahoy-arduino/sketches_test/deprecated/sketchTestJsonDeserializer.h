#define ARDUINO_DEBUG //uncomment this line for production
// #include "../ahoy/ahoy.h"

#include "../ahoy/jsonIO/jsonDeserializer.h"

// char buff[] = "[02121,0.123456789,3433,gdaymate]";
char buff[] = "[5,1,0,0,0,0,0,0,0,0,0,9,1,0,1,0,255,0,1,0,0,255,0.5]";

JsonDeserializer *deserializer;

void HandleMessage(char **values)
{
    int val0 = atoi(values[0]);
    float val1 = atof(values[1]);
    int val2 = atoi(values[2]);
    char *val3 = values[3];
    Serial.println(val0);
    Serial.println(val1);
    Serial.println(val2);
    Serial.println(val3);
}

void setup()
{
    Serial.begin(115200);
    deserializer = new JsonDeserializer();
    deserializer->onMessage = [](char **values) { HandleMessage(values); };
    deserializer->Receive(buff);
}

void loop()
{
}