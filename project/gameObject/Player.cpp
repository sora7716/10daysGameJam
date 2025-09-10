#include "Player.h"
#include"Novice.h"
#include "calc/Collision.h"
#ifdef _DEBUG
#include <imgui.h>
#include "GameSwitch.h"
#endif // _DEBUG

//初期化
void Player::Initialize(char* keys, char* preKeys, std::vector<std::vector<int>>map, int* textureHandles)
{
	//キーの受け取り
	keys_ = keys;
	preKeys_ = preKeys;

	//プレイヤーデータの初期化
	playerData_.gameObject.size = { 32.0f,32.0f };
	playerData_.gameObject.radius = playerData_.gameObject.size / 2.0f;
	playerData_.gameObject.acceleration = { 0.0f,0.8f };
	for (int i = 0; i < static_cast<int>(PlayerState::kCount); i++) {
		playerData_.textureHandles[i] = textureHandles[i];
	}

	//プレイヤーの位置を探索
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == static_cast<int>(BlockType::kPlayer))
			{
				playerData_.gameObject.center =
				{
					static_cast<float>(x * kBlockSize) - playerData_.gameObject.radius.x,
					static_cast<float>(y * kBlockSize) - playerData_.gameObject.radius.y,
				};
				playerData_.beginPos = playerData_.gameObject.center;//初期値を設定
			}
		}
	}

}

//更新
void Player::Update()
{
	playerData_.time++;

	//マップチップ番号の取得
	CheckMapChipIndex();

	playerData_.gameObject.velocity += playerData_.gameObject.acceleration;//速度に加速度を足す
	playerData_.gameObject.center += playerData_.gameObject.velocity;//位置に速度を足す

	//スペースを押したら移動開始
	if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE])
	{
		isMove_ = true;
	}

	//ジャンプできるかどうか
	if (isJump_ && isOnGround_)
	{
		isOnGround_ = false;//地面から離れる
		playerData_.gameObject.velocity.y = -8.0f;//ジャンプ力を設定
		isJump_ = false;//ジャンプフラグをfalse
	}

	//下に行き過ぎないように
	if (playerData_.gameObject.center.y > 600.0f)
	{
		playerData_.gameObject.center.y = 600.0f;//Y軸の位置を固定
		isOnGround_ = true;//地面にくっつく
		isMove_ = false;//移動を止める
		playerData_.gameObject.velocity = {};//速度を0にする
		isReset_ = true;//リセットする
	}

	//地面にいるかどうか
	if (isOnGround_)
	{
		//速度を0にする　
		playerData_.gameObject.velocity.y = 0.0f;
		//加速度を0にする
		playerData_.gameObject.acceleration.y = 0.0f;
	}
	else
	{
		//加速度を元に戻す
		playerData_.gameObject.acceleration.y = 0.8f;
	}

	//移動するかどうか
	if (isMove_)
	{
		//速度を設定
		playerData_.gameObject.velocity.x = 2.0f;
		if (!isJump_) {
			playerTexIndex = static_cast<int>(PlayerState::kWork);
		}
		else
		{
			playerTexIndex = static_cast<int>(PlayerState::kJump);
		}
	}
	else
	{
		playerTexIndex = static_cast<int>(PlayerState::kIdol);
	}

	//アニメーションの処理
	if (playerData_.uvPos.x <= 128 - kBlockSize)
	{

		playerData_.frameCount = (playerData_.time / 4) % 4;
		playerData_.uvPos.x = 32 * playerData_.frameCount;

	}

	//リセット
	if (isReset_) {
		playerData_.gameObject.center = playerData_.beginPos;//初期値に戻す
		playerData_.gameObject.velocity = {};
		playerData_.gameObject.acceleration = {};
		isMove_ = false;
		isReset_ = false;
	}

#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::DragFloat2("position", &playerData_.gameObject.center.x, 0.1f);
	ImGui::Checkbox("isOnGround", &isOnGround_);
	ImGui::Checkbox("isJump", &isJump_);
	ImGui::DragInt2("leftTop", &playerData_.leftTop.x);
	ImGui::DragInt2("rightTop", &playerData_.leftTop.x);
	ImGui::DragInt2("leftBottom", &playerData_.leftBottom.x);
	ImGui::DragInt2("rightBottom", &playerData_.rightBottom.x);
	ImGui::End();
#endif // _DEBUG

}

//描画
void Player::Draw()
{
	Novice::DrawSpriteRect(
		static_cast<int>(playerData_.gameObject.center.x - playerData_.gameObject.radius.x),
		static_cast<int>(playerData_.gameObject.center.y - playerData_.gameObject.radius.y),
		playerData_.uvPos.x,
		playerData_.uvPos.y,
		kBlockSize, kBlockSize,
		playerData_.textureHandles[playerTexIndex],
		(static_cast<float>(kBlockSize) / static_cast<float>(kBlockSize * 4)), 1.0f,
		0.0f,
		WHITE
	);
}

//マップチップ番号を検索
void Player::CheckMapChipIndex()
{
	// プレイヤーの下のチップ座標を計算
	//左上
	playerData_.leftTop =
	{
		static_cast<int>(playerData_.gameObject.center.x - playerData_.gameObject.radius.x) / kBlockSize,
		static_cast<int>(playerData_.gameObject.center.y - playerData_.gameObject.radius.y) / kBlockSize
	};
	//右上
	playerData_.rightTop =
	{
		static_cast<int>(playerData_.gameObject.center.x + playerData_.gameObject.radius.x - 1.0f) / kBlockSize,
		static_cast<int>(playerData_.gameObject.center.y - playerData_.gameObject.radius.y - 1.0f) / kBlockSize
	};
	//左下
	playerData_.leftBottom =
	{
		static_cast<int>(playerData_.gameObject.center.x - playerData_.gameObject.radius.x) / kBlockSize,
		static_cast<int>(playerData_.gameObject.center.y + playerData_.gameObject.radius.y) / kBlockSize
	};
	//右下
	playerData_.rightBottom =
	{
		static_cast<int>(playerData_.gameObject.center.x + playerData_.gameObject.radius.x - 1.0f) / kBlockSize,
		static_cast<int>(playerData_.gameObject.center.y + playerData_.gameObject.radius.y - 1.0f) / kBlockSize
	};
}



