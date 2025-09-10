#pragma once
#include "calc/Vector2.h"

/// <summary>
/// チャンクの切り替えスイッチ
/// </summary>
class GameSwitch
{
public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">表示する座標</param>
	/// <param name="size">大きさ</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(const Vector2& position, const Vector2& size, int textureHandle );

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 
	/// </summary>
	void DrawRect();

	/// <summary>
	/// スイッチを押したかどうかのゲッター
	/// </summary>
	/// <returns>スイッチを押したかどうか</returns>
	bool IsPressSwitch() { return isPressSwitch_; };

	/// <summary>
	/// マウスの座標のセッター
	/// </summary>
	/// <param name="mousePos">マウスの座標</param>
	void SetMousePos(const Vector2Int& mousePos)
	{
		mousePos_ = { static_cast<float>(mousePos.x),static_cast<float>(mousePos.y) };
	}

	/// <summary>
	/// スイッチを押したかどうかのセッター
	/// </summary>
	/// <param name="isPressSwitch">スイッチを押したかどうかのセッター</param>
	void SetIsPressSwitch(bool isPressSwitch) { isPressSwitch_ = isPressSwitch; };

private://メンバ変数
	//座標
	Vector2 position_ = {};
	//サイズ
	Vector2 size_ = {};
	//マウスの位置
	Vector2 mousePos_ = {};
	//当たったかのフラグ
	bool isPressSwitch_ = false;

	int start = 0;

	//色
	unsigned int color_ = 0;
	//テクスチャ
	int textureHandle_ = 0;
	
	
};