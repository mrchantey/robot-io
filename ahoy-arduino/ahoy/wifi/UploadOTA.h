//copied from https://github.com/esp8266/Arduino/blob/master/libraries/ArduinoOTA/examples/BasicOTA/BasicOTA.ino
//ensure flash is set to correct size (usually 4mb)
//details:
//https://arduino-esp8266.readthedocs.io/en/latest/ota_updates/readme.html#arduino-ide
#include "../google-iot/googleIotSaveData.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

class UploadOTA
{
public:
	void (*onBeginLoad)() = [&]() {};
	void (*onEndLoad)() = [&]() {};
	UploadOTA(GoogleIotSaveData *saveData)
	{
		// No authentication by default
		// ArduinoOTA.setPassword("admin");

		// Password can be set with it's md5 value as well
		// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
		// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
		char hostname[64] = "ota_";
		strcat(hostname, saveData->deviceId);
		ArduinoOTA.setHostname(hostname);

		ArduinoOTA.onStart([&]() {
			onBeginLoad();
			// NOTE: if updating FS this would be the place to unmount FS using FS.end()
			#ifdef ARDUINO_DEBUG
			String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
			Serial.println("Start updating " + type);
			#endif
			});
		ArduinoOTA.onEnd([&]() {
			//force restart?
			#ifdef ARDUINO_DEBUG
			Serial.println("\nEnd");
			#endif
			});

		#ifdef ARDUINO_DEBUG
		ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
			Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
			});
		ArduinoOTA.onError([](ota_error_t error) {
			Serial.printf("Error[%u]: ", error);
			if (error == OTA_AUTH_ERROR)
				Serial.println("Auth Failed");
			else if (error == OTA_BEGIN_ERROR)
				Serial.println("Begin Failed");
			else if (error == OTA_CONNECT_ERROR)
				Serial.println("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR)
				Serial.println("Receive Failed");
			else if (error == OTA_END_ERROR)
				Serial.println("End Failed");
			});
		#endif

		ArduinoOTA.begin();
	}

	void Update()
	{
		ArduinoOTA.handle();
	}
};
