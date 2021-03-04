#pragma once

static void SplitStringArray(char *str, char **valuesBuffer, int maxValues)
{
	const char delimiters[] = "[,]";
	//int count = 0
	char *ptr = strtok(str, delimiters);
	//if ptr != NULL  count++
	for (int i = 0; i < maxValues; i++)
	{
		//if ptr != NULL count++
		// printf("%d", i);
		valuesBuffer[i] = ptr; //this will set all empty values to null all null values
		ptr = strtok(NULL, delimiters);
	}
}