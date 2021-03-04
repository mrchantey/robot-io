

#include <iostream>
#include <cstring>
// #include <stdlib.h>
#include <stdio.h>
// #include "dataParser.h"
#include "jsonParser.h"

// uint8_t test[128] = {11, 11, 11, 11, 41, 138, 233, 224, 0, 1, 2, 3, 4, 5, 57, 204, 102, 201, 11, 11, 11};

int numInt = 696969;
float numFloat = 0.123456789;

JsonParser *jsonParser;

char testArr[32] = "[0,0.12345678,2,3.33,4,5,6]";

int main()
{
    jsonParser = new JsonParser();
    jsonParser->ReceiveInt(4555);
    jsonParser->ReceiveFloat(9.8765432);

    // jsonParser->ReceiveJsonCharArray(testArr, 32);

    int a = jsonParser->ParseInt();
    std::cout << "value: ";
    std::cout << a;
    std::cout << "\n";

    float b = jsonParser->ParseFloat();
    std::cout << "value: ";
    std::cout << b;
    std::cout << "\n";

    return 0;
}