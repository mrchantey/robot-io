#include "../ahoy/ahoy.h"
#include "../ahoy/wifi/wifiServer.h"
#include "../ahoy/wifi/wifiStationary.h"
#include "../ahoy/wifi/wifiAccessPoint.h"

WifiServer *server;
WifiAccessPoint *accessPoint;
GoogleIotSaveData *saveData;

void setup()
{
	saveData = new GoogleIotSaveData();
	saveData->LoadFromEEPROM();
	Serial.begin(115200);
	Serial.println();
	// stationary = new WifiStationary();
	accessPoint = new WifiAccessPoint(saveData->deviceId);
	delay(100);
	server = new WifiServer(saveData);
}

void loop()
{
	server->Update();
}