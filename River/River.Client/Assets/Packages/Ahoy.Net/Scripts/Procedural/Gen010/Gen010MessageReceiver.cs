using UnityEngine;
using Unity.Entities;
namespace Ahoy.Net
{

    public class Gen010MessageReceiver : MessageReceiver<gen010>
    {

        public Gen010UnityEvent onMessage;
        protected override void HandleMessage(Message<gen010> msg)
        {
            onMessage.Invoke(msg.data[0]);
        }
    }

}