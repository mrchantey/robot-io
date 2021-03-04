#pragma once
#include <Client.h>
#include <MQTTClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include "../secret/googleCloudIotSecret.h"
#include <time.h>
#include <MQTT.h>

#include "base64.h"
#include "jwt.h"

// void messageReceived(String &topic, String &payload);

class GoogleIot
{
public:
	void (*onConnection)() = []() {};
	void (*onConnecting)() = []() {};
	void (*onFailedConnection)() = []() {};
	void (*onMessage)(String &topic, String &payload) = [](String &topic, String &payload) {};

	GoogleIot(
		const char *device_id,
		void (*onMessage)(String &topic, String &payload),
		int jwtTimeout = 3600 * 24)
		: GoogleIot(
			  GoogleCloudIotSecret::project_id,
			  GoogleCloudIotSecret::location,
			  GoogleCloudIotSecret::registry_id,
			  device_id,
			  GoogleCloudIotSecret::private_key_str,
			  GoogleCloudIotSecret::primary_ca,
			  GoogleCloudIotSecret::backup_ca,
			  jwtTimeout, //one hour
			  onMessage)
	{
	}

	GoogleIot(
		const char *project_id,
		const char *location,
		const char *registry_id,
		const char *device_id,
		const char *private_key,
		const char *primary_ca,
		const char *backup_ca,
		int _jwt_exp_secs,
		void (*onMessage)(String &topic, String &payload))
	{
		this->onMessage = onMessage;
		this->project_id = project_id;
		this->location = location;
		this->registry_id = registry_id;
		this->device_id = device_id;

		jwt_exp_secs = _jwt_exp_secs;

#ifdef ARDUINO_DEBUG
		Serial.println("Initializing MQTT..");
#endif

		InitializePrivateKey(private_key);
		InitializeSecureClient(primary_ca, backup_ca);
		InitializeTimeSync("pool.ntp.org", "time.nist.gov");
		InitializeMQTT();
#ifdef ARDUINO_DEBUG
		Serial.println("MQTT Initialized");
#endif
	}

	void Update() //mqtt client seems to NEED to loop every short period of time
	{
		CheckJwt();
		CheckConnection();
		mqttClient->loop();
		// delay(10); //apparently deals with some wifi instability issues
	}

	// void Initialize()

private:
	BearSSL::WiFiClientSecure *netClient;
	BearSSL::X509List certList;
	MQTTClient *mqttClient;

	const char *CLOUD_IOT_CORE_MQTT_HOST_LTS = "mqtt.2030.ltsapis.goog";
	const int CLOUD_IOT_CORE_MQTT_PORT = 8883;

	int backoffFactor = 2;
	// int numConnectionRetrys = 6;
	int backoffMin = 1000;
	int backoffMax = 60000;
	int backoffJitter = 500;

	//probably not needed
	const char *project_id;
	const char *location;
	const char *registry_id;
	const char *device_id;

	NN_DIGIT priv_key[9];

	//JWT STUFF
	String jwt;
	int jwt_exp_secs;
	unsigned long jwt_exp_time_millis = 0; //remember when will expire

	void InitializeSecureClient(const char *primary_ca, const char *backup_ca)
	{
		netClient = new WiFiClientSecure();
		certList.append(primary_ca);
		certList.append(backup_ca);
		netClient->setTrustAnchors(&certList);
	}

	void InitializeTimeSync(const char *ntp_primary, const char *ntp_secondary)
	{
		configTime(0, 0, ntp_primary, ntp_secondary);
#ifdef ARDUINO_DEBUG
		Serial.println("Synchronizing time...");
#endif
		while (time(nullptr) < 1510644967)
		{
			delay(10);
		}
#ifdef ARDUINO_DEBUG
		Serial.println("Time Synchronized");
#endif
	}

	void InitializePrivateKey(const char *private_key)
	{
		priv_key[8] = 0;
		for (int i = 7; i >= 0; i--)
		{
			priv_key[i] = 0;
			for (int byte_num = 0; byte_num < 4; byte_num++)
			{
				priv_key[i] = (priv_key[i] << 8) + strtoul(private_key, NULL, 16); // sometimes causes crash on ESP8266EX
				private_key += 3;
			}
		}
	}
	void InitializeMQTT()
	{
		mqttClient = new MQTTClient(512);
		mqttClient->setOptions(180, true, 1000); // keepAlive, cleanSession, timeout
		mqttClient->begin(CLOUD_IOT_CORE_MQTT_HOST_LTS, CLOUD_IOT_CORE_MQTT_PORT, *netClient);
		mqttClient->onMessage(onMessage);
	}

