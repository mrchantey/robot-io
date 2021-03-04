
#include "disco.h"

class PirateShip
{

  public:
    void SetSail(){

    };

    static void StaticSetSail()
    {
        Serial.println("yep, im sailing");
    }
};

StaticAction<NoType> *myAction;
void setup()
{
    Serial.begin(9600);
    Serial.println("yarr");

    // Radio::Init();

    myAction = new StaticAction<NoType>(&PirateShip::StaticSetSail);
    myAction->Invoke();

    // Action<PirateShip, NoType> *pirateAction = new Action<PirateShip, NoType>();

    // LoggerAction *loggerAction1 = new LoggerAction("action 1");
    // LoggerAction *loggerAction2 = new LoggerAction("action 2");

    // ActionArray<NoType, 2> *myActionArray = new ActionArray<NoType, 2>();
    // myActionArray->AddAction(loggerAction1);
    // myActionArray->AddAction(loggerAction2);

    // myActionArray->Invoke(NoType());
    // Serial.println("testing");
}
