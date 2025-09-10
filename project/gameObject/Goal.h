#pragma once
#include "calc/Vector2.h"
#include <vector>
#include "Particle.h"

/// <summary>
/// ゴール
/// </summary>
class Goal
{
private: //メンバ変数

	//位置
	Vector2 pos_ = {};

	//テクスチャ
	int textureHundle_;

	//衝突する対象の座標
	Vector2 targetPos_ = {};

	//衝突する対象の半径
	float targetRadius_=0.0f;

	//衝突したかどうかのフラグ
	bool isCollision_ = false;

	Particle* particle_ = nullptr;
	ParticleSystemData particleData_ = {};

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="map">マップ</param>
	/// <param name="textureHundle">テクスチャハンドル</param>
	void Initialize(const std::vector<std::vector<int>>&map, int textureHundle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// セッター：TargetPos
	/// </summary>
	/// <param name="targetPos">衝突する対象の座標</param>
	void SetTargetPos(Vector2 targetPos) { targetPos_ = targetPos; };

	/// <summary>
	/// 衝突したかどうかのフラグ
	/// </summary>
	/// <returns>衝突したかどうかのフラグ</returns>
	bool IsCollision() { return isCollision_; };

};

