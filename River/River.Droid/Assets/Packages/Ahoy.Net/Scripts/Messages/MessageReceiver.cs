using UnityEngine;
using UnityEngine.Events;
using Unity.Entities;
namespace Ahoy.Net
{

    // [CreateAssetMenu(fileName = "MessageReceiverSO", menuName = "Ahoy.Net/MessageReceiverSO", order = 0)]
    public abstract class MessageReceiver<T> : MonoBehaviour
    {

        public MessageHeaderInfo headerInfo;
        // public byte channel;
        MessageReceiveSystem receiveSystem;

        public bool debug;

        private void OnEnable()
        {
            // if (!UnityEditor.EditorApplication.isPlaying)
            //     return;
            receiveSystem = World.Active.GetOrCreateSystem<MessageReceiveSystem>();
            receiveSystem.AddChannelListener(headerInfo.channel, OnMessage);
            // manager = World.Active.get    
        }
        void OnMessage(MessageEventArgs args)
        {
            if (IsMatch(args))
            {
                if (debug)
                    Debug.Log($"message received! : {args}");
                var msg = (Message<T>)args.message;
                HandleMessage(msg);
            }
            else
            {
                if (debug)
                    Debug.Log($"channel message does not match header info : header info: {headerInfo}\nmessage:{args.message}");
            }
        }

        protected abstract void HandleMessage(Message<T> msg);

        bool IsMatch(MessageEventArgs args)
        {
            return args.message.channel == headerInfo.channel
            && args.message.command == headerInfo.command
            && args.message.dataType == headerInfo.dataType;
        }

    }

}