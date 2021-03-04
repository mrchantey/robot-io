#pragma once
namespace AppState
{

unsigned long frame = 0;
unsigned long lastMicros = 0;

unsigned long deltaMicros = 0;

float framesPerSecond = 0;

void Update()
{
    unsigned long nowMicros = micros();
    deltaMicros = (nowMicros - lastMicros);
    framesPerSecond = ((float)1 / deltaMicros) * 1000000;

    lastMicros = nowMicros;
    frame++;
}

void Print()
{
    Serial.print("Frame:\t");
    Serial.print(frame);
    Serial.print("\tMicros:\t");
    Serial.print(lastMicros);

    Serial.print("\tDelta Micros:\t");
    Serial.print(deltaMicros);
    Serial.print("\tFrames Per Second:\t");
    Serial.print(framesPerSecond);
    Serial.println();
}

} // namespace AppState
