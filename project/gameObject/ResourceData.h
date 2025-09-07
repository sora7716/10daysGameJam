#pragma once
#include "Vector2.h"

struct GameObject {
	Vector2 center;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 size;
	Vector2 radius;
};

struct PlayerData
{
	GameObject gameObject;
	Vector2Int rightTop;
	Vector2Int leftTop;
	Vector2Int rightBottom;
	Vector2Int leftBottom;
};