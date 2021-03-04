#include <iostream>
#include <cstring>
// #include <stdio>
#include "../ahoy/utility/utility.h"
using namespace std;

char buffer[64];
static const int MAX_VALUES = 64;
char *valuesBuffer[MAX_VALUES] = {};

int parseValuesBuffer(char **_valuesBuffer, int index)
{
	printf("value: %s", _valuesBuffer[index]);
	return index;
}

int main()
{
	// printf("hello world");

	strcpy(buffer, "[9,220,0,255,0,1,0.9]");
	SplitStringArray(buffer, valuesBuffer, MAX_VALUES);

	int valueIndex = 0;
	int lastValueIndex = 0;
	while (valuesBuffer[valueIndex] != NULL || valueIndex >= MAX_VALUES)
	{
		valueIndex = parseValuesBuffer(valuesBuffer, valueIndex);
		if (valueIndex == lastValueIndex)
			valueIndex++;
		lastValueIndex = valueIndex;
	}

	return 0;
}
