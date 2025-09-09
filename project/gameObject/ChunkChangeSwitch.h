#pragma once
#include "calc/Vector2.h"

/// <summary>
/// チャンクの切り替えスイッチ
/// </summary>
class ChunkChangeSwitch
{
public://メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="position">表示する座標</param>
	void Initialize(const Vector2& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

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

private://メンバ変数
	//座標
	Vector2 position_ = {};
	//サイズ
	Vector2 size_ = {};
	//マウスの位置
	Vector2 mousePos_ = {};
	//当たったかのフラグ
	bool isPressSwitch_ = false;
};