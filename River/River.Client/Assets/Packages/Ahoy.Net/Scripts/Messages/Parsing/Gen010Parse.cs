using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class Gen010Parse
    {

        public static byte[] EncodeToBytes(byte channel, byte command, gen010 data)
        {
            return EncodeToBytes(channel, command, new gen010[] { data });
        }
        public static byte[] EncodeToBytes(byte channel, byte command, gen010[] data)
        {
            var len = 3;
            var bytes = new byte[len];
            bytes[0] = channel;
            bytes[1] = command;
            bytes[2] = (byte)DataType.None;
            return bytes;
        }
    }

}