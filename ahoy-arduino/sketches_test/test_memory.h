#define ARDUINO_DEBUG

#include "../ahoy/systems/loopSystem.h"
#include "../ahoy/led/ledStripSK6812.h"
#include "../ahoy/led/ledController.h"
#include "../ahoy/dataIO/wireSailor.h"
#include "../ahoy/dataIO/ledIO.h"
#include "../ahoy/utility/RemainingMemory.h"

#define SAILOR_ADDRESS 8

WireSailor *wireSailor = InitializeWireSailor(SAILOR_ADDRESS);
// WireSailor *wireSailor = new WireSailor();

LedIO *ledIO;

LedStripSK6812 *strip;
LedController *controller;
LedConnection *ledConnection;

void HandleMessage(char **values) { ledIO->ReceiveMessage(values); }
void setup()
{
    Serial.begin(115200);
    strip = new LedStripSK6812();

    controller = new LedController(strip);    //166 bytes
    ledConnection = new LedConnection(strip); //31

    ledIO = new LedIO(controller, ledConnection); //6 bytes

    wireSailor->onMessage = [](char **values) { HandleMessage(values); };
    int remainingMemory = RemainingMemory();
    Serial.print("remaining memory: ");
    Serial.println(remainingMemory);
    Serial.print("delta memory: ");
    Serial.println(1428 - remainingMemory);
}

void loop()
{
    strip->SetRange(Color::Black());
    LoopSystem::Update();
    controller->Update();
    ledConnection->Update();
    strip->Render();
}