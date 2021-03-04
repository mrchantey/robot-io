
using UnityEngine;
using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;

namespace Ahoy.Net
{


    public struct MessageEventArgs
    {
        public EndPoint sender;
        public AhoySocket receiver;
        public Message message;

        public MessageEventArgs(EndPoint _sender, AhoySocket _receiver, Message _message)
        {
            receiver = _receiver;
            sender = _sender;
            message = _message;
        }



        public override string ToString()
        {
            return $"sender:{sender}, receiver: {receiver}, message:\n{message}";
        }


    }
}