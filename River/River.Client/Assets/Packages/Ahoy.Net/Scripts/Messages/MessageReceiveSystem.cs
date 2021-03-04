
using System;
using System.Collections.Generic;
// using System.Linq;
// using System.Net;
// using System.Net.Socskets;
using System.Text;
using Unity.Entities;
// [Serializable]

using UnityEngine;
namespace Ahoy.Net
{

    using EventSet = Dictionary<byte, AhoyEvent<MessageEventArgs>>;
    // using ReceiveEvent =
    public class MessageReceiveSystem : ComponentSystem
    {

        public bool debug;

        public EventSet channelEvents;
        AhoySocketSystem socketSystem;

        protected override void OnCreate()
        {
            channelEvents = new EventSet();
            socketSystem = World.Active.GetOrCreateSystem<AhoySocketSystem>();
            socketSystem.onData.AddListener(OnData);
        }

        AhoyEvent<MessageEventArgs> GetOrCreateChannelReceiver(byte key)
        {
            AhoyEvent<MessageEventArgs> eve;
            if (!channelEvents.TryGetValue(key, out eve))
            {
                if (debug)
                    Debug.Log($"Message Receive System - creating event for channel {key}");
                // Debug.Log($"creating event");
                eve = new AhoyEvent<MessageEventArgs>();
                channelEvents[key] = eve;
            }
            return eve;
        }

        public void AddChannelListener(byte channel, Action<MessageEventArgs> onMessage)
        {
            var eve = GetOrCreateChannelReceiver(channel);
            eve.AddListener(onMessage);
        }

        public void OnData(SocketDataEventArgs args)
        {
            if (debug)
                Debug.Log($"Message Receive System - data received: {args}");
            if (args.data.Count < 1)
                return;
            AhoyEvent<MessageEventArgs> messageEvent;
            var channel = args.data.GetElement(0);
            if (channelEvents.TryGetValue(channel, out messageEvent))
            {
                var message = MessageParse.DecodeToMessage(args.data);
                var msgArgs = new MessageEventArgs(args.sender, args.receiver, message);
                if (debug)
                    Debug.Log($"Message Receive System - data event: {args}");
                messageEvent.Invoke(msgArgs);
            }
            else
            {
                if (debug)
                    Debug.Log($"Message Receive System - no channel receivers for channel {channel}: {args}");
            }
        }

        // public bool TrySetInstruction()
        // {


        // }

        protected override void OnUpdate() { }
        // public void TestCreate() { OnCreate(); }
    }


}