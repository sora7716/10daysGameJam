#pragma once
#include "gameObject/ResourceData.h"
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

	void SetLeftTop(const Vector2Int& leftTop) { playerData_.leftTop = leftTop; };
	void SetLeftBottom(const Vector2Int& leftBottom) { playerData_.leftBottom = leftBottom; };;
	void SetRightTop(const Vector2Int& rightTop) { playerData_.rightTop = rightTop; };;
	void SetRightBottom(const Vector2Int& rightBottom) { playerData_.rightBottom = rightBottom; };;

	void SetCenter(const Vector2& center) { playerData_.gameObject.center = center; };

	void SetVelocity(const Vector2& velocity) { playerData_.gameObject.velocity = velocity; };

	void SetIsOnGround(bool isJump) { isOnGround_ = isJump; };

	//void SetCenter(const Vector2& center) { center_ = center; };
private:

	void CheackMapChipPosition();
};


