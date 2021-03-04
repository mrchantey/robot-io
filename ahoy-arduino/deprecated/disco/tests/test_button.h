#include "button.h"


// #include "discoAction.h"
// #include <time.h>
// #include "appState.h"

Button *button;
LoggerAction *pressedAction;
LoggerAction *releasedAction;
int count = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("bang");

    pressedAction = new LoggerAction("Button was Pressed");
    releasedAction = new LoggerAction("Button was Released");
    button = new Button(12);
    button->OnButtonPressed->action = pressedAction;
    button->OnButtonReleased->action = releasedAction;
}

void loop()
{
    // AppState::Update();
    // AppState::Print();
    // button->Update();
    // count++;
    // Serial.print(button->value);
}