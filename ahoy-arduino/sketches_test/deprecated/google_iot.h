#include "../ahoy/google-iot/googleIot.h"
// #include "../ahoy/secret/googleCloudIotSecret.h"

GoogleIot *googleIot;

const char *device_id = "kitchen";
const int jwt_expiry_secs = 60;
// const int jwt_expiry_secs = 3600; //1h, max 24h

void messageReceived(String &topic, String &payload)
{
#ifdef ARDUINO_DEBUG
    Serial.print("Message Received - topic: ");
    Serial.print(topic);
    Serial.print("\t message: '");
    Serial.print(payload);
    Serial.println("'");
#endif
}

void setup()
{
    Serial.begin(115200);
    Serial.println();
    googleIot = new GoogleIot(device_id, messageReceived, jwt_expiry_secs);
}

void loop()
{
    googleIot->Update();
    // Serial.println("looping");
}