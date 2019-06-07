using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

namespace Ahoy
{
    [Serializable]
    public class NullUnityEvent : UnityEvent { }
    [Serializable]
    public class ObjectUnityEvent : UnityEvent<object> { }
    [Serializable]
    public class BoolUnityEvent : UnityEvent<bool> { }
    [Serializable]
    public class StringUnityEvent : UnityEvent<string> { }
    [Serializable]
    public class FloatUnityEvent : UnityEvent<float> { }
    [Serializable]
    public class IntUnityEvent : UnityEvent<int> { }
    [Serializable]
    public class Vector2UnityEvent : UnityEvent<Vector2> { }
    [Serializable]
    public class Vector3UnityEvent : UnityEvent<Vector3> { }
    [Serializable]
    public class SerializableVector3UnityEvent : UnityEvent<SerializableVector3> { }
    [Serializable]
    public class GameObjectUnityEvent : UnityEvent<GameObject> { }
    [Serializable]
    public class KeyCodeUnityEvent : UnityEvent<KeyCode> { }

    [Serializable]
    public class ObjectArrayUnityEvent : UnityEvent<object[]> { }
    [Serializable]
    public class BoolArrayUnityEvent : UnityEvent<bool[]> { }
    [Serializable]
    public class StringArrayUnityEvent : UnityEvent<string[]> { }
    [Serializable]
    public class FloatArrayUnityEvent : UnityEvent<float[]> { }
    [Serializable]
    public class IntArrayUnityEvent : UnityEvent<int[]> { }
    [Serializable]
    public class Vector2ArrayUnityEvent : UnityEvent<Vector2[]> { }
    [Serializable]
    public class Vector3ArrayUnityEvent : UnityEvent<Vector3[]> { }
    [Serializable]
    public class SerializableVector3ArrayUnityEvent : UnityEvent<SerializableVector3[]> { }
    [Serializable]
    public class GameObjectArrayUnityEvent : UnityEvent<GameObject[]> { }
    [Serializable]
    public class KeyCodeArrayUnityEvent : UnityEvent<KeyCode[]> { }

    [Serializable]
    public class ObjectListUnityEvent : UnityEvent<List<object>> { }
    [Serializable]
    public class BoolListUnityEvent : UnityEvent<List<bool>> { }
    [Serializable]
    public class StringListUnityEvent : UnityEvent<List<string>> { }
    [Serializable]
    public class FloatListUnityEvent : UnityEvent<List<float>> { }
    [Serializable]
    public class IntListUnityEvent : UnityEvent<List<int>> { }
    [Serializable]
    public class Vector2ListUnityEvent : UnityEvent<List<Vector2>> { }
    [Serializable]
    public class Vector3ListUnityEvent : UnityEvent<List<Vector3>> { }
    [Serializable]
    public class SerializableVector3ListUnityEvent : UnityEvent<List<SerializableVector3>> { }
    [Serializable]
    public class GameObjectListUnityEvent : UnityEvent<List<GameObject>> { }
    [Serializable]
    public class KeyCodeListUnityEvent : UnityEvent<List<KeyCode>> { }
}