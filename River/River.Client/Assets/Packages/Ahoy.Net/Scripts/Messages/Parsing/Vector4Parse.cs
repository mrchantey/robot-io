using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class Vector4Parse
    {
        static readonly int STRIDE = 16;

        public static byte[] EncodeToBytes(byte channel, byte command, Vector4 val)
        {
            return EncodeToBytes(channel, command, new Vector4[] { val });
        }

        public static byte[] EncodeToBytes(byte channel, byte command, Vector4[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Vector4;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bx = BitConverter.GetBytes(arr[ai].x);
                bytes.Insert(bx, bi, 4);
                var by = BitConverter.GetBytes(arr[ai].y);
                bytes.Insert(by, bi + 4, 4);
                var bz = BitConverter.GetBytes(arr[ai].z);
                bytes.Insert(bz, bi + 8, 4);
                var bw = BitConverter.GetBytes(arr[ai].w);
                bytes.Insert(bw, bi + 12, 4);
            }
            return bytes;
        }

        public static Vector4[] ToVector4s(ArraySegment<byte> bytes)
        {
            var arrLen = bytes.Count / STRIDE;
            var arr = new Vector4[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                arr[ai] = new Vector4(
                    BitConverter.ToSingle(bytes.Array, bi),
                    BitConverter.ToSingle(bytes.Array, bi + 4),
                    BitConverter.ToSingle(bytes.Array, bi + 8),
                    BitConverter.ToSingle(bytes.Array, bi + 12));
            }
            return arr;
        }

    }

}