#pragma once
#include "Vector2.h"

struct PlayerData
{
	Vector2 pos;
	Vector2 posOld;
	float width;
	float height;
	Vector2 velocity;
	Vector2 acceleration;


	Vector2Int rightTop;
	Vector2Int leftTop;
	Vector2Int rightBottom;
	Vector2Int leftBottom;
};