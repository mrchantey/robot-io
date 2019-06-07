using UnityEngine;

namespace Ahoy.Net
{

    public class Messenger : InvocableMono
    {

        public string message = "hello world";
        public StringUnityEvent messageEvent;

        public override void Invoke()
        {
            messageEvent.Invoke(message);
        }


    }

}