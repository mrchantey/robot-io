using UnityEngine;
using Unity.Entities;
using Unity.Collections;
using System.Linq;
using System;


public static class AhoyEntitiesExtensionMethods
{
    public static void ForEach<T>(this NativeArray<T> arr, System.Action<T> action) where T : struct
    {
        for (int i = 0; i < arr.Length; i++)
        {
            action(arr[i]);
        }
    }

    public static void ForEach<T>(this NativeArray<T> arr, System.Action<T, int> action) where T : struct
    {
        for (int i = 0; i < arr.Length; i++)
        {
            action(arr[i], i);
        }
    }

    public static string ElementsToString<T>(this NativeArray<T> arr) where T : struct
    {
        return String.Join(",", arr.Select(p => p.ToString()).ToArray());
    }


    public static void ForEach<T>(this NativeList<T> arr, System.Action<T, int> action) where T : struct
    {
        for (int i = 0; i < arr.Length; i++)
        {
            action(arr[i], i);
        }
    }

    public static void ForEach<T>(this NativeList<T> arr, System.Action<T> action) where T : struct
    {
        for (int i = 0; i < arr.Length; i++)
        {
            action(arr[i]);
        }
    }

    // public static string ElementsToString<T>(this NativeList<T> arr) where T : struct
    // {
    //     // return String.Join(",", arr.Select(p => p.ToString()).ToArray());
    // }


    public static void SafeDispose<T>(this NativeQueue<T> arr) where T : struct
    {
        if (arr.IsCreated)
            arr.Dispose();
    }

    public static void SafeDispose<T>(this NativeList<T> arr) where T : struct
    {
        if (arr.IsCreated)
            arr.Dispose();
    }

    public static NativeList<T> ConvertToNativeList<T>(this NativeQueue<T> arr, Allocator allocator = Allocator.Persistent) where T : struct
    {
        NativeList<T> list = new NativeList<T>(allocator);
        T el;

        while (arr.TryDequeue(out el))
        {
            list.Add(el);
        };
        // arr.SafeDispose();
        arr.Dispose();
        return list;
    }

}
