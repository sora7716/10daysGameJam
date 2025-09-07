#pragma once
struct Vector2
{
	float x;
	float y;

	//‰ÁZ
	Vector2& operator+=(const Vector2& v);
	//Œ¸Z
	Vector2 operator-(const Vector2& v);

	//‰ÁZ
	Vector2 operator+(const Vector2& v);

	//œZ
	Vector2 operator/(float n);
};

struct Vector2Int 
{
	int x;
	int y;
};