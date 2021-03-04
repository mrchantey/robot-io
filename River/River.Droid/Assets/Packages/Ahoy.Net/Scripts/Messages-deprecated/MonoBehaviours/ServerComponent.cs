// using UnityEngine;
// using Unity.Entities;

// namespace Ahoy.Net
// {

//     public class ServerComponent : MonoBehaviour
//     {


//         public int port = 9000;
//         public bool debug;
//         public MessageUnityEvent onMessage;

//         Server server;

//         private void OnEnable()
//         {
//             server = World.Active.GetOrCreateSystem<Server>();
//             server.debug = debug;
//             server.Init(port);
//             server.onMessage.AddListener(msg => onMessage.Invoke(msg));
//         }

//         public void EmitMessage(Message message)
//         {
//             server.SendMessage(message);
//         }

//     }

// }