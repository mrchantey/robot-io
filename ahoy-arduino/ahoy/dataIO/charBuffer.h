#pragma once

class CharBuffer
{
public:
	const static uint16_t CHAR_BUFFER_SIZE = 128;
	char buffer[CHAR_BUFFER_SIZE];

private:
	int bufferIndex = 0;

public:
	CharBuffer()
	{
		Reset();
	}

	void Append(char c)
	{
		if (bufferIndex + 1 == CHAR_BUFFER_SIZE)
		{
#ifdef ARDUINO_DEBUG
			Serial.println("Char buffer overflow, clearing");
#endif
			Reset();
		}
		else
		{
			buffer[bufferIndex++] = c;
		}
	}

	void Reset()
	{
		memset(buffer, 0x00, CHAR_BUFFER_SIZE);
		bufferIndex = 0;
	}

	int GetNullIndex()
	{
		for (int i = 0; i < CHAR_BUFFER_SIZE; i++)
		{
			if (buffer[i] == '\0')
				return i;
		}
		return -1;
	}
};