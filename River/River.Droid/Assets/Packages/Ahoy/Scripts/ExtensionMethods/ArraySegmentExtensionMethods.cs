using System;
using UnityEngine;


public static class ArraySegmentExtensions
{


    public static void SetElement<T>(this ArraySegment<T> seg, int index, T val)
    {
        seg.Array[seg.Offset + index] = val;
    }
    public static ArraySegment<T> ToSeek<T>(this ArraySegment<T> seg, int offset)
    {
        return new ArraySegment<T>(seg.Array, seg.Offset + offset, seg.Count - offset);
    }

    public static T GetElement<T>(this ArraySegment<T> seg, int index)
    {
        return seg.Array[seg.Offset + index];
    }

    // public static string SegmentElementsToString<T>(this ArraySegment<T> arr)
    // {
    //     var str = "";
    //     for (int i = arr.Offset; i < arr.Offset + arr.Count; i++)
    //     {
    //         str += arr.Array[i];
    //         if (i != arr.Offset + arr.Count - 1) ;
    //         str += ",";
    //     }
    //     return str;
    // }
}
