using UnityEngine;
using System;
namespace Ahoy.Net
{

    [CreateAssetMenu(fileName = "MessageHeaderInfo", menuName = "Ahoy.Net/MessageHeaderInfo", order = 0)]
    public class MessageHeaderInfo : ScriptableObject, IEquatable<MessageHeaderInfo>
    {

        public byte channel;
        public byte command;
        public DataType dataType = DataType.None;


        public bool Equals(MessageHeaderInfo other)
        {
            return
            channel == other.channel &&
            command == other.command &&
            dataType == other.dataType;
        }
    }

}