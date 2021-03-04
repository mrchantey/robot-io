#include <ESP8266WiFi.h>

class WifiAccessPoint
{
	// const char *SOFT_AP_PASSWORD = "1234";

public:
	WifiAccessPoint(char *_ssid)
	{

		char ssid[31];
		strncpy(ssid, _ssid, 30);

		IPAddress local_ip(192, 168, 1, 1);
		IPAddress gateway(192, 168, 1, 1);
		IPAddress subnet(255, 255, 0, 0);

		WiFi.mode(WIFI_AP);
		// WiFi.mode(WIFI_AP_STA);
		WiFi.softAPConfig(local_ip, gateway, subnet);
		WiFi.softAP(ssid);
		// WiFi.softAP(ssid, SOFT_AP_PASSWORD);
// delay(100);
#ifdef ARDUINO_DEBUG
		Serial.print("Access point up! IP address:\t");
		Serial.println(WiFi.softAPIP());
#endif
		// uint8_t macAddr[6];
		// WiFi.softAPmacAddress(macAddr);
		// Serial.printf("MAC address = %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
	}

	void SwitchOff()
	{
		WiFi.softAPdisconnect(true);
	}
};