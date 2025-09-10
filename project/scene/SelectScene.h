#pragma once
#include "gameObject/ResourceData.h"

class GameSwitch;

/// <summary>
/// セレクトシーン
/// </summary>
class SelectScene
{
private://メンバ変数

	//マウスの座標
	Vector2Int* mousePos_ = {};

	//次のシーン
	Scene nextScene_ = kNone;

	//シーンの終了フラグ
	bool isFinished_ = false;

	//ゲームシーン
	GameSwitch* gameSwitch_[4] = { nullptr };

	Vector2 gameSwitchPos_[4] = {};

	int bgTex_[6] = {};

	int stageMoji_[4] = {};

	int stageTitleName = 0;

	int switchTex = 0;

	Vector2 stageNamePos = {};

	Vector2 screenPos_{ 351.0f ,137.0f };
	int screenTextureList_[4] = {};
	int screenTexture_ = 0;

public://メンバ関数

	void Initialize(Vector2Int* mousePos);

	void Update();

	void Draw();

	Scene GetNextScene() { return nextScene_; };

	bool IsFinised() { return isFinished_; };
};

