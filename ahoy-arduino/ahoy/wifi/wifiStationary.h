#include <ESP8266WiFi.h>

class WifiStationary
{
public:
	unsigned int timeout = 10000;

	void (*onConnection)() = []() {};
	void (*onConnecting)() = []() {};
	// void (*onFailedConnection)() = []() {};

	bool isConnected = false;
	bool autoReconnect;
	char *ssid;
	char *password;
	long connectingMillis;

	WifiStationary(char *ssid, char *password, bool autoReconnect)
	{
		this->ssid = ssid;
		this->password = password;
		this->autoReconnect = autoReconnect;
	}

	void Update()
	{
		if (WiFi.status() == WL_CONNECTED) //poll for wifi connected
		{
			if (!isConnected)
			{
				isConnected = true;
#ifdef ARDUINO_DEBUG
				Serial.print("wifi Connected! ip address:\t");
				Serial.println(WiFi.localIP());
#endif
				onConnection();
			}
		}
		else
		{
			if (millis() - connectingMillis > timeout)
			{
#ifdef ARDUINO_DEBUG
				Serial.println("wifi is disconnected");
#endif
				if (autoReconnect)
					Connect();
			}
		}
	}

	void Connect()
	{
		Disconnect();
#ifdef ARDUINO_DEBUG
		Serial.println(String() + "\nwifi connecting.. \tssid: " + String(ssid) + "\tpassword: " + String(password));
#endif
		connectingMillis = millis();
		onConnecting();
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid, password);
	}

	void Disconnect()
	{
		if (isConnected)
			WiFi.disconnect();
		isConnected = false;
	}
};