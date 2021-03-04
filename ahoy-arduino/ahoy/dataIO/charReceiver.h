#pragma once
#include "./charBuffer.h"
#include "../utility/utility.h"
#include <Wire.h>

void __emptyFunc(char **, int) {}
// void __emptyFunc(char *,int) {}

class CharReceiver : public CharBuffer
{

public:
	// static const int MAX_VALUES = 64;
	bool isReceiving = false;
	static const int MAX_VALUES = 32;
	char *valuesBuffer[MAX_VALUES] = {};

	// void (*onMessage)(char *) = __emptyFunc;
	void (*onValues)(char **, int) = __emptyFunc;

	CharReceiver()
	{
	}

	void ReceiveIntMessage(int key)
	{
		Reset();
		// char buffer[32] = {};
		sprintf(buffer, "[%d]", key);
		// #ifdef ARDUINO_DEBUG
		// 		Serial.print("receiving int message: ");
		// 		Serial.print('\'');
		// 		Serial.print(buffer);
		// 		Serial.print('\'');
		// 		Serial.println();
		// #endif
		OnMessage();
	}

	void Receive(String str)
	{
		Reset();
		for (int i = 0; i < str.length(); i++)
		{
			char c = str.charAt(i);
			Append(c);
		}
		OnMessage();
	}

	void HandleReceiveWire(int numBytes)
	{
#ifdef ARDUINO_DEBUG
		Serial.print("receiving wire message...");
#endif
		while (Wire.available())
		{
			char c = Wire.read();
			Append(c);
			if (c == ']')
				OnMessage();
		}
	}

	void OnMessage()
	{
#ifdef ARDUINO_DEBUG
		Serial.print("Message Received:");
		Serial.println(buffer);
#endif
		// onMessage(buffer);
		SplitStringArray(buffer, valuesBuffer, MAX_VALUES);
		// ParseValuesBuffer();
		onValues(valuesBuffer, MAX_VALUES);
		Reset();
	}
};

CharReceiver *___wireCharReceiver;

CharReceiver *InitializeWireCharReceiver(int address = 8)
{
	___wireCharReceiver = new CharReceiver();
	Wire.begin(address);
	// Wire.onRequest([]() { ___wireSailor->HandleRequest(); });
	Wire.onReceive([](int numBytes) { ___wireCharReceiver->HandleReceiveWire(numBytes); });
	return ___wireCharReceiver;
}
