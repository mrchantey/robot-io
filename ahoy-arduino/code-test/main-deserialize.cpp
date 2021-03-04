

#include <iostream>
#include <cstring>

char buff[] = "[123456789,0.123456789,3433,gdaymate]";
const int NUM_VALUES = 8;
char *values[NUM_VALUES];

int main()
{
    std::cout << "hello world\n";
    printf("formatting string: %s\n", buff);

    const char delimiters[] = "[,]";
    char *ptr;
    ptr = strtok(buff, delimiters);

    for (int i = 0; i < NUM_VALUES; i++)
    {
        values[i] = ptr;
        printf("value string: %s\n", ptr);
        printf("formatted string: %s\n", buff);
        ptr = strtok(NULL, delimiters);
    }

    if (values[0] != NULL)
    {
        int val = atoi(values[0]);
        printf("value 0: %d\n", val);
    }
    if (values[1] != NULL)
    {
        float val = atof(values[1]);
        printf("value 1: %f\n", val);
    }
    if (values[2] != NULL)
    {
        int val = atoi(values[2]);
        printf("value 2: %d\n", val);
    }
    if (values[3] != NULL)
    {
        char *val = values[3];
        // int val = atoi(values[0]);
        printf("value 3: %s\n", val);
    }

    while (ptr != NULL)
    {
    }

    return 0;
}