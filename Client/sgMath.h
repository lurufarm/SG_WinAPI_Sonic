#pragma once
#include <math.h>
#define PI 3.141592

struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}
	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}
	
	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2 & other)
	{
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}
	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}

	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}
	Vector2 operator/(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x / other.x;
		temp.y = y / other.y;

		return temp;
	}


	Vector2 operator*(float other)
	{
		Vector2 temp;
		temp.x = x * other;
		temp.y = y * other;

		return temp;
	}

	Vector2 operator/(float other)
	{
		Vector2 temp;
		temp.x = x / other;
		temp.y = y / other;

		return temp;
	}

	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}
	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}
	void operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}
	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}

	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}
	
	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Nomalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}

};

namespace sg::math
{
	inline static Vector2 Rotate(Vector2 vec, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vec.Nomalize();

		float x = vec.x * cosf(radian) - vec.y * sinf(radian);
		float y = vec.y * sinf(radian) + vec.y * cosf(radian);
		
		return Vector2(x, y);
	}

	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}
}

