#pragma once
#include "gameObject/ResourceData.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene
{
private://メンバ変数

	//マウスの座標
	Vector2Int* mousePos_ = nullptr;

	//次のシーン
	Scene nextScene_ = kNone;

	//シーンの終了フラグ
	bool isFinised_ = false;

public://メンバ関数

	void Initialize(Vector2Int*mousePos);

	void Update();

	void Draw();

	Scene GetNextScene() { return nextScene_; };

	bool IsFinished() { return isFinised_; };
};

