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

enum class PlayerState
{
	kIdol,
	kWork,
	kJump,
	kCount
};


//プレイヤーデータ
struct PlayerData
{
	GameObject gameObject;
	Vector2 beginPos;
	int textureHandles[static_cast<int>(PlayerState::kCount)];
	Vector2Int uvPos;
	Vector2Int rightTop;
	Vector2Int leftTop;
	Vector2Int rightBottom;
	Vector2Int leftBottom;
	int frameCount;
	int time;
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
	kStart,
	kReset,
	kCount
};

//タイルのテクスチャ
enum class TileTex 
{
	kUpper,
	kUnder,
	kCount
};
enum class soundEffects
{
	kStart,
	kReset,
	kSelect,
	kBgm,
	kInversion,
	kChange,
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

