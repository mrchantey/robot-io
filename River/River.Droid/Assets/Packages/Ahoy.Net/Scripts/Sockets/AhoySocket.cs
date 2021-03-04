using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
// [Serializable]

using UnityEngine;
using Unity.Entities;
namespace Ahoy.Net
{

    [Serializable]
    public struct AhoySocket : ISharedComponentData, IEquatable<AhoySocket>
    {

        static int idIncr;
        public int id { get; private set; }

        public Socket socket;
        public IPEndPoint localEndPoint;
        public List<EndPoint> remoteEndPoints;

        public AhoySocket(string ipAddress, int port)
        {
            id = ++idIncr;
            remoteEndPoints = new List<EndPoint>();
            // localEndPoint = new IPEndPoint(IPAddress.Any, port);
            localEndPoint = new IPEndPoint(IPAddress.Parse(ipAddress), port);
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            socket.Bind(localEndPoint);
            // socket.SendTimeout = timeOut;//these arent needed for datagrams i think
            // socket.ReceiveTimeout = timeOut;
        }

        public bool Equals(AhoySocket other)
        {
            return id == other.id;
        }

        public override int GetHashCode()
        {
            return id;
        }

        public override string ToString()
        {
            return $"{localEndPoint.Address}:{localEndPoint.Port}";
        }
    }
}