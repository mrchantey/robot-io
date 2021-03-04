

template <typename dataT>
class JsonPrimitiveTransmitAction : public ActionBase<dataT>
{
  public:
    // ActionArray<String> *onData;
    String key;

    JsonPrimitiveTransmitAction(String _key = "key")
    {
        key = _key;
        // onData = new ActionArray<dataT>;
    }

    void Invoke(dataT data)
    {
        KeyValuePair<dataT> kvpData = KeyValuePair<dataT>(key, data);
        RadioTransmitter::Transmit(kvpData.ToJson());
        //    onData->Invoke(data.To)
    }
};

template <typename dataT>
class JsonObjectTransmitAction : public ActionBase<dataT>
{

  public:
    String key;
    JsonObjectTransmitAction(String _key = "key")
    {
        key = _key;
    }
    void Invoke(dataT data)
    {
        String json = String("");
        json += "{\"";
        json += key;
        json += "\":";
        json += data.ToJson();
        json += ",\"timeStamp\":";
        json += LoopSystem::elapsedMillis;
        json += "}";

        RadioTransmitter::Transmit(json);
    };
};