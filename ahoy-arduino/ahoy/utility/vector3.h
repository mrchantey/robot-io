#pragma once
#include "./math.h"

struct Vector3
{
	float x = 0;
	float y = 0;
	float z = 0;

public:
	Vector3() {}
	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float Length()
	{
		float h = sqrt(x * x + y * y);
		return sqrt(h * h + z * z);
	}

	Vector3 operator+(Vector3 const &other)
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 operator-(Vector3 const &other)
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	static float Distance(Vector3 a, Vector3 b)
	{
		return (b - a).Length();
	}

	static Vector3 One()
	{
		return Vector3(1, 1, 1);
	}
	static Vector3 Zero()
	{
		return Vector3(0, 0, 0);
	}

	static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		return Vector3(
			Math::Lerp(a.x, b.x, t),
			Math::Lerp(a.y, b.y, t),
			Math::Lerp(a.z, b.z, t));
	}

	static Vector3 Scale(Vector3 val, float t)
	{
		return Vector3(
			val.x * t,
			val.y * t,
			val.z * t);
	}
};