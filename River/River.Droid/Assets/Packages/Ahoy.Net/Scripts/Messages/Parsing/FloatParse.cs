using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class FloatParse
    {
        static readonly int STRIDE = 4;

        public static byte[] EncodeToBytes(byte channel, byte command, float val)
        {
            return EncodeToBytes(channel, command, new float[] { val });
        }

        public static byte[] EncodeToBytes(byte channel, byte command, float[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Float;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bv = BitConverter.GetBytes(arr[ai]);
                bytes.Insert(bv, bi, 4);
            }
            return bytes;
        }

        public static float[] ToFloats(ArraySegment<byte> bytes)
        {
            var arrLen = bytes.Count / STRIDE;
            var arr = new float[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                arr[ai] = BitConverter.ToSingle(bytes.Array, bi);
            }
            return arr;
        }

    }

}