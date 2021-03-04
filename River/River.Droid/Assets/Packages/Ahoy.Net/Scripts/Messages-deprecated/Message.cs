// using UnityEngine;
// using System;
// using UnityEngine.Events;
// namespace Ahoy.Net
// {

//     public enum MessageType
//     {
//         Null,
//         Gen010,
//         Gen010Array,
//         Object,
//         ObjectArray,
//         Bool,
//         BoolArray,
//         String,
//         StringArray,
//         Int,
//         IntArray,
//         Float,
//         FloatArray,
//         Vec2,
//         Vec2Array,
//         Vec3,
//         Vec3Array,
//         Vec4,
//         Vec4Array,
//         Vec3vec4,
//         Vec3vec4Array
//     };
//     [Serializable]
//     public class MessageUnityEvent : UnityEvent<Message> { }
//     [Serializable]
//     public abstract class Message
//     {
//         public string name;
//         public abstract MessageType messageType { get; }
//         public Message()
//         {
//             name = messageType.ToString();
//         }
//         public Message(string _name)
//         {
//             name = _name;
//         }
//     }

//     public interface IMessage
//     {
//         string name { get; }
//         MessageType messageType { get; }
//     }

//     [Serializable]
//     public abstract class MessageBase<T> : Message
//     {
//         public T value;

//         public MessageBase(T _value, string _name) : base(_name)
//         {
//             value = _value;
//         }
//         public MessageBase(T _value)
//         {
//             value = _value;
//         }
//         public override string ToString()
//         {
//             return $"name: {name}\ttype: {messageType.ToString()}\tvalue: {value.ToString()}";
//         }
//     }

//     [Serializable]
//     public abstract class MessageArray<T> : MessageBase<T[]>
//     {

//         public MessageArray(T[] _value, string _name) : base(_value, _name)
//         {
//         }
//         public MessageArray(T[] _value) : base(_value)
//         {
//         }
//         public override string ToString()
//         {
//             return $"\nname: {name}\ntype: {messageType.ToString()}\nlength: {value.Length}\nvalue: {value.ElementsToString()}";
//         }
//     }


//     [Serializable]
//     public class NullMessageUnityEvent : UnityEvent<NullMessage> { }

//     [Serializable]
//     public class NullMessage : MessageBase<NullType>
//     {
//         public override MessageType messageType { get { return MessageType.Null; } }
//         public NullMessage(string _name) : base(new NullType(), _name) { }
//         public NullMessage() : base(new NullType()) { }
//     }


//     // [Serializable]
//     // public class ObjectMessageUnityEvent : UnityEvent<ObjectMessage> { }
//     // [Serializable]
//     // public class ObjectArrayMessageUnityEvent : UnityEvent<ObjectArrayMessage> { }
//     // [Serializable]
//     // public class ObjectMessage : MessageBase<object>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Object; } }
//     //     public ObjectMessage(object _value, string _name) : base(_value, _name) { }
//     //     public ObjectMessage(object _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class ObjectArrayMessage : MessageArray<object>
//     // {
//     //     public override MessageType messageType { get { return MessageType.ObjectArray; } }
//     //     public ObjectArrayMessage(object[] _value, string _name) : base(_value, _name) { }
//     //     public ObjectArrayMessage(object[] _value) : base(_value) { }
//     // }


//     // [Serializable]
//     // public class BoolMessageUnityEvent : UnityEvent<BoolMessage> { }
//     // [Serializable]
//     // public class BoolArrayMessageUnityEvent : UnityEvent<BoolArrayMessage> { }
//     // [Serializable]
//     // public class BoolMessage : MessageBase<bool>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Bool; } }
//     //     public BoolMessage(bool _value, string _name) : base(_value, _name) { }
//     //     public BoolMessage(bool _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class BoolArrayMessage : MessageArray<bool>
//     // {
//     //     public override MessageType messageType { get { return MessageType.BoolArray; } }
//     //     public BoolArrayMessage(bool[] _value, string _name) : base(_value, _name) { }
//     //     public BoolArrayMessage(bool[] _value) : base(_value) { }
//     // }


