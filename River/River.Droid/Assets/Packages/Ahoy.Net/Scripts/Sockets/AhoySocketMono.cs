using UnityEngine;
using Unity.Entities;
using System.Collections.Generic;

namespace Ahoy.Net
{

    public class AhoySocketMono : MonoBehaviour
    {

        public IpInfo myIpInfo;

        AhoySocket socket;
        AhoySocketSystem socketSystem;

        public List<IpInfo> connections;

        public bool isEnabled;

        private void Update()
        {
            if (Time.frameCount > 1 && !isEnabled)
                Init();
        }

        void Init()
        {
            socketSystem = World.Active.GetOrCreateSystem<AhoySocketSystem>();
            socket = socketSystem.CreateSocket(myIpInfo.ipAddress, myIpInfo.port);
            connections.ForEach(c => { socketSystem.Connect(socket, c.ipAddress, c.port); });
            isEnabled = true;
        }


        public void SendBytes(byte[] bytes)
        {
            socketSystem.SendData(socket, bytes);
        }

    }

}