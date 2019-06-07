using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using System;
using Unity.Collections;
// namespace Ahoy
// {

public static class ExtensionMethods
{

    public static void ForEach<T>(this IEnumerable<T> source, System.Action<T> action)
    {
        foreach (var element in source)
        {
            action(element);
        }
    }

    public static void ForEach<T>(this IEnumerable<T> arr, System.Action<T, int> action)
    {
        for (int i = 0; i < arr.Count(); i++)
        {
            action(arr.ElementAt(i), i);
        }
    }

    public static string ElementsToString<T>(this IEnumerable<T> arr)
    {
        return String.Join(",", arr.Select(p => p.ToString()).ToArray());
    }

    public static IEnumerable<T> SubArray<T>(this IEnumerable<T> source, int startIndex, int count)
    {
        return source.Skip(startIndex).Take(count);
    }

}
// }