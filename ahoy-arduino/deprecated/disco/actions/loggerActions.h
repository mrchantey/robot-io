#pragma once

#include "action.h"

class Logger : public ActionBase<NoType>
{

  public:
    String eventName = "";
    bool newLine = false;
    Logger(String _eventName, bool _newLine = false)
    {
        newLine = _newLine;
        eventName = _eventName;
    }

    void Invoke(NoType data)
    {
        Serial.print("Event occured..\t");
        Serial.print(eventName);
        if (newLine)
            Serial.println();
        else
            Serial.print("\t");
    }
};

class ColorLogger : public ActionBase<Color>
{

  public:
    bool newLine;
    ColorLogger(bool _newLine = false)
    {
        newLine = _newLine;
    }

    void Invoke(Color col)
    {
        col.Print();
        if (newLine)
            Serial.println();
    }
};

// template <typename dataT>
// struct DataLogger
// {
// };

template <typename dataT>
class DataLogger : public ActionBase<dataT>
{

  public:
    String preText;
    bool newLine;
    DataLogger(String _preText = "got value: ", bool _newLine = true)
    {
        preText = _preText;
        newLine = _newLine;
        // Action<DataLogger<dataT>, dataT>::Init(this, &DataLogger<dataT>::Log);
    }

    void Invoke(dataT data)
    {
        Serial.print(preText);
        Serial.print(data);
        if (newLine)
            Serial.println();
        else
            Serial.print("\t");
    }
};
template <typename dataT>
class DiscoDataLogger : public ActionBase<dataT>
{

  public:
    String preText;
    String postText;
    bool logJson;
    // bool convertToBits;
    DiscoDataLogger(String _preText = "got value: ", String _postText = "", bool _newLine = true, bool _logJson = false)
    {
        preText = _preText;
        postText = _postText;
        if (_newLine)
            postText += "\r\n";
        else
            postText += "\t";
        logJson = _logJson;
        // newLine = _newLine;
        // convertToBits = _convertToBits;
        // Action<DataLogger<dataT>, dataT>::Init(this, &DataLogger<dataT>::Log);
    }

    void Invoke(dataT data)
    {
        String dataStr = logJson ? data.ToJson() : data.ToString();
        String str = String("") + preText + dataStr + postText;
        Serial.print(str);
    }
};
