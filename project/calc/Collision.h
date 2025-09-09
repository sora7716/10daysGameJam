#pragma once
#include "gameObject/ResourceData.h"
#include <vector>
class Player;

/// <summary>
/// 衝突判定
/// </summary>
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
	void IsMapChipCollision();

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
	/// AABBと点の衝突判定
	/// </summary>
	/// <param name="aabb">aabb</param>
	/// <param name="point">点</param>
	/// <returns>衝突判定</returns>
	static bool IsPointInRect(const AABB& aabb,const Vector2& point);
};






