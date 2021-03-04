using UnityEngine;
using UnityEngine.Events;
using System.Collections.Generic;
using System;
using System.Linq;

namespace Ahoy
{

    [Serializable]
    public class Gen010UnityEvent : UnityEvent<gen010> { }
    [Serializable]
    public class Gen010ArrayUnityEvent : UnityEvent<gen010[]> { }
    [Serializable]
    public class Gen010ListUnityEvent : UnityEvent<List<gen010>> { }

}