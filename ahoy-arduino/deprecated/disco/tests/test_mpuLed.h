
MPU6050 *mpu;
RgbwLedStrip<3, 60> *ledStrip;

// class

class MpuTransform
{

  public:
    static StaticAction<MPUData> *doTransform;
    static void Transform(MPUData data)
    {
        float z = data.acc.z;
        float zNorm = Math::Map(z, -32768, 32767, 0, 1);
        float invZNorm = 1 - zNorm;

        String str = String() + "raw: " + z + "\tnormalized: " + zNorm;

        ledStrip->SetAllLeds(CRGBW(0, 0, 0, 0), false);
        // ledStrip->SetFromNormal(zNorm, CRGBW(32, 32, 0, 16), false);
        ledStrip->SetFromNormal(invZNorm, CRGBW(32, 32, 0, 16), false);
        ledStrip->Render();

        Serial.println(str);
        // float zNormal = Math::Lerp(abs())
    }
};
StaticAction<MPUData> *MpuTransform::doTransform = new StaticAction<MPUData>(&MpuTransform::Transform);

void setup()
{
    Serial.begin(115200);
    mpu = new MPU6050();
    ledStrip = new RgbwLedStrip<3, 60>();
    mpu->onData = MpuTransform::doTransform;
}