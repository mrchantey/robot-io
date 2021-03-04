using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public enum DataType
    {
        __na__,//python enums start from 1
        None,
        Float,
        Vector2,
        Vector3,
        Vector4,
        Pose,
        Int,
        Bool,
        String
    }


    public static class MessageParse
    {

        public static Message<T> DecodeToMessage<T>(ArraySegment<byte> bytes)
        {
            return (Message<T>)DecodeToMessage(bytes);
        }

        public static Message DecodeToMessage(ArraySegment<byte> bytes)
        {
            var channel = bytes.GetElement(0);
            var command = bytes.GetElement(1);
            var dataType = (DataType)bytes.GetElement(2);
            var bodySlice = bytes.ToSeek(3);
            switch (dataType)
            {
                case DataType.Float:
                    return new Message<float>(channel, command, dataType, FloatParse.ToFloats(bodySlice));
                case DataType.Vector3:
                    return new Message<Vector3>(channel, command, dataType, Vector3Parse.ToVector3s(bodySlice));
                case DataType.Pose:
                    return new Message<Pose>(channel, command, dataType, PoseParse.ToPoses(bodySlice));
                case DataType.None:
                default:
                    return new Message(channel, command, dataType);
            }
        }


    }

}