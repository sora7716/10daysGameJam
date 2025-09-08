#include "Collision.h"
#include <imgui.h>
#include "gameObject/Player.h"
#include<Novice.h>

//マップチップの衝突判定
void Collision::IsMapChipCollision()
{
	Vector2Int leftTop = player_->GetPlayerData().leftTop;
	Vector2Int rightTop = player_->GetPlayerData().rightTop;
	Vector2Int leftBottom = player_->GetPlayerData().leftBottom;
	Vector2Int rightBottom = player_->GetPlayerData().rightBottom;

	Vector2 center = player_->GetPlayerData().gameObject.center;
	Vector2 radius = player_->GetPlayerData().gameObject.radius;
	Vector2 velocity = player_->GetPlayerData().gameObject.velocity;
	static Vector2 newCenter = {};

	if (velocity.y > 0.0f)
	{
		//下方向の判定
		leftBottom.y = static_cast<int>(center.y + radius.y + velocity.y) / kBlockSize;
		rightBottom.y = static_cast<int>(center.y + radius.y + velocity.y) / kBlockSize;

		if (map_[leftBottom.y][leftBottom.x] == 1 ||
			map_[rightBottom.y][rightBottom.x] == 1)
		{
			player_->SetIsOnGround(true);
			newCenter = { center.x,static_cast<float>((leftBottom.y) * kBlockSize) - radius.y - 1.7f };
			player_->SetCenter(newCenter);
		}
	} 
	else
	{
		//当たってないときの判定
		if (map_[leftBottom.y][leftBottom.x] != 1 &&
			map_[rightBottom.y][rightBottom.x] != 1)
		{
			player_->SetIsOnGround(false);
		}

		//上方向の判定
		Vector2Int top =
		{
			static_cast<int>(center.x) / kBlockSize,
			static_cast<int>(center.y - radius.y + velocity.y) / kBlockSize
		};
		if (map_[top.y][top.x] == 1 || map_[top.y][top.x] == 2)
		{
			newCenter = { center.x,static_cast<float>((top.y + 1) * kBlockSize) + radius.y };
			player_->SetCenter(newCenter);
			player_->SetVelocity({ velocity.x,0.0f });
		}
	}

	//右の判定
	Vector2Int right =
	{
		static_cast<int>(center.x + radius.x + velocity.x) / kBlockSize,
		static_cast<int>(center.y) / kBlockSize
	};

	if (map_[right.y][right.x] == 1)
	{

		velocity.x = 0.0f;
		player_->SetVelocity(velocity);
		if (player_->IsMove()) 
		{
			player_->SetIsJump(true);
		} 
		else
		{
			player_->SetIsOnGround(false);
			velocity.y = 0.0f;
			player_->SetVelocity(velocity);
		}
	}

#ifdef _DEBUG
	ImGui::Begin("map_");
	ImGui::Text("leftTop:%d", map_[leftTop.y][leftTop.x]);
	ImGui::Text("rightTop:%d", map_[rightTop.y][rightTop.x]);
	ImGui::Text("leftBottom:%d", map_[leftBottom.y][leftBottom.x]);
	ImGui::Text("rightBottom:%d", map_[rightBottom.y][rightBottom.x]);
	ImGui::DragFloat2("newCenter", &newCenter.x);
#endif // _DEBUG

}