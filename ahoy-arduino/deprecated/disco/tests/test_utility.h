

#include "color.h"
#include "Arduino.h"

void setup()
{
    Serial.begin(115200);
    Color startCol = Color();
    Color endCol = Color(255, 255, 255);
    Serial.print("Start Color: ");
    startCol.Print();
    Serial.print("End Color: ");
    endCol.Print();
    for (float i = 0; i <= 1; i += 0.001)
    {
        Serial.print("Lerp Color: ");
        Color col = Color::Lerp(startCol, endCol, i);
        col.Print();
    }
}

void loop()
{
}