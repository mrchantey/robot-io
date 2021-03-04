using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class BoolParse
    {
        static readonly int STRIDE = 4;

        public static byte[] EncodeToBytes(byte channel, byte command, bool val)
        {
            return EncodeToBytes(channel, command, new bool[] { val });
        }

        public static byte[] EncodeToBytes(byte channel, byte command, bool[] arr)
        {
            var headerLen = 3;
            var bArrLen = arr.Length * STRIDE;
            var totalLen = headerLen + bArrLen;
            var bytes = new byte[totalLen];

            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.Bool;
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = headerLen + ai * STRIDE;
                var bv = BitConverter.GetBytes(arr[ai]);
                bytes.Insert(bv, bi, 4);
            }
            return bytes;
        }

        public static bool[] ToBools(ArraySegment<byte> bytes)
        {
            var arrLen = bytes.Count / STRIDE;
            var arr = new bool[arrLen];
            for (int ai = 0; ai < arr.Length; ai++)
            {
                var bi = bytes.Offset + ai * STRIDE;
                arr[ai] = BitConverter.ToBoolean(bytes.Array, bi);
            }
            return arr;
        }

    }

}