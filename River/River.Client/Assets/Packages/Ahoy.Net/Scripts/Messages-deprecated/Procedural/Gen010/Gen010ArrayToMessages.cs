// using UnityEngine;

// namespace Ahoy.Net
// {

//     public class Gen010ArrayToMessages : MonoBehaviour
//     {

//         public string messageName;
//         [Range(1, 256)]
//         public int chunkSize = 32;
//         public Gen010ArrayMessageUnityEvent messageEvent;

//         public void Invoke(gen010[] arr)
//         {
//             var messages = Gen010ArrayMessage.CreateArrayMessages(arr, messageName, chunkSize);
//             messages.ForEach(messageEvent.Invoke);
//         }


//     }

// }