//     // [Serializable]
//     // public class StringMessageUnityEvent : UnityEvent<StringMessage> { }
//     // [Serializable]
//     // public class StringArrayMessageUnityEvent : UnityEvent<StringArrayMessage> { }
//     // [Serializable]
//     // public class StringMessage : MessageBase<string>
//     // {
//     //     public override MessageType messageType { get { return MessageType.String; } }
//     //     public StringMessage(string _value, string _name) : base(_value, _name) { }
//     //     public StringMessage(string _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class StringArrayMessage : MessageArray<string>
//     // {
//     //     public override MessageType messageType { get { return MessageType.StringArray; } }
//     //     public StringArrayMessage(string[] _value, string _name) : base(_value, _name) { }
//     //     public StringArrayMessage(string[] _value) : base(_value) { }
//     // }


//     // [Serializable]
//     // public class IntMessageUnityEvent : UnityEvent<IntMessage> { }
//     // [Serializable]
//     // public class IntArrayMessageUnityEvent : UnityEvent<IntArrayMessage> { }
//     // [Serializable]
//     // public class IntMessage : MessageBase<int>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Int; } }
//     //     public IntMessage(int _value, string _name) : base(_value, _name) { }
//     //     public IntMessage(int _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class IntArrayMessage : MessageArray<int>
//     // {
//     //     public static readonly int maxLength = 307;
//     //     public override MessageType messageType { get { return MessageType.IntArray; } }
//     //     public IntArrayMessage(int[] _value, string _name) : base(_value, _name) { }
//     //     public IntArrayMessage(int[] _value) : base(_value) { }
//     // }


//     // [Serializable]
//     // public class FloatMessageUnityEvent : UnityEvent<FloatMessage> { }
//     // [Serializable]
//     // public class FloatArrayMessageUnityEvent : UnityEvent<FloatArrayMessage> { }
//     // [Serializable]
//     // public class FloatMessage : MessageBase<float>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Float; } }
//     //     public FloatMessage(float _value, string _name) : base(_value, _name) { }
//     //     public FloatMessage(float _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class FloatArrayMessage : MessageArray<float>
//     // {
//     //     public override MessageType messageType { get { return MessageType.FloatArray; } }
//     //     public FloatArrayMessage(float[] _value, string _name) : base(_value, _name) { }
//     //     public FloatArrayMessage(float[] _value) : base(_value) { }
//     // }


//     // [Serializable]
//     // public class Vec2MessageUnityEvent : UnityEvent<Vec2Message> { }
//     // [Serializable]
//     // public class Vec2ArrayMessageUnityEvent : UnityEvent<Vec2ArrayMessage> { }
//     // [Serializable]
//     // public class Vec2Message : MessageBase<Vec2>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Vec2; } }
//     //     public Vec2Message(Vec2 _value, string _name) : base(_value, _name) { }
//     //     public Vec2Message(Vec2 _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class Vec2ArrayMessage : MessageArray<Vec2>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Vec2Array; } }
//     //     public Vec2ArrayMessage(Vec2[] _value, string _name) : base(_value, _name) { }
//     //     public Vec2ArrayMessage(Vec2[] _value) : base(_value) { }
//     // }


//     // [Serializable]
//     // public class Vec3MessageUnityEvent : UnityEvent<Vec3Message> { }
//     // [Serializable]
//     // public class Vec3ArrayMessageUnityEvent : UnityEvent<Vec3ArrayMessage> { }
//     // [Serializable]
//     // public class Vec3Message : MessageBase<Vec3>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Vec3; } }
//     //     public Vec3Message(Vec3 _value, string _name) : base(_value, _name) { }
//     //     public Vec3Message(Vec3 _value) : base(_value) { }
//     // }
//     // [Serializable]
//     // public class Vec3ArrayMessage : MessageArray<Vec3>
//     // {
//     //     public override MessageType messageType { get { return MessageType.Vec3Array; } }
//     //     public Vec3ArrayMessage(Vec3[] _value, string _name) : base(_value, _name) { }
//     //     public Vec3ArrayMessage(Vec3[] _value) : base(_value) { }
//     // }

// }