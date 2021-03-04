#pragma once

//https://www.jaycar.com.au/medias/sys_master/images/9350632734750/XC4411-manualMain.pdf

#define IO_USERNAME "chantey"
#define IO_KEY "3e2bda1a2675454ab799b2e5d0531033"
#define WIFI_SSID "royalewithcheese"
#define WIFI_PASS "tastyburger"

// #define AIO_DATA_LENGTH 128
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

class AdafruitClient
{
public:
  AdafruitIO_Feed *feed;
  NullAction<AdafruitClient> *doUpdate;
  NullEvent<> *onConnecting;
  NullEvent<> *onConnected;
  // ActionArray<NoType> *onConnect;
  bool isConnected = false;

  AdafruitClient()
  {
    onConnecting = new NullEvent<>();
    onConnected = new NullEvent<>();

    feed = io.feed("ahoy-kitchen");
    feed->onMessage(handleMessage);

    doUpdate = new NullAction<AdafruitClient>(this, &AdafruitClient::Update);
    LoopSystem::AddListener(doUpdate);
  }

  void Connect()
  {
    io.connect();
    onConnecting->Invoke();
  }

  void Update()
  {
    if (!isConnected && !(io.mqttStatus() < AIO_CONNECTED))
    {
      isConnected = true;
      onConnected->Invoke();
    }
    else
    {
      io.run();
    }
  }

  static void handleMessage(AdafruitIO_Data *data) { Serial.println(data->value()); }
};
