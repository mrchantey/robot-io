#pragma once
#include "../ahoy/dataIO/charSender.h"
#include "../ahoy/dataIO/charReceiver.h"
#include "../ahoy/modules/rootModule.h"
#include "../ahoy/modules/definitions.h"
#include "./iotController.h"
#include "./utility/throttle.h"

#define PUBLISH_INTERVAL_MILLIS 10000

class ChanteyDevice;

ChanteyDevice *_chanteyDevice;

class ChanteyDevice
{
public:
	CharSender *charSender;
	CharReceiver *charReceiver;
	IotController *iotController;
	RootModule *rootModule;

	Throttle *publishThrottle;

	ChanteyDevice()
	{
		#ifdef ARDUINO_DEBUG
		Serial.begin(115200);
		Serial.println();
		Serial.println("----CHANTEY DEVICE----");
		#endif

		_chanteyDevice = this;

		publishThrottle = new Throttle(PUBLISH_INTERVAL_MILLIS);
		publishThrottle->onTrigger = HandlePublishThrottleTrigger;

		rootModule = new RootModule();
		rootModule->onPublishDouble = HandlePublish;
		rootModule->onPublishLong = HandlePublish;

		charSender = new CharSender();
		charSender->onPublish = HandlePublishTelemetry;

		charReceiver = new CharReceiver();
		charReceiver->onValues = HandleOnValues;

		iotController = new IotController();
		iotController->onMessageInt = HandleReceiveMessage;
		iotController->onMessageString = HandleReceiveMessage;
		iotController->Begin();

	}

	void Update()
	{
		iotController->Update();
		rootModule->Update();
		publishThrottle->Update();
	}

	static void HandleOnValues(char **values, int maxIndex)
	{
		_chanteyDevice->rootModule->HandleOnValues(values, maxIndex);
	}

	static void HandlePublish(long val)
	{
		_chanteyDevice->charSender->Serialize(val);
	}
	static void HandlePublish(double val)
	{
		_chanteyDevice->charSender->Serialize(val);
	}

	static void HandleReceiveMessage(int val)
	{
		_chanteyDevice->charReceiver->ReceiveIntMessage(val);
	}

	static void HandleReceiveMessage(String &val)
	{
		_chanteyDevice->charReceiver->Receive(val);
	}

	static void HandlePublishTelemetry(char *data, int length)
	{
		_chanteyDevice->iotController->googleIot->publishTelemetry(data, length);
	}

	static void HandlePublishThrottleTrigger()
	{
		if (_chanteyDevice->iotController->accessPointMode ||
			!_chanteyDevice->iotController->wifiStationary->isConnected)
			_chanteyDevice->charSender->ResetAndAppend();
		else
			_chanteyDevice->charSender->Publish();
	}
};