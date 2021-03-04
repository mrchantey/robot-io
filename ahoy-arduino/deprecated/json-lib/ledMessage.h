

enum MessageKey
{
    MKEY_CONNECTION_STATUS = 10,
    MKEY_LED_MODE = 210,
    MKEY_LED_INDICIES = 211,
    MKEY_LED_BRIGHTNESS = 212,
    MKEY_LED_WHITENESS = 213,
    MKEY_LED_SPEED = 214,
    MKEY_LED_PERIOD = 215,
    MKEY_LED_COLOR_COUNT = 220,
    MKEY_LED_SET_COLOR = 221,
};

enum MessageValue
{
    MVAL_WIFI_CLIENT = 0,
    MVAL_WIFI_HOST = 1,
    MVAL_BLUETOOTH_CLIENT = 2,
    MVAL_BLUETOOTH_HOST = 3,
    MVAL_CONNECTION_IDLE = 0,
    MVAL_CONNECTION_CONNECTING = 1,
    MVAL_CONNECTION_CONNECTED = 2,
    MVAL_CONNECTION_FAILED = 3,
};

class LedMessageRgbw
{
public:
    LedControllerRgbw *controller;
    Action<LedMessageRgbw, JsonArray> *doReceiveMessage;
    LedMessageRgbw(LedControllerRgbw *_controller)
    {
        controller = _controller;
        doReceiveMessage = new Action<LedMessageRgbw, JsonArray>(this, &LedMessageRgbw::ReceiveMessage);
    }

    void ReceiveMessage(JsonArray msg)
    {
        int ledSegment = msg[2].as<int>();
        switch (msg[1].as<int>())
        {
        case MKEY_CONNECTION_STATUS:
            int connectionStatus = msg[3].as<int>();
            switch (connectionStatus)
            {
            case MVAL_CONNECTION_IDLE:
                controller->segments[4]->SetColor(Color::White(), 0);
                controller->segments[4]->SetColor(Color::Black(), 1);
                controller->segments[4]->animationMode = ANIM_FADE;
                break;
            case MVAL_CONNECTION_CONNECTING:
                controller->segments[4]->SetColor(Color::Green(), 0);
                controller->segments[4]->SetColor(Color::Blue(), 1);
                controller->segments[4]->animationMode = ANIM_FADE;
                break;
            case MVAL_CONNECTION_CONNECTED:
                controller->segments[4]->animationMode = ANIM_OFF;
            case MVAL_CONNECTION_FAILED:
                controller->segments[4]->SetColor(Color::Red(), 0);
                controller->segments[4]->SetColor(Color::Black(), 1);
                controller->segments[4]->animationMode = ANIM_FADE;
                break;
            }
            break;
        case MKEY_LED_MODE:
            controller->segments[ledSegment]->animationMode = msg[3].as<int>();
            break;
        case MKEY_LED_INDICIES:
            controller->segments[ledSegment]->SetIndicies(msg[3].as<int>(), msg[4].as<int>());
            break;
        case MKEY_LED_BRIGHTNESS:
            controller->segments[ledSegment]->SetBrightness(msg[3].as<float>());
            break;
        case MKEY_LED_WHITENESS:
            controller->segments[ledSegment]->SetWhiteness(msg[3].as<int>());
            break;
        case MKEY_LED_SPEED:
            controller->segments[ledSegment]->speed = msg[3].as<float>();
            break;
        case MKEY_LED_PERIOD:
            controller->segments[ledSegment]->period = msg[3].as<float>();
            break;
        case MKEY_LED_COLOR_COUNT:
            controller->segments[ledSegment]->colorsUsed = msg[3].as<int>();
            break;
        case MKEY_LED_SET_COLOR:
            Color col = Color(msg[4].as<int>(), msg[5].as<int>(), msg[6].as<int>(), msg[7].as<int>());
            controller->segments[ledSegment]->SetColor(col, msg[3].as<int>());
            break;
        }
    }
};