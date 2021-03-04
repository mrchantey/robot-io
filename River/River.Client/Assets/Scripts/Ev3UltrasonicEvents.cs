using UnityEngine;
using Ahoy;

namespace River.Client
{

    public class Ev3UltrasonicEvents : MonoBehaviour
    {


        public Vector3ArrayUnityEvent onObstaclePosition;

        // [Range(-0.5f, 0.5f)]
        public Vector3 sensorOffset = new Vector3(0, 0.05f, -0.1f);
        [Range(0, 255f)]
        public float maxThresholdCM = 100f;
        public bool debug;

        public void OnValueRecieved(float[] vals)
        {
            if (vals.Length != 1)
            {
                Debug.LogWarning($"ev3 ultrasonic - was expecting one value, got {vals.Length}");
                return;
            }
            if (vals[0] >= maxThresholdCM)
            {
                if (debug)
                    Debug.Log($"ev3 ultrasonic - value exceeds max threshold: {vals[0]}/{maxThresholdCM}");
                return;
            }
            var valM = vals[0] * 0.01f;
            var obstacleLocalPosition = Vector3.forward * valM + sensorOffset;
            var obstacleWorldPosition = transform.TransformPoint(obstacleLocalPosition);
            if (debug)
                Debug.Log($"ev3 ultrasonic - obstacle world position: {obstacleWorldPosition}");
            onObstaclePosition.Invoke(new Vector3[] { obstacleWorldPosition });
        }

    }

}