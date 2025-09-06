#pragma once
#include "gameObject/PlayerData.h"
class Player
{
private://	メンバー変数


	float timer = 0.0f;
	char* keys_ = {};
	char* preKeys_ = {};
	bool isMove_ = false;
	bool isOnGround_ = false;
	int deadTimer_ = false;
	int dead_ = false;

	PlayerData playerData_ = {};
	Vector2 center_ = {};

public://メンバー関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="keys">現在のキー</param>
	/// <param name="preKeys">過去のキー</param>
	void Initialize(char* keys, char* preKeys);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	PlayerData GetPlayerData()const { return playerData_; };

	void SetPlayerData(const PlayerData& playerData) { playerData_ = playerData; };

	bool IsOnGround() { return isOnGround_; };

	void SetLeftTop(const Vector2Int& leftTop);
	void SetLeftBottom(const Vector2Int& leftBottom);
	void SetRightTop(const Vector2Int& rightTop);
	void SetRightBottom(const Vector2Int& rightBottom);

	void SetPosition(const Vector2& pos);

	void SetVelocity(const Vector2& velocity);

	void SetIsOnGround(bool isJump) { isOnGround_ = isJump; };

	void SetCenter(const Vector2& center) { center_ = center; };
private:

	void CheackMapChipPosition();
};


