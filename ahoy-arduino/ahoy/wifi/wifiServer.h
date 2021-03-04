#include <ESP8266WebServer.h>
#include "../google-iot/googleIotSaveData.h"
#include <ESP8266mDNS.h>

void Static_HandlePostWifiData();

//CONVERTED STRING TO CHAR ARRAY

class WifiServer
{
	ESP8266WebServer *webServer;
	GoogleIotSaveData *saveData;

public:
	void (*onMessage)(String &message) = [](String &message) {};

	WifiServer(GoogleIotSaveData *_saveData)
	{
		saveData = _saveData;
		webServer = new ESP8266WebServer(80); //creating the server at port 80
		webServer->on("/message", HTTP_POST, [&]() {String str = webServer->arg("message"); onMessage(str);HandleServeWebpage(); });
		webServer->on("/saveData", HTTP_POST, [&]() { WifiServer::HandlePostWifiData(); });
		webServer->on("/", [&]() { WifiServer::HandleServeWebpage(); });
		// webServer->on("/ping", [&]() { WifiServer::HandlePing(); });
		webServer->onNotFound([&]() { WifiServer::webServer->send(404, "text/html", "Not Found"); });
		if (!MDNS.begin("iotdevice"))
		{
#ifdef ARDUINO_DEBUG
			Serial.println("Error setting up MDNS responder!");
#endif
		}
		webServer->begin();
		// MDNS.begin("iotdevice");
	}

	// void HandlePing()
	// {
	// 	webServer->send(200, "text/html", "CHANTEY_IOT_DEVICE_PING");
	// }

	void HandleServeWebpage()
	{
		saveData->LoadFromEEPROM();

		//hopefully this is stored in flash? about 600 bytes
		static const char htmlRaw[] PROGMEM = /*435836*/ /* static const char htmlRaw[] = //435036*/
			"<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta http-equiv='X-UA-Compatible' content='ie=edge'><title>Device</title><style>html{font-family: Arial, Helvetica, sans-serif;text-align: center;}</style></head><body><h1>Device Setup</h1><p>version 0.6</p><h2>Config</h2><p>write count: %d</p><form action='/saveData' method='POST'>SSID:<br><input type='text' name='ssid' value='%s'><br>Password:<br><input type='text' name='password' value='%s'><br>Device Name:<br><input type='text' name='deviceId' value='%s'><br><input type='submit' value='Save'></form><br/><br/><form action='/message' method='POST'><div>Send Debug Message</div><input type='text' name='message'><br><input type='submit' value='Send'></form></body></html>";
		const uint len = strlen(htmlRaw) + GoogleIotSaveData::STRING_SIZE * 3;
		char html[len] = "";
		sprintf(html, htmlRaw, saveData->writeCount, saveData->ssid, saveData->password, saveData->deviceId);
		webServer->send(200, "text/html", html, len);
	}

	void HandlePostWifiData()
	{
		String ssid = webServer->arg("ssid");
		String password = webServer->arg("password");
		String deviceId = webServer->arg("deviceId");
		saveData->LoadFromEEPROM();
		saveData->SetFromStrings(ssid, password, deviceId);
		saveData->SaveToEEPROM();
		webServer->send(200, "text/html", "<h3>Success! Please restart your device in online mode.</h3>");
	}

	void Update()
	{
		webServer->handleClient();
		MDNS.update();
	}
};