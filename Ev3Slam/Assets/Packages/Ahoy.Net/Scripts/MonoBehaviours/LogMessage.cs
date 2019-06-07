using UnityEngine;

namespace Ahoy.Net
{

    public class LogMessage : MonoBehaviour
    {

        public void Log(string message)
        {
            Debug.Log(message);
        }
        public void Log(Vector3 message)
        {
            Debug.Log(message);
        }
        public void Log(float message)
        {
            Debug.Log(message);
        }
        public void Log(Vector3[] message)
        {
            Debug.Log(message.ElementsToString());
        }

    }

}