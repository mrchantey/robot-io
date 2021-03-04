class LedIO
{
public:
    LedControllerRgbw *controller;
    Action<LedIO, uint8_t *> *doReceiveMessage;
    LedIO(LedControllerRgbw *_controller)
    {
        controller = _controller;
        doReceiveMessage = new Action<LedIO, uint8_t *>(this, &LedIO::ReceiveMessage);
    }
    void ReceiveMessage(uint8_t *msg)
    {
#ifdef ARDUINO_DEBUG
        Serial.println(String() + "Led IO - Message Received! key: " + msg[0]);
        // char *keyStr = GetMessageKeyString(msg[0]);
        // Serial.println(String() + "key: " + keyStr);
#endif
        if (msg[0] >= 100 && msg[0] <= 199)
            HandleConnectionMessage(msg);
        else if (msg[0] >= 200 && msg[0] <= 299)
            HandleLedMessage(msg);
#ifdef ARDUINO_DEBUG
        Serial.println();
#endif
    }

    void HandleConnectionMessage(uint8_t *msg)
    {
#ifdef ARDUINO_DEBUG
        Serial.println(String() + "Connection Message");
#endif
        int lastIndex = SEGMENTS_IN_CONTROLLER - 1;
        switch (msg[0])
        {
        case MKEY_CONNECTION_IDLE:
        {
            controller->segments[lastIndex]->SetColor(Color::White(), 0);
            controller->segments[lastIndex]->SetColor(Color::Black(), 1);
            controller->segments[lastIndex]->animationMode = ANIM_FADE;
            break;
        }
        case MKEY_CONNECTION_CONNECTING:
        {
            controller->segments[lastIndex]->SetColor(Color::Green(), 0);
            controller->segments[lastIndex]->SetColor(Color::Blue(), 1);
            controller->segments[lastIndex]->animationMode = ANIM_FADE;
            break;
        }
        case MKEY_CONNECTION_CONNECTED:
        {
            controller->segments[lastIndex]->animationMode = ANIM_OFF;
            break;
        }
        case MKEY_CONNECTION_FAILED:
        {
            controller->segments[lastIndex]->SetColor(Color::Red(), 0);
            controller->segments[lastIndex]->SetColor(Color::Black(), 1);
            controller->segments[lastIndex]->animationMode = ANIM_FADE;
            break;
        }
        }
    }

    void HandleLedMessage(uint8_t *msg)
    {
#ifdef ARDUINO_DEBUG
        Serial.println(String() + "Led Message - Segment: " + msg[1]);
#endif
        switch (msg[0])
        {
        default:
            break;
        case MKEY_LED_MODE:
        {
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "mode: " + msg[2]);
#endif
            controller->segments[msg[1]]->animationMode = msg[2];
            break;
        }
        case MKEY_LED_INDICIES:
        {
            uint8_t imin = DataParser::BytesToInt16(msg, 2);
            uint8_t imax = DataParser::BytesToInt16(msg, 4);
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "imin: " + imin + "\timax: " + imax);
#endif
            controller->segments[msg[1]]->SetIndicies(imin, imax);
            break;
        }
        case MKEY_LED_BRIGHTNESS:
        {
            float brightness = DataParser::BytesToFloat(msg, 2);
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "brightness: " + brightness);
#endif
            controller->segments[msg[1]]->SetBrightness(brightness);
            break;
        }
        case MKEY_LED_WHITENESS:
        {

#ifdef ARDUINO_DEBUG
            Serial.println(String() + "whiteness: " + msg[2]);
#endif
            controller->segments[msg[1]]->SetWhiteness(msg[2]);
            break;
        }
        case MKEY_LED_SPEED:
        {
            float speed = DataParser::BytesToFloat(msg, 2);
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "speed: " + speed);
#endif
            controller->segments[msg[1]]->speed = speed;
            break;
        }
        case MKEY_LED_PERIOD:
        {
            float period = DataParser::BytesToFloat(msg, 2);
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "period: " + period);
#endif
            controller->segments[msg[1]]->period = period;
            break;
        }
        case MKEY_LED_COLOR_COUNT:
        {
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "color count: " + msg[2]);
#endif
            controller->segments[msg[1]]->colorsUsed = msg[2];
            break;
        }
        case MKEY_LED_SET_COLOR:
        {
            Color col = Color(msg[3], msg[4], msg[5], msg[6]);
            controller->segments[msg[1]]->SetColor(col, msg[2]);
#ifdef ARDUINO_DEBUG
            Serial.println(String() + "index: " + msg[2] + "\tcolor: " + col.r + "," + col.g + "," + col.b + "," + col.w);
#endif
            break;
        }
        }
    }
};