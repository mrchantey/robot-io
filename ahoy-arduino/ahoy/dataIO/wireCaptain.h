#pragma once

// #include "../utility/ftoa.h"
#include "./charBuffer.h"
#include "../led/definitions.h"
//ESP8266 DATA

//https://robotdyn.com/uno-wifi-r3-atmega328p-esp8266-32mb-flash-usb-ttl-ch340g-micro-usb.html
// //esp8266 corresponding GPIO pin
// //static const uint8_t D0   = 16;
// static const uint8_t D1   = 5; //SCL
// static const uint8_t D2   = 4; //SDA
// //static const uint8_t D3   = 0;
// //static const uint8_t D4   = 2;
// static const uint8_t D5   = 14;
// static const uint8_t D6   = 12;
// static const uint8_t D7   = 13;
// //static const uint8_t D8   = 15;
// //static const uint8_t D9   = 3;
// //static const uint8_t D10  = 1;
#include <Wire.h>
//https://www.arduino.cc/en/Reference/Wire

//https://www.arduino.cc/en/Reference/WireEndTransmission

//SHOULD USE WIRE END ERROR CODES TO SEND DATA

// Nobody talks to the captain
// A wire captain talks to sailors, but sailors do not talk to captain

class WireCaptain : public CharBuffer
{

public:
	static const int sailorAddress = 8;
	int numSailors = 0;
	WireCaptain()
	{
		PingSailors();
	}

	void PingSailors()
	{
		Set(MKEY_AWAKE);
		bool sailorPresent = true;
#ifdef ARDUINO_DEBUG
		Serial.println("Pinging sailors...");
#endif
		while (sailorPresent)
		{
			int address = sailorAddress + numSailors;
			sailorPresent = Send(address, 2000); //less tolerance for initial ping?
			if (sailorPresent)
				numSailors++;
			yield();
		}
#ifdef ARDUINO_DEBUG
		Serial.print(numSailors);
		Serial.println(" sailors found");
// Serial.println();
#endif
	}

	bool SetAndSend(int command, int address)
	{
		Set(command);
		return Send(address);
	}
	bool SetAndSend(char *arr, int len, int address)
	{
		Set(arr, len);
		return Send(address);
	}
	bool SetAndSend(char *arr, int address)
	{
		Set(arr);
		return Send(address);
	}

	bool SetAndSend(String str, int address)
	{
		Set(str);
		return Send(address);
	}
	bool SetAndSendAll(int command)
	{
		Set(command);
		return SendAll();
	}
	bool SetAndSendAll(char *arr, int len)
	{
		Set(arr, len);
		return SendAll();
	}
	bool SetAndSendAll(char *arr)
	{
		Set(arr);
		return SendAll();
	}

	bool SetAndSendAll(String str)
	{
		Set(str);
		return SendAll();
	}

	void Set(int command)
	{
		Reset();
		sprintf(buffer, "[%d]", command);
	}

	void Set(char *arr)
	{
		Reset();
		int i = 0;
		while (arr[i] != '\0')
			Append(arr[i++]);
	}

	void Set(char *arr, size_t len)
	{
		Reset();
		for (int i = 0; i < len; i++)
			Append(arr[i]);
	}

	void Set(String str)
	{
		Reset();
		str.toCharArray(buffer, CharBuffer::CHAR_BUFFER_SIZE);
	}

	bool SendAll()
	{
		bool success = true;
		for (int i = 0; i < numSailors; i++)
		{
			if (!Send(sailorAddress + i))
				success = false;
		}
		return success;
	}

	bool Send(int address, int timeout = 5000)
	{
		int nullIndex = GetNullIndex();
#ifdef ARDUINO_DEBUG
		Serial.println("wire message");
		Serial.println(buffer);
		Serial.println("sending...");
		long messageStartMillis = millis();
#endif
		for (int i = 0; i < nullIndex; i++)
		{
			if (DefinatelySendChar(address, buffer[i], timeout) == false)
			{
#ifdef ARDUINO_DEBUG
				Serial.println("wire transmit timeout");
#endif
				return false;
			}
		}
		Wire.beginTransmission(address);
		Wire.endTransmission(true); //does this get set even if failed?

#ifdef ARDUINO_DEBUG
		long deltaMillis = millis() - messageStartMillis;
		Serial.println();
		Serial.print("Message sent in ");
		Serial.print(deltaMillis);
		Serial.println(" milliseconds");
#endif
		return true;
	}

	bool DefinatelySendChar(int address, char c, int timeout = 5000)
	{
		long byteStartMillis = millis();
		byte status = -1;
		while (status != 0)
		{
			Wire.beginTransmission(address);
			Wire.write(c);
			status = Wire.endTransmission(false); //will return > 0 if error, usually 2 for no address ack
			long deltaMillis = millis() - byteStartMillis;
			if (deltaMillis > timeout)
				return false;
			yield(); //Not yielding for over a second can cause a crash
		}
		return true;
	}
};

// WIRE ERROR CODES
// 0:success
// 1:data too long to fit in transmit buffer
// 2:received NACK on transmit of address
// 3:received NACK on transmit of data
// 4:other error

/*
PIN DIAGRAM
ESP PINS
0 0 2 4
0 0 0 0
0 0 0 0
*/
WireCaptain *___wireCaptain;

//for dual board set clock to 2
WireCaptain *InitializeWireCaptain(int sda = 4, int scl = 5)
// WireCaptain *InitializeWireCaptain()
{
	Wire.begin(sda, scl); //needs to be in global function?
	// Wire.begin();
	___wireCaptain = new WireCaptain();
	// ___wireCaptain->PingSailors();

	// Wire.onRequest([]() { ___wireCaptain->HandleRequest(); });
	// Wire.onReceive([](int numBytes) { ___wireCaptain->HandleReceive(numBytes); });
	return ___wireCaptain;
}