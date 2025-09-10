#pragma once
#include "gameObject/ResourceData.h"

class Player;
class Collision;
class Map;
class GameSwitch;
class Goal;

/// <summary>
/// ステージ1
/// </summary>
class StageScene4
{
private://メンバ変数
	Player* player = nullptr;
	Collision* collision = nullptr;
	Vector2Int* mousePos_ = nullptr;

	int playerTexture = 0;

	//次のシーン
	Scene nextScene_ = kNone;

	//シーンの終了フラグ
	bool isFinised_ = false;

	Map* map = nullptr;

	GameSwitch* startSwitch = nullptr;

	AABB startSwitchData
	{
	.min{100.0f,600.0f},
	.max{132.0f,632.0f}
	};

	GameSwitch* resetSwitch = nullptr;

	AABB resetSwitchData
	{
	.min{150.0f,600.0f},
	.max{182.0f,632.0f}
	};

	//スターとボタンを押したかどうか　
	bool isPressStart_ = false;

	Goal* goal = nullptr;

	int bgTex_ = 0;

public://メンバ関数

	void Initialize(char* keys, char* preKeys, Vector2Int* mousePos);

	void Update();

	void Draw();

	~StageScene4();

	Scene GetNextScene() { return nextScene_; };

	bool IsFinised() { return isFinised_; };
};

