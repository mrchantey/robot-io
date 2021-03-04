using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class IntParse
    {
        static readonly int STRIDE = 4;

        public static byte[] EncodeToBytes(byte channel, byte command, int val)
        {
            return EncodeToBytes(channel, command, new int[] { val });
        }

        public static byte[] EncodeToBytes(byte channel, byte command, int[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Int;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bv = BitConverter.GetBytes(arr[ai]);
                bytes.Insert(bv, bi, 4);
            }
            return bytes;
        }

        public static int[] ToInts(ArraySegment<byte> bytes)
        {
            var arrLen = bytes.Count / STRIDE;
            var arr = new int[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                arr[ai] = BitConverter.ToInt32(bytes.Array, bi);
            }
            return arr;
        }

    }

}