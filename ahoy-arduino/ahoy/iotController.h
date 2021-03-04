#pragma once

#include "../ahoy/wifi/wifiStationary.h"
#include "../ahoy/wifi/wifiAccessPoint.h"
#include "../ahoy/wifi/wifiServer.h"
#include "../ahoy/wifi/UploadOTA.h"
#include "../ahoy/google-iot/googleIot.h"
#include "../ahoy/google-iot/googleIotSaveData.h"
#include "../ahoy/modules/definitions.h"

#ifndef PIN_SETUP_MODE
#define PIN_SETUP_MODE 4 //(D2) 15 causes hangup
#endif

class IotController;

IotController *_iotController;

class IotController
{
public:
	WifiAccessPoint *wifiAccessPoint;
	WifiServer *wifiServer;

	WifiStationary *wifiStationary;
	GoogleIot *googleIot;
	UploadOTA *uploadOTA;

	GoogleIotSaveData *saveData;

	bool accessPointMode = false;

	void (*onMessageInt)(int);
	void (*onMessageString)(String &);

	IotController()
	{
		_iotController = this;
		saveData = new GoogleIotSaveData();
	}

	void Begin()
	{
		saveData->LoadFromEEPROM();

		pinMode(PIN_SETUP_MODE, INPUT);
		if (digitalRead(PIN_SETUP_MODE))
			CreateAccessPoint();
		else
			CreateStationary();
	}

	void Update()
	{
		if (accessPointMode)
		{
			wifiServer->Update();
		}
		else
		{
			wifiStationary->Update();
			if (wifiStationary->isConnected)
			{
				googleIot->Update();
				uploadOTA->Update();
			}
		}
	}

	void CreateAccessPoint()
	{
#ifdef ARDUINO_DEBUG
		Serial.println("creating access point");
#endif
		accessPointMode = true;
		onMessageInt(MKEY_CONFIG_MODE);
		wifiAccessPoint = new WifiAccessPoint(saveData->deviceId);
		delay(100); //apparently this is important
		wifiServer = new WifiServer(saveData);
		wifiServer->onMessage = HandleonMessageString;
	}

	void CreateStationary()
	{
#ifdef ARDUINO_DEBUG
		Serial.println("creating wifi client");
#endif
		wifiStationary = new WifiStationary(saveData->ssid, saveData->password, true);

		wifiStationary->onConnecting = HandleWifiStationaryConnecting;
		wifiStationary->onConnection = HandleWifiStationaryConnection;
	}

	static void HandleonMessageString(String &message)
	{
		_iotController->onMessageString(message);
	}

	static void HandleWifiStationaryConnecting()
	{
		_iotController->onMessageInt(MKEY_WIFI_CONNECTING);
	}

	static void HandleWifiStationaryConnection()
	{
		_iotController->onMessageInt(MKEY_WIFI_CONNECTED);

		void (*onMessage)(String & topic, String & payload) = [&](String &topic, String &payload) {
#ifdef ARDUINO_DEBUG
			Serial.print("IOT MESSAGE RECEIVED: ");
			Serial.print(topic);
			Serial.print("\t");
			Serial.print(payload);
			Serial.println();
#endif
			if (payload == "")
			{
#ifdef ARDUINO_DEBUG
				Serial.println("EMPTY MESSAGE");
#endif
				return;
			}
			else
				_iotController->onMessageString(payload);
		};
		_iotController->googleIot = new GoogleIot(_iotController->saveData->deviceId, onMessage);
		_iotController->googleIot->onConnecting = []() { _iotController->onMessageInt(MKEY_MQTT_CONNECTING); };
		_iotController->googleIot->onConnection = []() {
			_iotController->onMessageInt(MKEY_MQTT_CONNECTED);
			_iotController->onMessageInt(MKEY_CONNECTED);
		};

		_iotController->uploadOTA = new UploadOTA(_iotController->saveData);
		_iotController->uploadOTA->onBeginLoad = [&]() { _iotController->onMessageInt(MKEY_OTA_BEGIN); };
		_iotController->uploadOTA->onEndLoad = [&]() { _iotController->onMessageInt(MKEY_OTA_END); };
	}
};
