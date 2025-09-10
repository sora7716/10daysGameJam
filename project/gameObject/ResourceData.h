#pragma once
#include "calc/Vector2.h"

enum Scene
{
	kTitle,
	kSelect,
	kStage1,
	kStage2,
	kStage3,
	kStage4,
	kNone
};

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
	Vector2 beginPos;
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

//スイッチのテクスチャ
enum class SwitchTex 
{
	kTransition,
	kInvert,
	kCount
};

//タイルのテクスチャ
enum class TileTex 
{
	kUpper,
	kUnder,
	kCount
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

//ブロックサイズ
const int kBlockSize = 32;

