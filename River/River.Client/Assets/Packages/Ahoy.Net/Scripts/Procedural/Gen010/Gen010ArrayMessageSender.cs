using Unity.Entities;
using UnityEngine;

namespace Ahoy.Net
{

    // [CreateAssetMenu(fileName = "SendGen010", menuName = "Ahoy.Net/Message Sender/Gen010", order = 0)]
    public class Gen010ArrayMessageSender : MessageSender<gen010[]>
    {
        protected override byte[] GetBytes(gen010[] val)
        {
            return Gen010Parse.EncodeToBytes(headerInfo.channel, headerInfo.command, val);
        }
    }

}