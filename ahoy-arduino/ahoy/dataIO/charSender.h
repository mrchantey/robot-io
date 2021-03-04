#pragma once

#include "./charBuffer.h"
#include "../utility/ftoa.h"
void __emptyFunc(char *, int) {}

class CharSender : public CharBuffer
{
	const static uint16_t BASE_10 = 10;

public:
	void (*onPublish)(char *, int) = __emptyFunc;

	CharSender()
	{
		Append('[');
	}

	void Publish(bool resetBuffer = true)
	{
		int nullIndex = GetNullIndex();
		if (nullIndex <= 1) //empty, only a bracket
			return;
		if (buffer[nullIndex - 1] == ',')
			buffer[nullIndex - 1] = ']';
		else
			Append(']');

#ifdef ARDUINO_DEBUG
		Serial.println(String() + "charSender - Publishing..");
		Serial.println(buffer);
#endif
		onPublish(buffer, GetNullIndex());
		if (resetBuffer)
			ResetAndAppend();
	}
	void ResetAndAppend()
	{
		Reset();
		Append('[');
	}

	void Serialize(int val)
	{
		char temp[10] = {};
		itoa(val, temp, BASE_10);
		strcat(buffer, temp);
		strcat(buffer, ",");
	}

	void Serialize(long val)
	{
		char temp[20] = {};
		ltoa(val, temp, BASE_10);
		strcat(buffer, temp);
		strcat(buffer, ",");
	}

	void Serialize(float val)
	{
		char temp[10] = {};
		ftoa(val, temp);
		strcat(buffer, temp);
		strcat(buffer, ",");
	}
	void Serialize(double val)
	{
		char temp[10] = {};
		ftoa(val, temp);
		strcat(buffer, temp);
		strcat(buffer, ",");
	}

	void Serialize(char *val)
	{
		strcat(buffer, val);
		strcat(buffer, ",");
	}
};