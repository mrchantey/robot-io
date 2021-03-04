using System;
using UnityEngine;
using Ahoy;
namespace Ahoy.Net
{

    public static class NullParse
    {

        public static byte[] EncodeToBytes(byte channel, byte command)
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