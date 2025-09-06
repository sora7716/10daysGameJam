#pragma once
struct Vector2
{
	float x;
	float y;

	//加算
	Vector2& operator+=(const Vector2& v);
	//減算
	Vector2 operator-(const Vector2& v);

	//加算
	Vector2 operator+(const Vector2& v);
};

struct Vector2Int 
{
	int x;
	int y;
};