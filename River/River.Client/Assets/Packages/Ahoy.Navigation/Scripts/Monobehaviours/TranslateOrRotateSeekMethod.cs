using UnityEngine;
using Ahoy;

namespace Ahoy.Navigation
{
    public enum SeekState
    {
        TurningLeft,
        TurningRight,
        MovingForward
    }

    [CreateAssetMenu(fileName = "TranslateOrRotateSeekMethod", menuName = "Ahoy.Navigation/TranslateOrRotateSeekMethod", order = 0)]
    public class TranslateOrRotateSeekMethod : SeekMethod
    {
        [Range(0, 3.1415f)]
        public float thetaThreshold = 0.1f;
        public SeekState seekState;

        public FloatAssetEvent onTranslate;
        public FloatAssetEvent onRotate;


        SeekState GetSeekState(Transform seeker, Vector3 target)
        {
            var targetLocalPosition = seeker.InverseTransformPoint(target);
            var theta = Mathf.Atan2(targetLocalPosition.x, targetLocalPosition.z);
            var hThreshold = thetaThreshold / 2;
            if (theta < -thetaThreshold)
                return SeekState.TurningRight;
            else if (theta > thetaThreshold)
                return SeekState.TurningLeft;
            else if (seekState == SeekState.TurningRight && theta < -hThreshold)
                return SeekState.TurningRight;
            else if (seekState == SeekState.TurningLeft && theta > hThreshold)
                return SeekState.TurningLeft;
            else
                return SeekState.MovingForward;
        }


        public override void SeekTarget(Transform seeker, Vector3 target)
        {
            seekState = GetSeekState(seeker, target);
            switch (seekState)
            {
                case SeekState.TurningRight:
                    onRotate.Invoke(-1);
                    break;
                case SeekState.TurningLeft:
                    onRotate.Invoke(1);
                    break;
                case SeekState.MovingForward:
                    onTranslate.Invoke(1);
                    break;
            }
        }

        // private void OnDrawGizmosSelected()
        // {
        //     //tan(theta) = o / a
        //     //o = tan(theta) * a
        //     float a = 3;
        //     float o = Mathf.Tan(thetaThreshold) * a;
        //     Vector3 thetaMin = transform.position + transform.forward * a + transform.right * -o;
        //     Vector3 thetaMax = transform.position + transform.forward * a + transform.right * o;
        //     Vector3 thetahMin = transform.position + transform.forward * a + transform.right * -o * 0.5f;
        //     Vector3 thetahMax = transform.position + transform.forward * a + transform.right * o * 0.5f;
        //     Gizmos.color = Color.magenta;
        //     Gizmos.DrawLine(transform.position, thetaMin);
        //     Gizmos.DrawLine(transform.position, thetaMax);
        //     Gizmos.color = Color.yellow;
        //     Gizmos.DrawLine(transform.position, thetahMin);
        //     Gizmos.DrawLine(transform.position, thetahMax);
        // }
    }

}