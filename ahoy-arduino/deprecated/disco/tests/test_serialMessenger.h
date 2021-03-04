

int count = 0;

class MessageAction : public ActionBase<NoType>
{
  public:
    void Invoke(NoType data)
    {
        count += random(-10, 10);
        String msg = "{\"key\":\"counter\",\"value\":" + String(count) + ",\"timeStamp\":" + millis() + "}";
        Serial.println(msg);
    }
};
MessageAction *action;

void setup()
{
    action = new MessageAction();
    Serial.begin(9600);
    Serial.println("hello");
    // Color *myCol = new Color();
    // LoopSystem::delayMillis = 2000;
    // action->Invoke(NoType());
    // action->Invoke(NoType());
    // action->Invoke(NoType());
    LoopSystem::AddListener(action);
    // SerialMessenger::SendMessage<Color>(GetVarName(myCol), *myCol);
    // SerialMessenger::SendMessage("counter", String(count++));
}