	void SetJwt()
	{
		ESP.wdtDisable();
		unsigned long current_time = time(nullptr);
#ifdef ARDUINO_DEBUG
		Serial.println("Refreshing JWT");
#endif
		jwt_exp_time_millis = millis() + (jwt_exp_secs * 1000);
		jwt = Jwt::CreateJwt(project_id, current_time, priv_key, jwt_exp_secs);
		ESP.wdtEnable(0);
	}

	void CheckJwt()
	{
		// if (millis() >= jwt_exp_time_millis && mqttClient->connected())
		if (millis() >= jwt_exp_time_millis)
		{
#ifdef ARDUINO_DEBUG
			Serial.println("Reconnecting before JWT expiration");
#endif
			TryMQTTConnect(true);
		}
	}

	void CheckConnection()
	{
		if (!mqttClient->connected())
			TryMQTTConnect();
	}

	//TODO non blocking
	bool TryMQTTConnect(bool skip = false)
	{
		onConnecting();
		ESP.wdtDisable();
		bool keepgoing = true;
		int backoff = backoffMin;
		while (keepgoing)
		{
#ifdef ARDUINO_DEBUG
			Serial.println("MQTT connecting...");
#endif
			SetJwt();
			mqttClient->disconnect();
			int result = mqttClient->connect(getClientId().c_str(), "unused", jwt.c_str(), skip);

			// if (mqttClient->lastError() != LWMQTT_SUCCESS && result)
			if ((mqttClient->lastError() != LWMQTT_SUCCESS && result != 0) || !mqttClient->connected())
			{
				if (backoff > backoffMax)
				{
#ifdef ARDUINO_DEBUG
					Serial.println("Maximum backoff reached, giving up..");
#endif
					onFailedConnection();
					return false;
				}
#ifdef ARDUINO_DEBUG
				Serial.println("Delaying " + String(backoff) + "ms");
#endif
				backoff = backoff * backoffFactor + random(backoffJitter);
				skip = false;
				delay(backoff);
			}
			else
				keepgoing = false;
		}
#ifdef ARDUINO_DEBUG
		Serial.print("MQTT connected - device Id: ");
		Serial.println(device_id);
#endif

		mqttClient->subscribe(getConfigTopic(), 1); //QoS 1 (ack) (0 = no ack)
		mqttClient->subscribe(getCommandsTopic(), 1);

		// publishState("connected");
		// publishTelemetry("/events", getDeviceId() + String("-connected"));
		ESP.wdtEnable(0);
		onConnection();
		return true;
	}

	String getBasePath()
	{
		return String("/v1/projects/") + project_id + "/locations/" + location +
			   "/registries/" + registry_id + "/devices/" + device_id;
	}

	String getClientId()
	{
		return String("projects/") + project_id + "/locations/" + location +
			   "/registries/" + registry_id + "/devices/" + device_id;
	}

	String getConfigTopic()
	{
		return String("/devices/") + device_id + "/config";
	}

	String getCommandsTopic()
	{
		return String("/devices/") + device_id + "/commands/#";
	}

	String getDeviceId()
	{
		return String(device_id);
	}

	String getEventsTopic()
	{
		return String("/devices/") + device_id + "/events";
	}

	String getStateTopic()
	{
		return String("/devices/") + device_id + "/state";
	}

	String getConfigPath(int version)
	{
		char buf[8] = {0};
		itoa(version, buf, 10);
		return this->getBasePath() + "/config?local_version=" + buf;
	}

	String getLastConfigPath()
	{
		return this->getConfigPath(0);
	}

	String getSendTelemetryPath()
	{
		return this->getBasePath() + ":publishEvent";
	}

	String getSetStatePath()
	{
		return this->getBasePath() + ":setState";
	}

	bool publishTelemetry(String data)
	{
		return this->mqttClient->publish(getEventsTopic(), data);
	}

public:
	bool publishTelemetry(const char *data, int length)
	{
		return this->mqttClient->publish(getEventsTopic().c_str(), data, length);
	}

private:
	bool publishTelemetry(String subtopic, String data)
	{
		return this->mqttClient->publish(getEventsTopic() + subtopic, data);
	}

	bool publishTelemetry(String subtopic, const char *data, int length)
	{
		return this->mqttClient->publish(String(getEventsTopic() + subtopic).c_str(), data, length);
	}

	// Helper that just sends default sensor
	bool publishState(String data)
	{
		return this->mqttClient->publish(getStateTopic(), data);
	}

	bool publishState(const char *data, int length)
	{
		return this->mqttClient->publish(getStateTopic().c_str(), data, length);
	}
};