// using UnityEngine;

// namespace Ahoy.Net
// {

//     public class Vec4MessageCaster : MonoBehaviour
//     {

//         public Vector4UnityEvent onInvokeVector4;
//         public QuaternionUnityEvent onInvokeQuaternion;

//         public void Invoke(Vec4Message msg)
//         {
//             onInvokeVector4.Invoke(msg.value.ToVector4());
//             onInvokeQuaternion.Invoke(msg.value.ToQuaternion());
//         }

//     }

// }