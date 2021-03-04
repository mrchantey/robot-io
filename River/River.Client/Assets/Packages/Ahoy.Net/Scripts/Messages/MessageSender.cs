using Unity.Entities;
using UnityEngine;

namespace Ahoy.Net
{

    public abstract class MessageSender<T> : MonoBehaviour
    {

        public MessageHeaderInfo headerInfo;

        public AhoySocketMono socket;

        private void OnEnable()
        {
        }


        public void Send(T val)
        {
            var bytes = GetBytes(val);
            socket.SendBytes(bytes);
        }

        protected abstract byte[] GetBytes(T val);

    }

}