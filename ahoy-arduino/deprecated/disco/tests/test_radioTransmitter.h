
MPU6050 *mpu;

// JsonObjectTransmitAction<MPUData> *action;
MPUTransmitAction *action;
// LoopDataLogger *loopLogger;

void setup()
{
    Serial.begin(9600);
    // loopLogger = new LoopDataLogger();
    RadioTransmitter::Init();

    mpu = new MPU6050(true);
    action = new MPUTransmitAction();
    mpu->onData->AddAction(action);

    // action = new JsonObjectTransmitAction<MPUData>("mpuData");
}
