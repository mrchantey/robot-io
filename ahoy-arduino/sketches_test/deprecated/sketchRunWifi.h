#include "../ahoy/ahoy.h"
#include "../ahoy/wifi/accessPointInfo.h"
#include "../ahoy/wifi/wifiStationary.h"
#include "../ahoy/wifi/wifiAccessPoint.h"
#include "../ahoy/wifi/wifiServer.h"

AccessPointInfo *accessPointInfo;
WifiStationary *wifiStationary;
WifiAccessPoint *wifiAccessPoint;
WifiServer *wifiServer;

// WifiStationary *wifiStationary;

void CreateAccessPoint()
{
    Serial.println("creating access point");
    wifiAccessPoint = new WifiAccessPoint();
    delay(100);
    wifiServer = new WifiServer();
}

void setup()
{
    Serial.begin(115200);
    Serial.println();

    accessPointInfo = new AccessPointInfo();
    accessPointInfo->LoadFromEEPROM();

    wifiStationary = new WifiStationary();
    wifiStationary->onFailedConnection->AddAction(new StaticNullAction(CreateAccessPoint));
    wifiStationary->Connect(accessPointInfo->ssid, accessPointInfo->password);
}

void loop()
{
    LoopSystem::Update();
}