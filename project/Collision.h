#pragma once
#include "Vector2.h"
class Player;

const int kMapWidth = 20;
const int kMapHeight = 13;
const int kBlockSize = 32;


class Collision
{
private:

	//	メンバー変数
	Player* player_ = nullptr;
	char* keys_ = {};
	char* preKeys_ = {};
	int map[kMapHeight][kMapWidth] =
	{


		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1},
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1},
		{0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1},
		{0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	};
	Vector2 origin = { 0.0f,0.0f };
	Vector2Int mapPos = { 0,0 };
	Vector2Int mapSize = { 5,5 };

public:
	//メンバー関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="keys">現在のキー</param>
	/// <param name="preKeys">過去のキー</param>
	void Initialize(Player* player, char* keys, char* preKeys);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画>
	/// </summary>
	void Draw();
};








