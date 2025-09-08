#pragma once
#include "calc/Vector2.h"

//ゲームオブジェクト
struct GameObject 
{
	Vector2 center;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 size;
	Vector2 radius;
};


//プレイヤーデータ
struct PlayerData
{
	GameObject gameObject;
	int textureHandle;
	Vector2Int rightTop;
	Vector2Int leftTop;
	Vector2Int rightBottom;
	Vector2Int leftBottom;
};

//ブロックタイプ
enum class BlockType
{
	kBlank,
	kBlock,
	kPlayer
};

};

struct  Line
{
	Vector2Int startPos;
	Vector2Int endPos;
};

//AABB
struct AABB {
	Vector2 min;
	Vector2 max;
};

