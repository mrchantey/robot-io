
class RGBWSetter : public ActionBase<float>
{

  public:
    RgbwLedStrip<3, 60> *ledStrip;
    RGBWSetter(RgbwLedStrip<3, 60> *_ledStrip)
    {
        ledStrip = _ledStrip;
    }
    void Invoke(float data)
    {
        Serial.println(data);
        ledStrip->SetAllLeds(CRGBW(0, 0, 0, 0), false);
        // ledStrip->SetFromNormal(zNorm, CRGBW(32, 32, 0, 16), false);

        ledStrip->SetFromNormal(data, CRGBW(32, 32, 0, 16), false);
        ledStrip->Render();
    }
};

MPU6050 *mpu;
RgbwLedStrip<3, 60> *ledStrip;
PropertyGetter<MPUData, Vector3Int> *accGetter;
PropertyGetter<Vector3Int, int> *zGetter;
DataLogger<float> *logger;
ValueMapper<int, float> *mapper;
ValueMapper<float, float> *mapSin2Strip;
PolygonConstructor *polygonConstructor;
FunctionAction<float> *sinAction;
RGBWSetter *setter;

void setup()
{
    Serial.begin(9600);
    // Serial.println("hello world");
    mpu = new MPU6050();
    accGetter = new PropertyGetter<MPUData, Vector3Int>(&MPUData::acc);
    zGetter = new PropertyGetter<Vector3Int, int>(&Vector3Int::z);
    // mapper = new ValueMapper<int, float>(-32768, 32767, -1, 1);
    mapper = new ValueMapper<int, float>(-32768, 32767, -PI, PI);
    polygonConstructor = new PolygonConstructor(3, 0.6);

    // sinAction = new FunctionAction<float>(&Math::Sin<float>);
    // mapSin2Strip = new ValueMapper<float, float>(-1, 1, 0, 1);
    ledStrip = new RgbwLedStrip<3, 60>();
    setter = new RGBWSetter(ledStrip);

    logger = new DataLogger<float>("z: ");
    mpu->onData = accGetter;
    accGetter->onData = zGetter;
    zGetter->onData = mapper;
    // mapper->onData = sinAction;
    mapper->onData = polygonConstructor;
    polygonConstructor->onData = setter;

    // sinAction->onData = mapSin2Strip;
    // mapSin2Strip->onData = setter;
}