#include "Vector2.h"

//加算
Vector2& Vector2::operator+=(const Vector2& v)
{
	// TODO: return ステートメントをここに挿入します
	this->x += v.x;
	this->y += v.y;

	return *this;
}

//減算
Vector2 Vector2::operator-(const Vector2& v)
{
	Vector2 result = {
			result.x = x - v.x,
			result.y = y - v.y,
	};
	return result;
}

//加算
Vector2 Vector2::operator+(const Vector2& v)
{
	Vector2 result = {
		result.x = x + v.x,
		result.y = y + v.y,
	};
	return result;
}
