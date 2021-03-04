

MPU6050 *mpu;
PropertyGetter<MPUData, Vector3Int> *accGetter;
PropertyGetter<Vector3Int, int> *zGetter;
// DiscoDataLogger<> *logger;
// DataLogger<int> *logger;
DataLogger<float> *logger;
ValueMapper<int, float> *mapper;
FunctionAction<float> *sinAction;

void setup()
{
    Serial.begin(9600);
    Serial.println("hello world");
    mpu = new MPU6050();
    accGetter = new PropertyGetter<MPUData, Vector3Int>(&MPUData::acc);
    zGetter = new PropertyGetter<Vector3Int, int>(&Vector3Int::z);
    // mapper = new ValueMapper<int, float>(-32768, 32767, -1, 1);
    mapper = new ValueMapper<int, float>(-32768, 32767, -PI / 2, PI / 2);
    sinAction = new FunctionAction<float>(&Math::Sin<float>);

    logger = new DataLogger<float>("z: ");
    mpu->onData = accGetter;
    accGetter->onData = zGetter;
    zGetter->onData = mapper;
    mapper->onData = sinAction;
    sinAction->onData = logger;
}