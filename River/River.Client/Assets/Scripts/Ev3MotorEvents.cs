using UnityEngine;
using Ahoy;

namespace River.Client
{

    public class Ev3MotorEvents : MonoBehaviour
    {



        public FloatArrayUnityEvent onSetMotors;
        [Range(-1, 1)]
        public float scalar = 0.2f;
        public void OnTranslate(float val)
        {
            val *= scalar;
            var arr = new float[] { val, val };
            onSetMotors.Invoke(arr);
        }
        public void OnRotate(float val)
        {
            val *= scalar;
            var arr = new float[] { val, -val };
            onSetMotors.Invoke(arr);
        }

        // private void OnDestroy()
        // {
        //     var arr = new float[] { 0, 0 };
        //     onSetMotors.Invoke(arr);
        // }

    }

}