using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
// using System.Text;
using Unity.Entities;
// [Serializable]

using UnityEngine;
namespace Ahoy.Net
{


    public class AhoySocketSystem : ComponentSystem
    {
        public bool debug;

        // public int bufferSize = 1500;
        public int bufferSize = 10240;
        public int maxMessageLength = 1024;//unity datagram limit

        List<AhoySocket> sockets;
        EntityManager manager;
        byte[] buffer;

        public AhoyEvent<SocketDataEventArgs> onData;
        // EntityQuery query;
        public void TestCreate() { OnCreate(); }

        protected override void OnCreate()
        {
            sockets = new List<AhoySocket>();
            manager = World.Active.EntityManager;
            buffer = new byte[bufferSize];
            onData = new AhoyEvent<SocketDataEventArgs>();
        }

        public AhoySocket CreateSocket(string ipAddress, int port)
        {
            var ct = new ComponentType[] { typeof(AhoySocket) };
            var entity = manager.CreateEntity(ct);
            var socket = new AhoySocket(ipAddress, port);
            manager.SetSharedComponentData(entity, socket);
            sockets.Add(socket);
            if (debug)
                Debug.Log($"Ahoy Socket System - socket created: {socket}");
            return socket;
        }

        public EndPoint Connect(AhoySocket socket, EndPoint endPoint)
        {
            socket.remoteEndPoints.TryAdd(endPoint);
            if (debug)
                Debug.Log($"Ahoy Socket System - endpoint: {endPoint} connected to socket: {socket}");
            return endPoint;
        }
        public EndPoint Connect(AhoySocket socket, string ipAddress, int port)
        {
            var longIP = IPAddress.Parse(ipAddress);
            var endPoint = new IPEndPoint(longIP, port);
            Connect(socket, endPoint);
            return endPoint;
        }

        public void SendData(AhoySocket socket, byte[] data)
        {
            if (data.Length > maxMessageLength)
            {
                Debug.LogWarning("data length exceeds max message size");
                return;
            }
            socket.remoteEndPoints.ForEach(ep =>
            {
                if (debug)
                    Debug.Log($"Ahoy Socket System - sending data, socket: {socket}, end point: {ep}, data: {data}");
                // Debug.Log($"sending.. endpoint: {ep}, message: {data.ElementsToString()}");
                socket.socket.SendTo(data, ep);
            });
        }

        protected override void OnUpdate()
        {
            var offset = 0;
            sockets.ForEach(s =>
            {
                // var segmentSize = bufferSize;
                while (s.socket.Available != 0)
                {
                    // Debug.Log($"next: {offset + maxMessageLength}/{buffer.Length}");
                    if (offset + maxMessageLength > buffer.Length)
                    {
                        Debug.LogWarning("buffer overflow, please throttle messages or increase buffer size");
                        return;
                    }
                    EndPoint sender = new IPEndPoint(IPAddress.Any, 0);
                    int received = s.socket.ReceiveFrom(buffer, offset, maxMessageLength, SocketFlags.None, ref sender);
                    var segment = new ArraySegment<byte>(buffer, offset, received);
                    offset += received;
                    var args = new SocketDataEventArgs() { sender = sender, receiver = s, data = segment };
                    if (debug)
                        Debug.Log($"Ahoy Socket System - data received: {args}");
                    onData.Invoke(args);
                }
            });
        }

        protected override void OnDestroy()
        {
            sockets.ForEach(s => s.socket.Close());
        }
    }

}