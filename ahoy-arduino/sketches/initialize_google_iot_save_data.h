#include "../ahoy/google-iot/googleIotSaveData.h"

GoogleIotSaveData *saveData;

char deviceId[] = "my_device";

void setup()
{
	Serial.begin(115200);
	Serial.println();
	Serial.println("Initializing save data...");
	saveData = new GoogleIotSaveData();
	saveData->ClearData();
	strcpy(saveData->deviceId, deviceId);
	strcpy(saveData->ssid, "My Network"); //WIFI STATIONARY SEEMS TO NOT FAIL WHEN GIVEN EMPTY STRING
	strcpy(saveData->password, "**********");
	saveData->SaveToEEPROM();
	saveData->LoadFromEEPROM();
	Serial.println("Save Data Initialized");
	Serial.print("EEPROM SIZE: ");
	Serial.print(sizeof(GoogleIotSaveData));
	Serial.println("/4096");
	Serial.print("Write Count: ");
	Serial.println(saveData->writeCount);
	Serial.print("SSID: \"");
	Serial.print(saveData->ssid);
	Serial.println("\"");
	Serial.print("Password: \"");
	Serial.print(saveData->password);
	Serial.println("\"");
	Serial.print("Device Id: \"");
	Serial.print(saveData->deviceId);
	Serial.println("\"");
}

void loop() {}