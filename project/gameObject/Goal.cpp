#include "Goal.h"
#include "ResourceData.h"
#include "calc/Collision.h"
#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

//初期化
void Goal::Initialize(const std::vector<std::vector<int>>& map, int textureHundle)
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == static_cast<int>(BlockType::kGoal))
			{
				pos_ =
				{
					static_cast<float>(x * kBlockSize),
					static_cast<float>(y * kBlockSize)
				};
			}
		}
	}

	textureHundle_ = textureHundle;

	targetRadius_ = static_cast<int>(kBlockSize) / 2;
	
	particle_ = new Particle();
	particleData_.emitter = { pos_.x + 16.0f,pos_.y + 16.0f };
	particleData_.isAlive = false;
	particleData_.minAngle = 0.0f;
	particleData_.maxAngle = 360.0f;
	particleData_.subtructColor = 0x00000009;
	particleData_.textureHandle = Novice::LoadTexture("./resources/particle.png");
	particle_->Initialize(particleData_);

}

int soundHandle = 0;
//更新
void Goal::Update()
{
	particle_->Update();

	AABB aabb
	{
		.min = pos_,
		.max = {pos_.x + static_cast<int>(kBlockSize),pos_.y + static_cast<int>(kBlockSize)}
	};
	Vector2 point =
	{
		targetPos_.x + targetRadius_,
		targetPos_.y
	};

	if (Collision::IsPointInRect(aabb, point))
	{
		if (!Novice::IsPlayingAudio(soundHandle)) {
			soundHandle = Novice::PlayAudio(static_cast<int>(soundEffects::kGoal), 0, 1);//
		}		

		isCollision_ = true;
	}

	particleData_.isAlive = true;
	particleData_.spawnCount = 5;
	particleData_.speed = 0.0f;
	particleData_.scale = 1.0f;
	particle_->SetParticleSystemData(particleData_);

#ifdef _DEBUG
	ImGui::Begin("goal");
	ImGui::Checkbox("isCollision", &isCollision_);
	ImGui::End();
#endif // _DEBUG

}

//描画
void Goal::Draw()
{
	particle_->DrawRect();
	Novice::DrawSprite(static_cast<int>(pos_.x), static_cast<int>(pos_.y), textureHundle_, 1.0f, 1.0f, 0.0f, WHITE);

}