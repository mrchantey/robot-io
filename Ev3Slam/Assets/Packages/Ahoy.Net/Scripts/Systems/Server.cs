using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using Unity.Entities;
using Unity.Collections;

using Unity.Networking.Transport;

namespace Ahoy.Net
{


    public class Server : ComponentSystem
    {

        public UdpNetworkDriver driver;
        NativeList<NetworkConnection> connections;
        bool isInitialized;
        public bool debug;

        public AhoyEvent<object> onMessage;
        public AhoyEvent<NetworkConnection> onConnection;
        public AhoyEvent<NetworkConnection> onDisconnection;

        protected override void OnCreate()
        {
            onMessage = new AhoyEvent<object>();
            onConnection = new AhoyEvent<NetworkConnection>();
            onDisconnection = new AhoyEvent<NetworkConnection>();
        }

        public void Init(int port = 9000, int maxConnections = 8)
        {
            Dispose();
            isInitialized = true;
            var endPoint = NetworkEndPoint.AnyIpv4;
            // var endPoint = NetworkEndPoint.LoopbackIpv4;
            endPoint.Port = (ushort)port;
            driver = new UdpNetworkDriver(new INetworkParameter[0]);
            if (driver.Bind(endPoint) != 0)
                if (debug)
                    Debug.Log($"server - Failed to bind to port {port}");
                else
                {
                    if (debug)
                        Debug.Log($"server - listening on port {port}");
                }
            //m_Driver.CreatePipeline(typeof(NullPipelineStage));//unreliable
            driver.Listen();
            connections = new NativeList<NetworkConnection>(maxConnections, Allocator.Persistent);
        }

        void Dispose()
        {
            isInitialized = false;
            if (driver.IsCreated)
                driver.Dispose();
            if (connections.IsCreated)
                connections.Dispose();
        }


        protected override void OnDestroy()
        {
            Dispose();
        }

        protected override void OnUpdate()
        {
            if (!isInitialized)
                return;
            driver.ScheduleUpdate().Complete();
            CleanConnections();
            AcceptConnections();
            GetEvents();
        }

        void CleanConnections()
        {
            for (int i = 0; i < connections.Length; i++)
            {
                if (!connections[i].IsCreated)
                {
                    connections.RemoveAtSwapBack(i);
                    --i;
                }
            }

        }

        void AcceptConnections()
        {
            NetworkConnection c;
            while ((c = driver.Accept()) != default(NetworkConnection))
            {
                connections.Add(c);
                if (debug)
                    Debug.Log($"server - connected to client: {c.InternalId}");
                onConnection.Invoke(c);
            }
        }

        public void SendMessage(object data)
        {
            connections.ForEach(c => Messaging.WriteMessage(data, writer => driver.Send(NetworkPipeline.Null, c, writer)));
        }

        void GetEvents()
        {
            DataStreamReader stream;
            for (int i = 0; i < connections.Length; i++)
            {
                NetworkEvent.Type cmd;
                while ((cmd = driver.PopEventForConnection(connections[i], out stream)) != NetworkEvent.Type.Empty)
                {
                    switch (cmd)
                    {
                        case NetworkEvent.Type.Data:
                            var msg = Messaging.ReadMessage(stream);
                            if (debug)
                                Debug.Log($"server - message received: {msg}");
                            onMessage.Invoke(msg);
                            break;
                        case NetworkEvent.Type.Disconnect:
                            if (debug)
                                Debug.Log($"server - disconnected from client: {connections[i].InternalId}");
                            onDisconnection.Invoke(connections[i]);
                            connections[i] = default(NetworkConnection);
                            break;
                    }

                }
            }


        }
    }

}