#define ARDUINO_DEBUG //uncomment this line for production
/*docs 
https://robotdyn.com/uno-wifi-r3-atmega328p-esp8266-32mb-flash-usb-ttl-ch340g-micro-usb.html
https://www.jaycar.com.au/medias/sys_master/images/9353588998174/XC4411-manualMain.pdf
https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
*/
#include "../ahoy/ahoy.h"
#include "../ahoy/wifi/includeAdafruitWifi.h"
// #include "../ahoy/dataIO/includeDataIO.h"
#include "../ahoy/led/definitions.h"

AdafruitClient *client;
DataIO *dataIO; //USE FOR SENDING ONLY

void HandleConnecting()
{
#ifdef ARDUINO_DEBUG
	Serial.println();
	Serial.println(String() + "CONNECTING...");
	Serial.println("BEGIN BUFFER:");
#endif
	// dataIO->SerializeMessageB(MKEY_CONNECTION_CONNECTING);
#ifdef ARDUINO_DEBUG
	Serial.println(String() + ":END BUFFER");
#endif
}

void HandleConnected()
{
#ifdef ARDUINO_DEBUG
	Serial.println();
	Serial.println(String() + "CONNECTED! Time: " + LoopSystem::ElapsedSeconds());
	Serial.println("BEGIN BUFFER:");
#endif
	// dataIO->SerializeMessageB(MKEY_CONNECTION_CONNECTED);
	// dataIO->SerializeMessageBBII(MKEY_LED_INDICIES, 0, 0, 12);
	// dataIO->SerializeMessageBBB(MKEY_LED_MODE, 0, ANIM_SOLID);
#ifdef ARDUINO_DEBUG
	Serial.println(String() + ":END BUFFER");
#endif
}

// void HandleReceiveMessage(uint8_t *data)
// {
// #ifdef ARDUINO_DEBUG
//     Serial.print(String() + "BUFFER START:");
// #endif
//     for (int i = 0; i < DataParser::RECV_BUFF_LEN; i++)
//     {
//         Serial.print(data[i]);
//     }
//     // Serial.write(data, DataParser::RECV_BUFF_LEN);
// #ifdef ARDUINO_DEBUG
//     Serial.println(String() + ":END");
// #endif
// }

StaticNullAction *handleConnecting = new StaticNullAction(HandleConnecting);
StaticNullAction *handleConnected = new StaticNullAction(HandleConnected);
// StaticAction<uint8_t *> *handleReceiveMessage = new StaticAction<uint8_t *>(HandleReceiveMessage);

void setup()
{
	Serial.begin(115200);
	while (!Serial)
		continue;
	Serial.println();
	delay(1000);
#ifdef ARDUINO_DEBUG
#endif
	client = new AdafruitClient();
	dataIO = new DataIO();

	// dataIO->onMessage->AddAction(handleReceiveMessage);

	client->onConnecting->AddAction(handleConnecting);
	client->onConnected->AddAction(handleConnected);
	client->Connect();
}

void loop()
{
	LoopSystem::Update();
}
