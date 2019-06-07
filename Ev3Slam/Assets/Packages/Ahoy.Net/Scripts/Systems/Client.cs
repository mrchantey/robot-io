using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;

using Unity.Networking.Transport;
using Unity.Collections;
using Unity.Entities;
using Unity.Jobs;

namespace Ahoy.Net
{


    public class Client : ComponentSystem
    {

        public ushort port = 9000;
        public int val = 2;


        public AhoyEvent onConnect;
        public AhoyEvent<object> onMessage;
        public AhoyEvent onDisconnect;
        public bool debug;

        public UdpNetworkDriver driver;
        NetworkConnection connection;
        bool isDone;
        bool isInitialized;

        public bool isConnected { get; private set; }


        protected override void OnCreate()
        {
            onConnect = new AhoyEvent();
            onMessage = new AhoyEvent<object>();
            onDisconnect = new AhoyEvent();
        }

        public void Init(string ipAddress, int port)
        {
            Dispose();
            isInitialized = true;
            // var endPoint = NetworkEndPoint.LoopbackIpv4;
            // var endPoint = NetworkEndPoint.AnyIpv4;
            var endPoint = NetworkEndPoint.Parse(ipAddress, (ushort)port);
            // endPoint.Port = (ushort)port;
            if (debug)
                Debug.Log($"client - connecting to server: {ipAddress}:{port}");
            connection = default(NetworkConnection);
            driver = new UdpNetworkDriver(new INetworkParameter[0]);
            connection = driver.Connect(endPoint);
        }

        void Dispose()
        {
            isInitialized = false;
            if (driver.IsCreated)
                driver.Dispose();

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
            if (!connection.IsCreated)
            {
                if (!isDone)
                {
                    if (debug)
                        Debug.Log($"client - failed to connect to port {port}");
                    isDone = true;
                }
                return;
            }
            GetEvents();
        }



        public void SendMessage(object data)
        {
            if (debug)
                Debug.Log($"client - sending message: {data}");
            Messaging.WriteMessage(data, writer => connection.Send(driver, writer));
        }


        // struct ClientUpdateJob : IJob
        // {

        //     public UdpNetworkDriver driver;

        //     public void Execute()
        //     {

        //     }
        // }



        public void Disconnect()
        {
            isDone = true;
            connection.Disconnect(driver);
            connection = default(NetworkConnection);

        }
        void GetEvents()
        {
            DataStreamReader stream;
            NetworkEvent.Type cmd;
            while ((cmd = connection.PopEvent(driver, out stream)) != NetworkEvent.Type.Empty)
            {
                switch (cmd)
                {
                    case NetworkEvent.Type.Connect:
                        if (debug)
                            Debug.Log($"client - connected");
                        isConnected = true;
                        onConnect.Invoke();
                        break;
                    case NetworkEvent.Type.Data:
                        var msg = Messaging.ReadMessage(stream);
                        if (debug)
                            Debug.Log($"client - message received: {msg}");
                        onMessage.Invoke(msg);
                        break;
                    case NetworkEvent.Type.Disconnect:
                        if (debug)
                            Debug.Log($"client - disconnected");
                        isDone = true;
                        onDisconnect.Invoke();
                        connection = default(NetworkConnection);
                        break;
                }

            }
        }



    }
}

