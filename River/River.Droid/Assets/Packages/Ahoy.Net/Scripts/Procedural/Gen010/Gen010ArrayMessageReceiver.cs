using UnityEngine;
using Unity.Entities;
namespace Ahoy.Net
{

    public class Gen010ArrayMessageReceiver : MessageReceiver<gen010>
    {

        public Gen010ArrayUnityEvent onMessage;

        protected override void HandleMessage(Message<gen010> msg)
        {
            onMessage.Invoke(msg.data);

        }
    }

}