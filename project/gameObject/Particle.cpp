#include "Particle.h"
#include"Novice.h"
#include <numbers>
#include <cmath>

/// <summary>
/// 度数法を弧度法に直す
/// </summary>
/// <param name="angle">度数法</param>
/// <returns>弧度法</returns>
float ConversionToRadian(float angle) {
	return angle * (std::numbers::pi_v<float> / 180.0f); //角度をラジアンに変換
}

//初期化
void Particle::Initialize(const ParticleSystemData& particleSystemData)
{
	//パーティクルシステムのデータを受け取る
	particleSystemData_ = particleSystemData;

	for (int32_t i = 0; i < kParticleNum; i++) {
		//マウスのクリックした位置に配置
		particle_[i].position = particleSystemData_.emitter;
	}

	//乱数エンジンの初期化
	std::random_device seedGenerator;
	randomEngine_.seed(seedGenerator());
}

//更新
void Particle::Update()
{
	//ランダムに設定
	std::uniform_real_distribution<float>distribution(particleSystemData_.minAngle, particleSystemData_.maxAngle);
	//パーティクルの生成
	if (particleSystemData_.isAlive) {
		for (int32_t i = 0; i < particleSystemData_.spawnCount; i++) {
			//パーティクルが生きていないなら
			if (!particle_[i].isAlive) {
				particle_[i].isAlive = true;//パーティクルが生きている状態にする
				particle_[i].speed = particleSystemData_.speed; //パーティクルの速度
				particle_[i].color = WHITE; //パーティクルの色
				particle_[i].angle = distribution(randomEngine_);//度数法でランダムな角度をもとめる
				particle_[i].angle = ConversionToRadian(particle_[i].angle);//角度をラジアンに変換
				break;
			}
		}
	}

	//パーティクルの移動
	for (int32_t i = 0; i < particleSystemData_.spawnCount; i++) {
		if (particle_[i].isAlive) {
			//極座標で動かす
			particle_[i].position.x += particle_[i].speed * cosf(particle_[i].angle);
			particle_[i].position.y += particle_[i].speed * sinf(particle_[i].angle);
			particle_[i].scale += particleSystemData_.scale;
			//パーティクルのアルファ値を変化させていく
			if (particle_[i].color > 0xFFFFFF00) {
				particle_[i].color -= particleSystemData_.subtructColor;
			}
			else {
				particle_[i].isAlive = false;//パーティクルが死んだ状態にする
				particle_[i].position = particleSystemData_.emitter;//パーティクルの位置を初期位置に戻す
				particle_[i].color = WHITE; //パーティクルの色を元に戻すparticle_[i].scale
				particle_[i].scale = 0.0f;
			}
		}
	}

}

//描画
void Particle::Draw()
{
	//パーティクル
	for (int32_t i = 0; i < particleSystemData_.spawnCount; i++) {
		if (particle_[i].isAlive) {
			Novice::DrawSprite(
				static_cast<int32_t>(particle_[i].position.x),
				static_cast<int32_t>(particle_[i].position.y),
				particleSystemData_.textureHandle,
				1.0f, 1.0f, 0.0f, particle_[i].color
			);
		}
	}
}

//頂点描画
void Particle::DrawRect()
{
	//パーティクル
	for (int32_t i = 0; i < particleSystemData_.spawnCount; i++) {
		if (particle_[i].isAlive) {

			Novice::DrawQuad
			(
				static_cast<int32_t>(particle_[i].position.x - particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.y - particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.x + particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.y - particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.x - particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.y + particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.x + particle_[i].scale),
				static_cast<int32_t>(particle_[i].position.y + particle_[i].scale),
				0, 0, 32, 32, particleSystemData_.textureHandle, particle_[i].color
			);
		}
	}
}
