#include "Collision.h"
#include <imgui.h>
#include "gameObject/Player.h"
#include<Novice.h>

void Collision::Initialize(Player* player, char* keys, char* preKeys)
{
	keys_ = keys;
	preKeys_ = preKeys;
	player_ = player;
	Vector2 playerPos = player_->GetPlayerData().gameObject.center;
}

void Collision::Update()
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
		if (map[leftBottom.y][leftBottom.x] == 1 ||
			map[rightBottom.y][rightBottom.x] == 1)
		{
			player_->SetIsOnGround(true);
			newCenter = { center.x,static_cast<float>((leftBottom.y) * kBlockSize) - radius.y - 1.0f };
			player_->SetCenter(newCenter);
		}
	} else {
		//上方向の判定
		Vector2Int top =
		{
			static_cast<int>(center.x) / kBlockSize,
			static_cast<int>(center.y - radius.y + velocity.y) / kBlockSize
		};
		if (map[top.y][top.x] == 1)
		{
			newCenter = { center.x,static_cast<float>((top.y + 1) * kBlockSize) + radius.y };
			player_->SetCenter(newCenter);
			player_->SetVelocity({ velocity.x,0.0f });
		}
	}

	//当たってないときの判定
	if (map[leftBottom.y][leftBottom.x] == 1 ||
		map[rightBottom.y][rightBottom.x] == 1)
	{

	} else
	{
		player_->SetIsOnGround(false);
	}

	Vector2Int right =
	{
		static_cast<int>(center.x + radius.x + velocity.x) / kBlockSize,
		static_cast<int>(center.y) / kBlockSize
	};
	//横の判定
	if (map[right.y][right.x] == 1)
	{
		velocity.x = 0.0f;
		player_->SetVelocity(velocity);
	}

#ifdef _DEBUG
	ImGui::Begin("map");
	ImGui::DragFloat2("origin", &origin.x);
	ImGui::Text("leftTop:%d", map[leftTop.y][leftTop.x]);
	ImGui::Text("rightTop:%d", map[rightTop.y][rightTop.x]);
	ImGui::Text("leftBottom:%d", map[leftBottom.y][leftBottom.x]);
	ImGui::Text("rightBottom:%d", map[rightBottom.y][rightBottom.x]);
	ImGui::DragFloat2("newCenter", &newCenter.x);
#endif // _DEBUG


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

	/*Vector2Int leftTop = { static_cast<int>(center.x - radius.x) / kBlockSize, static_cast<int>(center.y - radius.y) / kBlockSize };

	bool isHit = false;
	if (map[leftTop.y][leftTop.x] == 1)
	{
		isHit = true;
		player_->SetPosition({ center.x,player_->GetPlayerData().pos.y });
	}*/
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

	//if (map[rightBottom.y][rightBottom.x] == 1 || map[leftBottom.y][leftBottom.x] == 1)
	//{
	//	player_->SetIsOnGround(false);
	//	//player_->SetPosition({ player_->GetPlayerData().pos.x,center.y - radius.y });
	//}
	//else
	//{
	//	player_->SetIsOnGround(true);
	//}

	/*ImGui::Begin("map");
	ImGui::DragFloat2("center", &center.x);
	ImGui::DragFloat2("radius", &radius.x);
	ImGui::DragInt2("leftBottom", &leftBottom.x);
	ImGui::DragInt2("rightBottom", &rightBottom.x);
	ImGui::Text("mapLeftTop:%d", map[leftTop.y][leftTop.x]);
	ImGui::Text("mapLeftBottom:%d", map[leftBottom.y][leftBottom.x]);
	ImGui::Text("mapRightBottom:%d", map[rightBottom.y][rightBottom.x]);
	ImGui::Checkbox("isHit", &isHit);
	ImGui::End();*/
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
			} else if (map[y][x] == 2)
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
			} else if (map[y][x] == 0)
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
