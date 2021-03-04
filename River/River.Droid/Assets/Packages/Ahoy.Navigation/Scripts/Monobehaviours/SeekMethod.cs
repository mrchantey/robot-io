using UnityEngine;

namespace Ahoy.Navigation
{

    public abstract class SeekMethod : ScriptableObject
    {

        public abstract void SeekTarget(Transform seeker, Vector3 target);

    }

}