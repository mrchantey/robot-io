#pragma once

#include <EEPROM.h>

//currently 100 bytes
class GoogleIotSaveData
{
public:
	static const int STRING_SIZE = 64;
	static const int EEPROM_ADDRESS = 0;
	uint writeCount = 0; //max 100,000 before failure
	char ssid[STRING_SIZE];
	char password[STRING_SIZE];
	char deviceId[STRING_SIZE];

	GoogleIotSaveData()
	{
		EEPROM.begin(sizeof(GoogleIotSaveData));
	}

	void ClearData()
	{
		memset(ssid, 0x00, STRING_SIZE);
		memset(password, 0x00, STRING_SIZE);
		memset(deviceId, 0x00, STRING_SIZE);
	}

	void SetFromStrings(String _ssid, String _password, String _deviceId)
	{
		ClearData();
		_ssid.toCharArray(ssid, STRING_SIZE, 0);
		_password.toCharArray(password, STRING_SIZE, 0);
		_deviceId.toCharArray(deviceId, STRING_SIZE, 0);
	}

	void SetFromCharArrays(char *_ssid, char *_password, char *_deviceId)
	{
		strncpy(ssid, _ssid, STRING_SIZE);
		strncpy(password, _password, STRING_SIZE);
		strncpy(deviceId, _deviceId, STRING_SIZE);
	}

	void SaveToEEPROM()
	{
		writeCount++;
		EEPROM.put(EEPROM_ADDRESS, *this);
		EEPROM.commit();
	}

	void LoadFromEEPROM()
	{
		EEPROM.get(EEPROM_ADDRESS, *this);
	}
};