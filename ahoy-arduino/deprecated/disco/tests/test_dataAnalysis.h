
MPU6050 *mpu;
MPURobotIOTransmitter *transmitter;
ActionArray<MPUData, 2> *splitter;
PropertyGetter<MPUData, Vector3Int> *accGetter;
PropertyGetter<Vector3Int, int> *zGetter;

ActionArray<int, 2> *accZSplitter;
RobotIOTransmitter<int> *directionChangeTransmitter;
RobotIOTransmitter<int> *accZTransmitter;

DirectionChangeDetector<int> *directionChangeDetector;
void setup()
{
    Serial.begin(115200);
    // Serial.begin(9600);
    Serial.flush();
    // Serial.println();
    Serial.print("\r\n*");

    RobotIOSystem::BeginInitTransmission();
    ubyte accChartId = RobotIOSystem::InitChart("Acc Z");
    // ubyte periodChartId = RobotIOSystem::InitChart("Period");
    // transmitter = new MPURobotIOTransmitter();
    accZTransmitter = RobotIOSystem::InitTransmitter<int>("z", accChartId);
    directionChangeTransmitter = RobotIOSystem::InitTransmitter<int>("direction change", accChartId, "markers");
    RobotIOSystem::EndInitTransmission();

    mpu = new MPU6050();
    accGetter = new PropertyGetter<MPUData, Vector3Int>(&MPUData::acc);
    mpu->onData = accGetter;
    zGetter = new PropertyGetter<Vector3Int, int>(&Vector3Int::z);
    accGetter->onData = zGetter;
    accZSplitter = new ActionArray<int, 2>();
    zGetter->onData = accZSplitter;
    accZSplitter->AddAction(accZTransmitter->doUpdateData);

    directionChangeDetector = new DirectionChangeDetector<int>(0);
    accZSplitter->AddAction(directionChangeDetector);
    directionChangeDetector->onDirectionChange = directionChangeTransmitter->doUpdateData;

    LoopSystem::AddListener(RobotIOSystem::doTransmitData);

    // RobotIOSystem::TransmitData();
}