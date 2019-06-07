using UnityEngine;
using Unity.Entities;

namespace Ahoy.Net
{

    public class ClientComponent : MonoBehaviour
    {


        public string ipAddress = "127.0.0.1";
        public int port = 9000;
        public bool debug;
        public ObjectUnityEvent onMessage;

        Client client;

        private void OnEnable()
        {
            client = World.Active.GetOrCreateSystem<Client>();
            client.debug = debug;
            client.Init(ipAddress, port);
            client.onMessage.AddListener(msg => onMessage.Invoke(msg));
        }

        public void EmitMessage(object message)
        {
            client.SendMessage(message);
        }

    }

}