#pragma once
#include "gameObject/ResourceData.h"
#include <random>

/// <summary>
/// パーティクル
/// </summary>
class Particle
{
private:

	//パーティクルシステムのデータ
	ParticleSystemData particleSystemData_ = { {},1.0f,0,false };

	//パーティクル
	ParticleProp particle_[kParticleNum] = {};

	//ランダムエンジン
	std::mt19937 randomEngine_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="particleSystemData">パーティクルシステムのデータ</param>
	void Initialize(const ParticleSystemData& particleSystemData);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 頂点描画
	/// </summary>
	void DrawRect();

	/// <summary>
	/// セッター：ParticleSystemData
	/// </summary>
	/// <param name="particleSystemData">パーティクルシステムのデータ</param>
	void SetParticleSystemData(const ParticleSystemData& particleSystemData) { particleSystemData_ = particleSystemData; };
};

