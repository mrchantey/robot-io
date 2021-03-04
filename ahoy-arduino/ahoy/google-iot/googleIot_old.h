#pragma once

#include <ESP8266WiFi.h>
// #include "FS.h"

// Google cloud pub sub allows about 3.7 pubsub messages (up to a kilobyte) per second
//this includes pushes and pulls
//after that its $40 / terabyte

// You need to set certificates to All SSL cyphers and you may need to
// increase memory settings in Arduino/cores/esp8266/StackThunk.cpp:
//C:\Users\petey\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.6.3\cores\esp8266\StackThunk.cpp
// #define _stackSize (6748/4)
//   https://github.com/esp8266/Arduino/issues/6811

// TODO publish states

#include "WiFiClientSecureBearSSL.h"
#include <time.h>
#include <MQTT.h>
#include <CloudIoTCore.h>
#include <CloudIoTCoreMqtt.h> //EDIT TO RETURN FALSE INSTEAD OF RETRYING CONNECTION

#include "../secret/googleCloudIotSecret.h"

// WiFiClient *netClient;
BearSSL::WiFiClientSecure *netClient;
BearSSL::X509List certList;

MQTTClient *mqttClient;
CloudIoTCoreDevice *device;
CloudIoTCoreMqtt *mqtt;
unsigned long iss = 0;
// const int jwt_exp_secs = 3600; // Maximum 24H (3600*24)
const int jwt_exp_secs = 30; // Maximum 24H (3600*24)
String jwt;

// void messageReceived(String &topic, String &payload)
// {
//     Serial.println("incoming: " + topic + " - " + payload);
// }

//must be global
String getJwt()
{
    ESP.wdtDisable();
    iss = time(nullptr);
#ifdef ARDUINO_DEBUG
    Serial.println("Refreshing JWT");
#endif
    jwt = device->createJWT(iss, jwt_exp_secs);
    ESP.wdtEnable(0);
    return jwt;
}

class GoogleIotds
{
public:
    // Time (seconds) to expire token += 20 minutes for drift
    char *deviceId;
    void (*onConnection)();
    void (*onFailedConnection)();
    bool hasFailed = false;
    bool hasInitialized = false; //not great

    GoogleIotds(char *_deviceId)
    {
        deviceId = _deviceId;
    }

    void Initialize()
    {
        //setup secure wifi
        netClient = new WiFiClientSecure();
        certList.append(GoogleCloudIotSecret::primary_ca);
        certList.append(GoogleCloudIotSecret::backup_ca);
        netClient->setTrustAnchors(&certList);

        //setup ntc
        configTime(0, 0, GoogleCloudIotSecret::ntp_primary, GoogleCloudIotSecret::ntp_secondary);
#ifdef ARDUINO_DEBUG
        Serial.println("Waiting on time sync...");
#endif
        while (time(nullptr) < 1510644967)
        {
            delay(10);
        }
#ifdef ARDUINO_DEBUG
        Serial.println("Time Synchronized");
#endif

        //setup mqtt
        device = new CloudIoTCoreDevice(GoogleCloudIotSecret::project_id, GoogleCloudIotSecret::location, GoogleCloudIotSecret::registry_id, deviceId, GoogleCloudIotSecret::private_key_str);
        mqttClient = new MQTTClient(512);
        mqttClient->setOptions(180, true, 1000); // keepAlive, cleanSession, timeout
        mqtt = new CloudIoTCoreMqtt(mqttClient, netClient, device);
        mqtt->setLogConnect(true);
        mqtt->setUseLts(true);

        mqtt->startMQTT(); // Opens connection, non blocking
#ifdef ARDUINO_DEBUG
        Serial.print("Google Iot Connected.. device id: ");
        Serial.println(deviceId);
#endif
        hasInitialized = true;
    }

    bool Publish(const char *data, int length)
    {
        return mqtt->publishTelemetry(data, length);
    }

    bool Publish(String subfolder, const char *data, int length)
    {
        return mqtt->publishTelemetry(subfolder, data, length);
    }

    void Update()
    {
        if (hasFailed || !hasInitialized)
            return;
        mqtt->loop();
        delay(10); // <- fixes some issues with WiFi stability

        if (!mqttClient->connected())
        {
#ifdef ARDUINO_DEBUG
            Serial.println("IOT Core Connecting..");
#endif
            ESP.wdtDisable();
            if (mqtt->mqttConnect())
            {
                ESP.wdtEnable(0);
#ifdef ARDUINO_DEBUG
                Serial.println("IOT Core Connected!");
#endif
                onConnection();
            }
            else
            {
                hasFailed = true;
#ifdef ARDUINO_DEBUG
                Serial.println("IOT Core Connection Failed!");
#endif
                onFailedConnection();
            }
        }

#ifdef ARDUINO_DEBUG
        // char buffer[32] = {};
        // if (LoopSystem::loopCount % 10000 == 100)
        // {
        //     Serial.println("sending message");
        //     // Serial.println(String() + "remaining memory: " + RemainingMemory());
        //     int len = sprintf(buffer, "%d,", LoopSystem::loopCount);
        //     Publish(buffer, len);
        // }
#endif
    }
};
