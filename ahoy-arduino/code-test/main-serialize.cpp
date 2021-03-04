

#include <iostream>
#include <cstring>
#include "./ftoa.h"

int valuesI[4] = {0, 1, 2, 3};
float valuesF[4] = {0.01234, 100000, 20.3456, 3.45678901234};
char buff[128] = {};
char tmp[16] = {};
char seperator[2] = ",";

int precision = -1;
int main()
{
    itoa(valuesI[0], tmp, 10);
    strcat(buff, tmp);
    strcat(buff, seperator);
    itoa(valuesI[1], tmp, 10);
    strcat(buff, tmp);
    strcat(buff, seperator);
    itoa(valuesI[2], tmp, 10);
    strcat(buff, tmp);
    strcat(buff, seperator);
    itoa(valuesI[3], tmp, 10);
    strcat(buff, tmp);
    strcat(buff, seperator);
    ftoa(valuesF[0], tmp, precision);
    strcat(buff, tmp);
    strcat(buff, seperator);
    ftoa(valuesF[1], tmp, precision);
    strcat(buff, tmp);
    strcat(buff, seperator);
    ftoa(valuesF[2], tmp, precision);
    strcat(buff, tmp);
    strcat(buff, seperator);
    ftoa(valuesF[3], tmp, precision);
    strcat(buff, tmp);
    // strcat(buff, seperator);
    printf(buff);
    return 0;
}