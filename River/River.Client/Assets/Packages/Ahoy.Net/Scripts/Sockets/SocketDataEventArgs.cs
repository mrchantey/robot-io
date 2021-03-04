
using UnityEngine;
using System;
using System.Net;
using System.Net.Sockets;

namespace Ahoy.Net
{

    public struct SocketDataEventArgs
    {
        public AhoySocket receiver;
        public EndPoint sender;
        // public ArraySegment<byte> data;
        public ArraySegment<byte> data;

        public override string ToString()
        {
            return $"sender:{sender}, receiver: {receiver}, data length:{data.Count}, data:{data.ElementsToString()}";
        }
    }
}