#define ARDUINO_DEBUG

#include "../ahoy/systems/loopSystem.h"

#include "../ahoy/led/ledStripSK6812.h"
#include "../ahoy/led/ledController.h"
#include "../ahoy/dataIO/wireSailor.h"
#include "../ahoy/dataIO/ledIO.h"

//shape,min,max,xyz,xyz
// char buff[] = "[5,1,0,0,0,0,0,0,0,0,0,9,1,0,1,0,255,0,1,0,0,255,0.5]";
// char buff[] = "[5,2,0,0,16,0,0,0,1,0,0,0,17,33,0,0,0,0,0,1,9,1,0,-0.2,0,255,0,1,0,0,255,1]";
// char buff[] = "[5,2,0,0,4,0,0,0,1,0,0,0,5,9,0,0,0,0,0,1,9,1,1,1,0,255,0,1,0,0,255,1]";

#define SAILOR_ADDRESS 8

WireSailor *wireSailor = InitializeWireSailor(SAILOR_ADDRESS);

LedIO *ledIO;

LedStripSK6812 *strip;
LedController *controller;
LedConnection *ledConnection;

void HandleMessage(char **values) { ledIO->ReceiveMessage(values); }
void setup()
{
    Serial.begin(115200);
    strip = new LedStripSK6812();

    controller = new LedController(strip);
    ledConnection = new LedConnection(strip);

    ledIO = new LedIO(controller, ledConnection);
    // wireSailor->onMessage = [&](char **values) { ledIO->ReceiveMessage(values); };
    wireSailor->onMessage = [](char **values) { HandleMessage(values); };
    // wireSailor->Receive("[5,2,0,0,16,0,0,0,1,0,0,0,17,33,0,0,0,0,0,1,9,1,0,-0.2,0,255,0,1,0,0,255,1]");
}

void loop()
{
    LoopSystem::Update();
    controller->Update();
    ledConnection->Update();
    strip->Render();
    // #ifdef ARDUINO_DEBUG
    //     Serial.println();
    // #endif
}