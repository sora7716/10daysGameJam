#pragma once
#include "gameObject/ResourceData.h"
#include <vector>

/// <summary>
/// プレイヤー
/// </summary>
class Player
{
private://	メンバー変数

	float timer = 0.0f;
	int deadTimer_ = false;
	int dead_ = false;
	//キー
	char* keys_ = {};
	char* preKeys_ = {};

	//地面の上にいるかのフラグ
	bool isOnGround_ = false;

	//ジャンプするかのフラグ
	bool isJump_ = false;

	//移動するかのフラグK
	bool isMove_ = false;

	//プレイヤーのデータ
	PlayerData playerData_ = {};

	//リセットボタン
	bool isReset_ = false;

	int playerTexIndex;


public://メンバー関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="keys">現在のキー</param>
	/// <param name="preKeys">過去のキー</param>
	/// <param name="map">マップ</param>
	/// <param name="textureHandles">テクスチャハンドル</param>
	void Initialize(char* keys, char* preKeys,std::vector<std::vector<int>>map,int* textureHandles);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーデータのゲッター
	/// </summary>
	/// <returns>プレイヤーデータ</returns>
	PlayerData GetPlayerData()const { return playerData_; };

	/// <summary>
	/// オブジェクトが地面にいるかどうかを判定します。
	/// </summary>
	/// <returns>オブジェクトが地面にいるかどうか</returns>
	bool IsOnGround() { return isOnGround_; };

	/// <summary>
	/// 移動しているかどうかのゲッター
	/// </summary>
	/// <returns> 移動しているかどうか</returns>
	bool IsMove() { return isMove_; };

	/// <summary>
	/// 左上のマップチップ番号のセッター
	/// </summary>
	/// <param name="leftTop">左上</param>
	void SetLeftTop(const Vector2Int& leftTop) { playerData_.leftTop = leftTop; };

	/// <summary>
	/// 左下のマップチップ番号のセッター
	/// </summary>
	/// <param name="leftBottom">左下</param>
	void SetLeftBottom(const Vector2Int& leftBottom) { playerData_.leftBottom = leftBottom; };

	/// <summary>
	/// 右上のマップチップ番号のセッター
	/// </summary>
	/// <param name="rightTop">右上</param>
	void SetRightTop(const Vector2Int& rightTop) { playerData_.rightTop = rightTop; };

	/// <summary>
	/// 右下のマップチップ番号のセッター
	/// </summary>
	/// <param name="rightBottom">右下</param>
	void SetRightBottom(const Vector2Int& rightBottom) { playerData_.rightBottom = rightBottom; };

	/// <summary>
	/// 中心座標のセッター
	/// </summary>
	/// <param name="center">中心座標</param>
	void SetCenter(const Vector2& center) { playerData_.gameObject.center = center; };

	/// <summary>
	/// 速度のセッター
	/// </summary>
	/// <param name="velocity">速度</param>
	void SetVelocity(const Vector2& velocity) { playerData_.gameObject.velocity = velocity; };

	/// <summary>
	/// オブジェクトが地面にいるかどうかを判定するフラグのセッター
	/// </summary>
	/// <param name="isOnGround">地面にいるフラグ</param>
	void SetIsOnGround(bool isOnGround) { isOnGround_ = isOnGround; };

	/// <summary>
	/// ジャンプぐラグのセッター
	/// </summary>
	/// <param name="isJump">ジャンプフラグ</param>
	void SetIsJump(bool isJump) { isJump_ = isJump; };

	/// <summary>
	/// 移動フラグのセッター
	/// </summary>
	/// <param name="isMove">移動フラグ</param>
	void SetIsMove(bool isMove) { isMove_ = isMove; };

	/// <summary>
	/// リセットボタンのセッター
	/// </summary>
	/// <param name="isReset">リセットボタン</param>
	void SetIsReset(bool isReset) { isReset_ = isReset; };

	/// <summary>
	/// リセットのゲッター
	/// </summary>
	/// <returns>リセットフラグ</returns>
	bool IsReset() { return isReset_; };
private:

	/// <summary>
	/// マップチップ番号を検索
	/// </summary>
	void CheckMapChipIndex();
};


