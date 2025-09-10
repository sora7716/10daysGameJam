#pragma once
#include "Vector2.h"
class Player
{
	private://	メンバー変数
		Vector2 pos_ = {};
		Vector2 Velocity_ = {};
		Vector2 acceleration_ = {};
		float radius = 50.0f;
		float timer = 0.0f;
		char* keys_ = {};
		char* preKeys_ = {};
		int Move = false;
		int jamp = false;
		int deadTimer = false;
		int dead = false;

public://メンバー関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="keys">現在のキー</param>
	/// <param name="preKeys">過去のキー</param>
	void Initialize(char * keys, char * preKeys);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};


