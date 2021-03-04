
#pragma once
volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high

class IMU_MPU6050 : public DataGetterAction<IMUData>
{

private:
  const int MPU_addr = 0x68;
  MPU6050 mpu;
  // MPU control/status vars
  bool dmpReady = false;  // set true if DMP init was successful
  uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
  uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
  uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
  uint16_t fifoCount;     // count of all bytes currently in FIFO
  uint8_t fifoBuffer[64]; // FIFO storage buffer

  // orientation/motion vars
public:
public:
  IMU_MPU6050(bool _autoRepeat = true, byte interruptPin = 2) : DataGetterAction<IMUData>(_autoRepeat)
  {
    Init(interruptPin);
  }

private:
  static void dmpDataReady()
  {
    mpuInterrupt = true;
  }

public:
  void Init(ubyte interruptPin)
  {
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties

    // initialize device
    // Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(interruptPin, INPUT);

    // verify connection
    // Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    //    mpu.setXGyroOffset(220);
    //    mpu.setYGyroOffset(76);
    //    mpu.setZGyroOffset(-85);
    //    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
      // turn on the DMP, now that it's ready
      // Serial.println(F("Enabling DMP..."));
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      // Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
      // Serial.print(digitalPinToInterrupt(interruptPin));
      // Serial.println(F(")..."));
      attachInterrupt(digitalPinToInterrupt(interruptPin), IMU_MPU6050::dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      // Serial.println(F("DMP ready! Waiting for first interrupt..."));
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
    }
  }
  void Invoke(NoType nt = noType)
  {
    IMUData data = GetImuData();
    // if (!GetImuData())
    // return;
    // if (data != )
    onData->Invoke(data);
  }
  IMUData GetImuData()
  {
    // if programming failed, don't try to do anything
    if (!dmpReady)
      return IMUData();

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize)
    {
      if (mpuInterrupt && fifoCount < packetSize)
      {
        // try to get out of the infinite loop
        fifoCount = mpu.getFIFOCount();
      }
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024)
    {
      // reset so we can continue cleanly
      mpu.resetFIFO();
      fifoCount = mpu.getFIFOCount();
      Serial.println(F("FIFO overflow!"));
      return IMUData();
      // otherwise, check for DMP data ready interrupt (this should happen frequently)
    }
    else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT))
    {
      // Serial.println("fetching data");
      // wait for correct available data length, should be a VERY short wait
      while (fifoCount < packetSize)
        fifoCount = mpu.getFIFOCount();

      // read a packet from FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);

      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;

      Quaternion q;        // [w, x, y, z]         quaternion container
      VectorInt16 aa;      // [x, y, z]            accel sensor measurements
      VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
      VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
      VectorFloat gravity; // [x, y, z]            gravity vector
      float euler[3];      // [psi, theta, phi]    Euler angle container
      float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetAccel(&aa, fifoBuffer);

      mpu.dmpGetEuler(euler, &q);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

      mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
      mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
      const int mult = 10000;
      ypr[0] *= mult;
      ypr[1] *= mult;
      ypr[2] *= mult;
      euler[0] *= mult;
      euler[1] *= mult;
      euler[2] *= mult;

      Vec3Int accVec = Vec3Int(aa.x, aa.y, aa.z);
      Vec3Int eulerVec = Vec3Int(euler[0], euler[1], euler[2]);
      Vec3Int gravityVec = Vec3Int(gravity.x, gravity.y, gravity.z);
      Vec3Int yprVec = Vec3Int(ypr[0], ypr[1], ypr[2]);
      Vec3Int accLinVec = Vec3Int(aaReal.x, aaReal.y, aaReal.z);
      Vec3Int accLinWorldVec = Vec3Int(aaWorld.x, aaWorld.y, aaWorld.z);

      IMUData imuData = IMUData::FromI2CDevLib(accVec, eulerVec, gravityVec, yprVec, accLinVec, accLinWorldVec);
      // IMUData imuData = IMUData::FromI2CDevLib(eulerVec, yprVec);
      // onData->Invoke(imuData);

      return imuData;
    }
  }
};
