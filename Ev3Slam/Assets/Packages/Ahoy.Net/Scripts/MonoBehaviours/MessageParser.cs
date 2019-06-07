using UnityEngine;

namespace Ahoy.Net
{

    public class MessageParser : MonoBehaviour
    {

        public NullUnityEvent nullMessage;
        public ObjectUnityEvent objectMessage;
        public BoolUnityEvent boolMessage;
        public StringUnityEvent stringMessage;
        public FloatUnityEvent floatMessage;
        public IntUnityEvent intMessage;
        // public Vector2UnityEvent vector2Message;
        public Vector3UnityEvent vector3Message;
        public Vector3ArrayUnityEvent vector3ArrayMessage;
        public IntArrayUnityEvent intArrayMessage;

        public void ParseMessage(object obj)
        {
            // Debug.Log($"parsing message {}");
            if (obj == null)
                nullMessage.Invoke();
            else if (obj.GetType() == typeof(string))
                stringMessage.Invoke((string)obj);
            else if (obj.GetType() == typeof(bool))
                boolMessage.Invoke((bool)obj);
            else if (obj.GetType() == typeof(int))
                intMessage.Invoke((int)obj);
            else if (obj.GetType() == typeof(SerializableVector3))
                vector3Message.Invoke(((SerializableVector3)obj).ToVector3());
            else if (obj.GetType() == typeof(SerializableVector3[]))
                vector3ArrayMessage.Invoke(SerializableVector3.ToVector3(((SerializableVector3[])obj)));
            else if (obj.GetType() == typeof(int[]))
                intArrayMessage.Invoke((int[])obj);
            else
                objectMessage.Invoke(obj);
        }


    }

}