#include "dataTransmitter.h"

DataTransmitter::DataTransmitter()
{
    pinMode(LED_BUILTIN, OUTPUT);

    if (!driver.init())
        Serial.println("init failed");
    else
    {
        Serial.println("RF initialized..");
        Serial.print("max message length:");
        Serial.println(driver.maxMessageLength());
    }
}

void DataTransmitter::SendBytes(uint8_t *msg, uint8_t len)
{

    digitalWrite(LED_BUILTIN, HIGH);

    Serial.print("sending message of length: ");
    Serial.println(len);

    driver.send(msg, len);
    // driver.send(msg, 64);
    driver.waitPacketSent();

    digitalWrite(LED_BUILTIN, LOW);
}