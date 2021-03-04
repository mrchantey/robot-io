

class ProximityDetector
{

  public:
    UltraSound *ultraSound;
    DataMonitor<ulong> *dataMonitor;
    ProximityDetector()
    {
        ultraSound = new UltraSound(4, 2);
        dataMonitor = new DataMonitor<ulong>(ultraSound);
    }
};