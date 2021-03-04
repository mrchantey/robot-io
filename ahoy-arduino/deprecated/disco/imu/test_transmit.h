
// MPU6050 *mpu;
// MPURobotIOTransmitAction *action;
// MPURobotIOTransmitter *transmitter;

void setup()
{

    Serial.begin(115200);
    while (Serial.available() && Serial.read())
        ; // empty buffer
    Serial.print("\r\n*");
    mpu = new MPU6050();
    // RobotIOSystem::BeginInitTransmission();
    // transmitter = new MPURobotIOTransmitter();
    // RobotIOSystem::EndInitTransmission();

    // mpu->onData = transmitter;
    // LoopSystem::AddListener(RobotIOSystem::doTransmitData);
    // RobotIOSystem::TransmitData();
}