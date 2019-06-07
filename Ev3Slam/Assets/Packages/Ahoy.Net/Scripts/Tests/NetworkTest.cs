using UnityEngine;
// using  Unity.Collections;
using Unity.Entities;
namespace Ahoy.Net
{

    public class NetworkTest : InvocableMono
    {


        Server server;
        Client client;
        public string ipAddress = "127.0.0.1";
        public int port = 9000;
        public bool debug;

        public string message = "hello, world";

        private void OnEnable()
        {
            server = World.Active.GetOrCreateSystem<Server>();
            client = World.Active.GetOrCreateSystem<Client>();
            server.debug = debug;
            client.debug = debug;
            server.Init(port);
            client.Init(ipAddress, port);
            // client.onConnect.AddListener(() => client.SendMessage(message));

            server.onMessage.AddListener(msg => Debug.Log($"server - message received: {msg}"));
        }

        public override void Invoke()
        {
            // client.SendMessage(69);
            client.SendMessage(message);
        }
    }

}