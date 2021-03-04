using UnityEngine;


public static class Vector3Extensions
{
    public static Vector3 Add(this Vector3 vec, float a)
    {
        return new Vector3(vec.x + a, vec.y + a, vec.z + a);
    }
    public static Vector3 Subtract(this Vector3 vec, float a)
    {
        return new Vector3(vec.x - a, vec.y - a, vec.z - a);
    }
    public static Vector3 Add(this Vector3 vec, Vector3 other)
    {
        return new Vector3(vec.x + other.x, vec.y + other.y, vec.z + other.z);
    }
    public static Vector3 Subtract(this Vector3 vec, Vector3 other)
    {
        return new Vector3(vec.x - other.x, vec.y - other.y, vec.z - other.z);
    }
    public static Vector3 Multiply(this Vector3 vec, Vector3 other)
    {
        return new Vector3(vec.x * other.x, vec.y * other.y, vec.z * other.z);
    }
    public static Vector3 Divide(this Vector3 vec, Vector3 other)
    {
        return new Vector3(vec.x / other.x, vec.y / other.y, vec.z / other.z);
    }



}
