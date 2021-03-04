using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class PoseParse
    {
        static readonly int STRIDE = 28;


        public static byte[] EncodeToBytes(byte channel, byte command, Pose val)
        {
            return EncodeToBytes(channel, command, new Pose[] { val });
        }
        public static byte[] EncodeToBytes(byte channel, byte command, Pose[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Pose;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bx1 = BitConverter.GetBytes(arr[ai].position.x);
                bytes.Insert(bx1, bi, 4);
                var by1 = BitConverter.GetBytes(arr[ai].position.y);
                bytes.Insert(by1, bi + 4, 4);
                var bz1 = BitConverter.GetBytes(arr[ai].position.z);
                bytes.Insert(bz1, bi + 8, 4);
                var bx2 = BitConverter.GetBytes(arr[ai].rotation.x);
                bytes.Insert(bx2, bi + 12, 4);
                var by2 = BitConverter.GetBytes(arr[ai].rotation.y);
                bytes.Insert(by2, bi + 16, 4);
                var bz2 = BitConverter.GetBytes(arr[ai].rotation.z);
                bytes.Insert(bz2, bi + 20, 4);
                var bw2 = BitConverter.GetBytes(arr[ai].rotation.w);
                bytes.Insert(bw2, bi + 24, 4);
            }
            // Debug.Log($"bytes encoded:{bytes.ElementsToString()}");
            return bytes;
        }


        public static Pose[] ToPoses(ArraySegment<byte> bytes)
        {

            var arrLen = bytes.Count / STRIDE;
            var arr = new Pose[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                var position = new Vector3(
                    BitConverter.ToSingle(bytes.Array, bi),
                    BitConverter.ToSingle(bytes.Array, bi + 4),
                    BitConverter.ToSingle(bytes.Array, bi + 8)
                );
                var rotation = new Quaternion(
                    BitConverter.ToSingle(bytes.Array, bi + 12),
                    BitConverter.ToSingle(bytes.Array, bi + 16),
                    BitConverter.ToSingle(bytes.Array, bi + 20),
                    BitConverter.ToSingle(bytes.Array, bi + 24)
                    );
                arr[ai] = new Pose(position, rotation);
            }
            // Debug.Log($"bytes decoded:{arr.ElementsToString()}");
            return arr;
        }

    }

}