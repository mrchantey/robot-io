// using UnityEngine;
// using UnityEngine.Events;

// namespace Ahoy.Net
// {
//     public class MessageFilter<T, eventT> : MonoBehaviour
//     where eventT : UnityEvent<T>
//     where T : Message
//     {
//         public bool debug;
//         public string messageName;
//         public eventT onMatch;

//         // public void InvokeIfMatch(T msg)
//         // {
//         //     if (msg.name == messageName)
//         //     {
//         //         if (debug)
//         //             Debug.Log($"message filter match - {msg}");
//         //         onMatch.Invoke(msg);
//         //     }
//         // }
//         public void InvokeIfMatch(Message msg)
//         {
//             if (msg.GetType() == typeof(T) && msg.name == messageName)
//             {
//                 if (debug)
//                     Debug.Log($"message filter match - {msg}");
//                 onMatch.Invoke((T)msg);
//             }
//         }
//     }
// }

