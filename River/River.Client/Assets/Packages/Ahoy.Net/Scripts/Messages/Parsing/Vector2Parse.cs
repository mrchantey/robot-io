using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class Vector2Parse
    {
        static readonly int STRIDE = 8;

        public static byte[] EncodeToBytes(byte channel, byte command, Vector2 val)
        {
            return EncodeToBytes(channel, command, new Vector2[] { val });
        }

        public static byte[] EncodeToBytes(byte channel, byte command, Vector2[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Vector2;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bx = BitConverter.GetBytes(arr[ai].x);
                bytes.Insert(bx, bi, 4);
                var by = BitConverter.GetBytes(arr[ai].y);
                bytes.Insert(by, bi + 4, 4);
            }
            return bytes;
        }

        public static Vector2[] ToVector2s(ArraySegment<byte> bytes)
        {
            var arrLen = bytes.Count / STRIDE;
            var arr = new Vector2[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                arr[ai] = new Vector2(
                    BitConverter.ToSingle(bytes.Array, bi),
                    BitConverter.ToSingle(bytes.Array, bi + 4));
            }
            return arr;
        }

    }

}