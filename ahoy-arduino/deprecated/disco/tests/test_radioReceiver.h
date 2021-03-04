
// RadioReceiver *receiver;

// DataLogger<String> *logger;

DiscoDataLogger<DiscoArray<ubyte>> *logger;

void setup()
{
  Serial.begin(9600); // Debugging only

  logger = new DiscoDataLogger<DiscoArray<ubyte>>("<", ">", true, true);

  // logger = new DataLogger<String>("", false);
  // logger = new DataLogger<String>("");
  RadioReceiver::onReceive->AddAction(logger);
  RadioReceiver::Init();

  // receiver = new RadioReceiver();
  // LoopSystem::AddListener(receiver->doListen);
}
