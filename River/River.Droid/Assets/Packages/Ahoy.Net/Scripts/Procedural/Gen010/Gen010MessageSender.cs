using Unity.Entities;
using UnityEngine;

namespace Ahoy.Net
{

    // [CreateAssetMenu(fileName = "SendVector3", menuName = "Ahoy.Net/Message Sender/Vector3", order = 0)]
    public class Gen010MessageSender : MessageSender<gen010>
    {
        protected override byte[] GetBytes(gen010 val)
        {
            return Gen010Parse.EncodeToBytes(headerInfo.channel, headerInfo.command, val);
        }
    }

}