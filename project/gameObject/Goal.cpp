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

}

//更新
void Goal::Update()
{
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
		isCollision_ = true;
	}

#ifdef _DEBUG
	ImGui::Begin("goal");
	ImGui::Checkbox("isCollision", &isCollision_);
	ImGui::End();
#endif // _DEBUG

}

//描画
void Goal::Draw()
{
	Novice::DrawSprite(static_cast<int>(pos_.x), static_cast<int>(pos_.y), textureHundle_, 1.0f, 1.0f, 0.0f, WHITE);

}