#pragma once
#include "gameObject/ResourceData.h"
#include <vector>
class Player;

const int kMapWidth = 35;
const int kMapHeight = 11;
const int kBlockSize = 32;


class Collision
{
private://メンバ変数

	Player* player_ = nullptr;
	//マップ
	std::vector<std::vector<int>> map_;

public://メンバ関数

	/// <summary>
	/// マップチップの衝突判定
	/// </summary>
	void IsMapChip();

	/// <summary>
	/// プレイヤーのセッター
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player) { player_ = player; };

	/// <summary>
	/// マップのセッター
	/// </summary>
	/// <param name="map">マップ</param>
	void SetMap(std::vector<std::vector<int>> map) { map_ = map; };

	/// <summary>
	/// AABBとマウスカーソルの当たり判定
	/// </summary>
	/// <param name="aabb">aabb</param>
	/// <returns>当たり判定</returns>
	static bool IsMouseOverRect(AABB aabb);
};






