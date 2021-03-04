using UnityEngine;

namespace Ahoy.Navigation
{

    public struct PathGenerateInfo
    {
        public Transform start;
        public Transform finish;
        public System.Action<PathInfo> onPathGenerated;
    }


}