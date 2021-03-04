// using UnityEngine;
using System;

namespace Ahoy
{

    public static class Utility
    {
        static readonly DateTime epoch = new DateTime(1992, 2, 20);

        public static double GetTime()
        {
            return DateTime.Now.Subtract(epoch).TotalMilliseconds;
        }

    }

}