#include "Particle.h"
#include"Novice.h"
#include <stdlib.h>
#include <time.h>
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
void Particles::Initialize(const ParticleSystemData& particleSystemData)
{

	//ランド関数の初期化
	srand(static_cast<unsigned int>(time(nullptr)));

	//パーティクルシステムのデータを受け取る
	particleSystemData_ = particleSystemData;

	for (int32_t i = 0; i < kParticleNum; i++) {
		//マウスのクリックした位置に配置
		particle[i].position = particleSystemData_.emitter;
	}
}

//更新
void Particles::Update()
{
	//パーティクルの生成
	if (particleSystemData_.isAlive) {
		for (int32_t i = 0; i < kParticleNum; i++) {
			//パーティクルが生きていないなら
			if (!particle[i].isAlive) {
				particle[i].isAlive = true;//パーティクルが生きている状態にする
				particle[i].speed = particleSystemData_.speed; //パーティクルの速度
				particle[i].color = WHITE; //パーティクルの色
				if (particleSystemData_.isCircle) {
					particle[i].angle = static_cast<float>(rand() % 360);//度数法でランダムな角度をもとめる
				}
				else {

				}
				particle[i].angle = ConversionToRadian(particle[i].angle);//角度をラジアンに変換
				break;
			}
		}
	}

	//パーティクルの移動
	for (int32_t i = 0; i < kParticleNum; i++) {
		if (particle[i].isAlive) {
			//極座標で動かす
			particle[i].position.x += particle[i].speed * cosf(particle[i].angle);
			particle[i].position.y += particle[i].speed * sinf(particle[i].angle);
			//パーティクルのアルファ値を変化させていく
			if (particle[i].color > 0xFFFFFF00) {
				particle[i].color -= 0x00000001;
			}
			else {
				particle[i].isAlive = false;//パーティクルが死んだ状態にする
				particle[i].position = particleSystemData_.emitter;//パーティクルの位置を初期位置に戻す
				particle[i].color = WHITE; //パーティクルの色を元に戻す
			}
		}
	}

}

//描画
void Particles::Draw()
{
	//パーティクル
	for (int32_t i = 0; i < kParticleNum; i++) {
		if (particle[i].isAlive) {
			Novice::DrawSprite(
				static_cast<int32_t>(particle[i].position.x),
				static_cast<int32_t>(particle[i].position.y),
				particleSystemData_.textureHandle,
				1.0f, 1.0f, 0.0f, particle[i].color
			);
		}
	}
}