#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

class Radio
{
    //   protected:

  public:
    static ubyte ledPin;
    static RH_ASK driver;
    static bool hasIntitialized;
    static void Init(ubyte _ledPin = LED_BUILTIN)
    {
        if (hasIntitialized)
            return;
        hasIntitialized = true;
        ledPin = _ledPin;

        pinMode(ledPin, OUTPUT);
        if (!driver.init())
            Serial.println("radio init failed");
        else
        {
            Serial.println("radio initializing..");
            Serial.print("Max message length in bytes:");
            Serial.println(RH_ASK_MAX_MESSAGE_LEN);
        }
    }
};
bool Radio::hasIntitialized = false;
ubyte Radio::ledPin = 0;
RH_ASK Radio::driver;
// class RadioBase
// {

//   public:
//     RH_ASK driver;
//     RadioBase(ubyte _ledPin = LED_BUILTIN)
//     {
//         ledPin = _ledPin;
//         pinMode(ledPin, OUTPUT);
//         if (!driver.init())
//             Serial.println("radio init failed");
//         else
//         {
//             Serial.println("radio initializing..");
//             Serial.print("Max message length in bytes:");
//             Serial.println(RH_ASK_MAX_MESSAGE_LEN);
//         }
//     }

//   protected:
//     ubyte ledPin;
// };
