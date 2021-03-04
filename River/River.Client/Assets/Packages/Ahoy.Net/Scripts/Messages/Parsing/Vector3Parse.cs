using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class Vector3Parse
    {
        static readonly int STRIDE = 12;

        public static byte[] EncodeToBytes(byte channel, byte command, Vector3 val)
        {
            return EncodeToBytes(channel, command, new Vector3[] { val });
        }

        public static byte[] EncodeToBytes(byte channel, byte command, Vector3[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Vector3;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bx = BitConverter.GetBytes(arr[ai].x);
                bytes.Insert(bx, bi, 4);
                var by = BitConverter.GetBytes(arr[ai].y);
                bytes.Insert(by, bi + 4, 4);
                var bz = BitConverter.GetBytes(arr[ai].z);
                bytes.Insert(bz, bi + 8, 4);
            }
            return bytes;
        }

        public static Vector3[] ToVector3s(ArraySegment<byte> bytes)
        {
            var arrLen = bytes.Count / STRIDE;
            var arr = new Vector3[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                arr[ai] = new Vector3(
                    BitConverter.ToSingle(bytes.Array, bi),
                    BitConverter.ToSingle(bytes.Array, bi + 4),
                    BitConverter.ToSingle(bytes.Array, bi + 8));
            }
            return arr;
        }

    }

}