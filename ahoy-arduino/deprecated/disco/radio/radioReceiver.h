
class RadioReceiver
{

public:
  static ActionArray<DiscoArray<ubyte>> *onReceive;
  // Action<RadioReceiver, NoType> *doListen;

  static StaticAction<NoType> *doListen;

  static void Init()
  {
    Radio::Init();
    LoopSystem::onLoop->AddAction(doListen);
  }

  static void ListenForReceive()
  {

    ubyte buf[RH_ASK_MAX_MESSAGE_LEN] = {0};
    ubyte bufLen = sizeof(buf);
    // ubyte bufLen = 0;
    digitalWrite(Radio::ledPin, HIGH);
    if (Radio::driver.recv(buf, &bufLen)) // Non-blocking
    {
      DiscoArray<ubyte> data = DiscoArray<ubyte>(buf, bufLen);
      onReceive->Invoke(data);
      // Message with a good checksum received, dump it.
      // Serial.print("Message length: ");
      // Serial.print(bufLen);
      // Serial.print("\t Message: ");

      //FOR STRINGS

      // char msg[bufLen + 1];
      // for (int i = 0; i < bufLen; i++)
      // {
      //   msg[i] = buf[i];
      // }
      // msg[bufLen] = '\0';
      // // Serial.println(msg);
      // String msgStr = String(msg);
      // onReceive->Invoke(msgStr);
    }
    digitalWrite(Radio::ledPin, LOW);
  }
};

ActionArray<DiscoArray<ubyte>> *RadioReceiver::onReceive = new ActionArray<DiscoArray<ubyte>>();
StaticAction<NoType> *RadioReceiver::doListen = new StaticAction<NoType>(&RadioReceiver::ListenForReceive);

// class RadioReceiver : public RadioBase
// {

// public:
//   ActionArray<String> *onReceive;
//   Action<RadioReceiver, NoType> *doListen;
//   RadioReceiver() : RadioBase()
//   {
//     onReceive = new ActionArray<String>();
//     doListen = new Action<RadioReceiver, NoType>(this, &RadioReceiver::ListenForReceive);
//   }

//   void ListenForReceive()
//   {

//     ubyte buf[RH_ASK_MAX_MESSAGE_LEN] = {0};
//     ubyte bufLen = sizeof(buf);
//     // ubyte bufLen = 0;
//     digitalWrite(ledPin, HIGH);
//     if (driver.recv(buf, &bufLen)) // Non-blocking
//     {
//       // Message with a good checksum received, dump it.
//       Serial.print("Message length: ");
//       Serial.print(bufLen);
//       Serial.print("\t Message: ");
//       char msg[bufLen + 1];
//       for (int i = 0; i < bufLen; i++)
//       {
//         msg[i] = buf[i];
//       }
//       msg[bufLen] = '\0';
//       Serial.println(msg);

//       //          Serial.print((char*)buf);
//       //          Serial.print("\t");
//       //    for (int i = 0; i < (sizeof(buf) / sizeof(uint8_t)); i++)
//       //    byte az = buf[4];
//       // for (int i = 0; i < 8; i++)
//       // {
//       //   ubyte valSigned = buf[i];
//       //   Serial.print(valSigned);
//       //   Serial.print("\t");
//       // }
//       // Serial.println();
//     }
//     digitalWrite(ledPin, LOW);
//   }
// };