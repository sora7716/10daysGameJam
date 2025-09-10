#pragma once
#include "calc/Vector2.h"
#include <cstdint>

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
	kPlayer,
	kGoal
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

const int32_t kParticleNum = 3000; //パーティクルの数
const int32_t kParticleSize = 80; //パーティクルのサイズ

//パーティクルに使うやつ
struct ParticleProp
{
	Vector2 position; //パーティクルの位置
	Vector2 beginPosition; //パーティクルの初期位置
	float speed; //パーティクルの速度
	float angle; //パーティクルの角度
	uint32_t color; //パーティクルの色
	bool isAlive; //パーティクルが生きているかどうか
};

//エミッター
struct ParticleSystemData 
{
	Vector2 emitter;
	float speed;
	int textureHandle;
	float minAngle;
	float maxAngle;
	bool isAlive;
};



