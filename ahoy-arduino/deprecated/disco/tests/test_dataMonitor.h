

UltraSound *ultraSound;
DataMonitor<ulong> *dataMonitor;

void setup()
{
    Serial.begin(115200);
    Serial.println("initializing");

    ultraSound = new UltraSound(4, 2);
    dataMonitor = new DataMonitor<ulong>(ultraSound);
}