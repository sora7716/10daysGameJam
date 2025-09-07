#pragma once
struct Vector2
{
	float x;
	float y;

	//���Z
	Vector2& operator+=(const Vector2& v);
	//���Z
	Vector2 operator-(const Vector2& v);

	//���Z
	Vector2 operator+(const Vector2& v);

	//���Z
	Vector2 operator/(float n);
};

struct Vector2Int 
{
	int x;
	int y;
};