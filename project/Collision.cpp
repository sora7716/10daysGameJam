#include "Collision.h"
#include <imgui.h>
#include "gameObject/Player.h"
#include<Novice.h>

void Collision::Initialize(Player* player, char* keys, char* preKeys)
{
	keys_ = keys;
	preKeys_ = preKeys;
	player_ = player;
}

void Collision::Update()
{
	Vector2 radius = { player_->GetPlayerData().width / 2.0f ,player_->GetPlayerData().height / 2.0f };
	Vector2 center = player_->GetPlayerData().pos + radius;
	Vector2Int leftBottom = { static_cast<int>(center.x - radius.x) / kBlockSize,static_cast<int>(center.y + radius.y) / kBlockSize };
	Vector2Int rightBottom = { static_cast<int>(center.x + radius.x) / kBlockSize,static_cast<int>(center.y + radius.y) / kBlockSize };
	player_->SetCenter(center);
	player_->SetLeftBottom(leftBottom);
	player_->SetRightBottom(rightBottom);


	// 上方向の移動

		/*playerData_.leftTop.y = static_cast<int>(playerData_.pos.y - playerData_.velocity.y) / kMapSize;
		playerData_.rightTop.y = static_cast<int>(playerData_.pos.y - playerData_.velocity.y) / kMapSize;

		if (map[playerData_.leftTop.y][playerData_.leftTop.x] == 1) {
			playerData_.pos.x = playerData_.posOld.x;
			playerData_.pos.y = playerData_.posOld.y;

		} else if (map[playerData_.rightTop.y][playerData_.rightTop.x] == 1) {
			playerData_.pos.x = playerData_.posOld.x;
			playerData_.pos.y = playerData_.posOld.y;

		} else {
			playerData_.pos.y -= playerData_.velocity.y;
		}*/



		// 左方向の移動

	Vector2Int leftTop = { static_cast<int>(center.x - radius.x) / kBlockSize, static_cast<int>(center.y - radius.y) / kBlockSize };

	bool isHit = false;
	if (map[leftTop.y][leftTop.x] == 1)
	{
		isHit = true;
		player_->SetPosition({ center.x,player_->GetPlayerData().pos.y });
	}
	/*else if (map[leftBottom.y][leftBottom.x] == 1)
	{
		player_->SetPosition(player_->GetPlayerData().posOld);
	}*/

	// 下方向の移動

/*player_->SetLeftBottom
({
	static_cast<int>(player_->GetPlayerData().pos.x) / kMapSize,
	static_cast<int>(player_->GetPlayerData().pos.y + (player_->GetPlayerData().height - 1.0f)) / kMapSize
});

player_->SetRightBottom
({
	static_cast<int>(player_->GetPlayerData().pos.x - (player_->GetPlayerData().width - 1.0f)) / kMapSize,
	static_cast<int>(player_->GetPlayerData().pos.y + (player_->GetPlayerData().height - 1.0f)) / kMapSize
});*/


//if (player_->IsJump())
//{
//	if (map[player_->GetPlayerData().leftBottom.y][player_->GetPlayerData().leftBottom.x] == 1 || map[player_->GetPlayerData().rightBottom.y][player_->GetPlayerData().rightBottom.x] == 1)
//	{
//		//player_->SetVelocity({ player_->GetPlayerData().velocity.x,0.0f });
//		player_->SetPosition(player_->GetPlayerData().posOld);
//		player_->SetIsJump(false);
//	}
//}

	if (map[rightBottom.y][rightBottom.x] == 1 || map[leftBottom.y][leftBottom.x] == 1)
	{
		player_->SetIsOnGround(false);
		//player_->SetPosition({ player_->GetPlayerData().pos.x,center.y - radius.y });
	}
	else
	{
		player_->SetIsOnGround(true);
	}

	ImGui::Begin("map");
	ImGui::DragFloat2("center", &center.x);
	ImGui::DragFloat2("radius", &radius.x);
	ImGui::DragInt2("leftBottom", &leftBottom.x);
	ImGui::DragInt2("rightBottom", &rightBottom.x);
	ImGui::Text("mapLeftTop:%d", map[leftTop.y][leftTop.x]);
	ImGui::Text("mapLeftBottom:%d", map[leftBottom.y][leftBottom.x]);
	ImGui::Text("mapRightBottom:%d", map[rightBottom.y][rightBottom.x]);
	ImGui::Checkbox("isHit", &isHit);
	ImGui::End();
	//playerData_.leftBottom.y = static_cast<int>(playerData_.pos.y + playerData_.height - 1.0f + playerData_.velocity.y) / kMapSize;
//playerData_.rightBottom.y = static_cast<int>(playerData_.pos.y + playerData_.height - 1.0f + playerData_.velocity.y) / kMapSize;


	/*else if ()
	{
		player_->SetPosition(player_->GetPlayerData().posOld);
	}*/
	/*else {
		playerData_.pos.y += playerData_.velocity.y;
	}*/


	// 右方向の移動

		/*playerData_.rightTop.x = static_cast<int>(   playerData_.pos.x + playerData_.width - 1.0f + playerData_.velocity.x) / kMapSize;
		playerData_.rightBottom.x = static_cast<int>(playerData_.pos.x + playerData_.height - 1.0f + playerData_.velocity.x) / kMapSize;

		if (map[playerData_.rightTop.y][playerData_.rightTop.x] == 1) {
			playerData_.pos.x = playerData_.posOld.x;
			playerData_.pos.y = playerData_.posOld.y;

		} else if (map[playerData_.rightBottom.y][playerData_.rightBottom.x] == 1) {
			playerData_.pos.x = playerData_.posOld.x;
			playerData_.pos.y = playerData_.posOld.y;

		} else {
			playerData_.pos.x += playerData_.velocity.x;
		}*/




}

void Collision::Draw()
{
	Novice::DrawBox(
		static_cast<int>(origin.x) + mapPos.x * kBlockSize,
		static_cast<int>(origin.y) + mapPos.y * kBlockSize,
		mapSize.x * kBlockSize,
		mapSize.y * kBlockSize,
		0.0f, 0x00FF0055, kFillModeSolid
	);


	//ブロック
	for (int y = 0; y < kMapHeight; ++y) {
		for (int x = 0; x < kMapWidth; ++x) {
			if (map[y][x] == 1) {
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize,
					kBlockSize, kBlockSize, 0.0f, 0Xa9a9a9FF, kFillModeSolid
				);
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize,
					kBlockSize, kBlockSize, 0.0f, BLACK, kFillModeWireFrame
				);
			}
			else if (map[y][x] == 2)
			{
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize,
					kBlockSize, kBlockSize, 0.0f, RED, kFillModeSolid
				);
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize,
					kBlockSize, kBlockSize, 0.0f, BLACK, kFillModeWireFrame
				);
			}
			else if (map[y][x] == 0)
			{
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize,
					kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeSolid
				);
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize,
					kBlockSize, kBlockSize, 0.0f, BLACK, kFillModeWireFrame
				);
			}
		}
	}





	/*Novice::ScreenPrintf(820, 400, "LeftTop: map[%d][%d]", playerData_.leftTop.y, playerData_.leftTop.x);
	Novice::ScreenPrintf(820, 440, "LeftBottom: map[%d][%d]", playerData_.leftBottom.y, playerData_.leftBottom.x);
	Novice::ScreenPrintf(1070, 400, "RightTop: map[%d][%d]", playerData_.rightTop.y, playerData_.rightTop.x);
	Novice::ScreenPrintf(1070, 440, "RightBottom: map[%d][%d]", playerData_.rightBottom.y, playerData_.rightBottom.x);*/

}
