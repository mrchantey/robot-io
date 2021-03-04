#include "../ahoy/wifi/accessPointInfo.h"

AccessPointInfo *info;

void setup()
{
    Serial.begin(115200);
    info = new AccessPointInfo();
    info->LoadFromEEPROM();
    // info->SetFromStrings("hello", "world");
    // info->SaveToEEPROM();
    Serial.println(String() + "\nssid: " + info->ssid + "\tpassword: " + info->password);
}

void loop()
{
}