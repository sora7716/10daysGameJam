#include "Player.h"
#include"Novice.h"
#include "calc/Collision.h"
#ifdef _DEBUG
#include <imgui.h>
#include "ChunkChangeSwitch.h"
#endif // _DEBUG

//初期化
void Player::Initialize(char* keys, char* preKeys, std::vector<std::vector<int>>map, int textureHandle)
{
	//キーの受け取り
	keys_ = keys;
	preKeys_ = preKeys;

	//プレイヤーデータの初期化
	playerData_.gameObject.size = { 32.0f,32.0f };
	playerData_.gameObject.radius = playerData_.gameObject.size / 2.0f;
	playerData_.gameObject.acceleration = { 0.0f,0.8f };
	playerData_.textureHandle = textureHandle;

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
			}
		}
	}

}

//更新
void Player::Update()
{
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
	}

	//地面にいるかどうか
	if (isOnGround_)
	{
		//速度を0にする　
		playerData_.gameObject.velocity.y = 0.0f;
		//加速度を0にする
		playerData_.gameObject.acceleration.y = 0.0f;
	} else
	{
		//加速度を元に戻す
		playerData_.gameObject.acceleration.y = 0.8f;
	}

	//移動するかどうか
	if (isMove_)
	{
		//速度を設定
		playerData_.gameObject.velocity.x = 2.0f;
	}

#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::DragFloat2("position", &playerData_.gameObject.center.x, 0.1f);
	ImGui::Checkbox("isOnGround", &isOnGround_);
	ImGui::DragInt2("leftTop", &playerData_.leftTop.x);
	ImGui::DragInt2("rightTop", &playerData_.leftTop.x);
	ImGui::DragInt2("leftBottom", &playerData_.leftBottom.x);
	ImGui::DragInt2("rightBottom", &playerData_.rightBottom.x);
	ImGui::End();
#endif // _DEBUG

	//if (!dead)//死亡条件
	//{


	//	if (playerData_.pos.x <= 0.0f && playerData_.pos.x <= 1000)//移動が止まり、ゴールまでたどり着いてなければ
	//	{
	//		deadTimer = true;
	//	}
	//	else
	//	{
	//		timer = 0.0f;
	//		deadTimer = false;
	//	}
	//	if (deadTimer)//死亡までのカウントダウン
	//	{
	//		timer += 1.0f;

	//		if (timer >= 300.0f)//カウントダウンが溜まったら
	//		{
	//			dead = true;
	//		}
	//	}

	//}



//}
//if (dead)//死亡後の処理
//{
//	playerData_.velocity = { 0.0f , 0.0f };
//	deadTimer = false;
//	Move = false;
//	jamp = false;
//	timer -= 1.0f;

//	if (timer <= 0.0f)
//	{
//		timer = 0.0f;
//		playerData_.pos = { 60.0f,600.0f };
//		dead = false;
//	}
//}
}

//描画
void Player::Draw()
{
	//if (!dead)//生きていたら表示
	//{
	//	Novice::DrawBox(
	//		static_cast<int>(playerData_.pos.x), //円のX座標
	//		static_cast<int>(playerData_.pos.y), //円のY座標
	//		static_cast<int>(playerData_.width), static_cast<int>(playerData_.height), //円の半径X方向,Y方向
	//		0.0f, //円の角度
	//		WHITE, //円の色
	//		kFillModeSolid //塗りつぶすか否か
	//	);
	//}
	//else//死亡したら表示
	//{
	//	Novice::DrawBox(
	//		static_cast<int>(playerData_.pos.x), //円のX座標
	//		static_cast<int>(playerData_.pos.y), //円のY座標
	//		static_cast<int>(playerData_.width), static_cast<int>(playerData_.height), //円の半径X方向,Y方向
	//		0.0f, //円の角度
	//		BLACK, //円の色
	//		kFillModeSolid);//塗りつぶすか否か
	//}

	/*Novice::DrawBox
	(
		static_cast<int>(playerData_.gameObject.center.x - playerData_.gameObject.radius.x),
		static_cast<int>(playerData_.gameObject.center.y - playerData_.gameObject.radius.y),
		static_cast<int>(playerData_.gameObject.size.x),
		static_cast<int>(playerData_.gameObject.size.y),
		0.0f, BLUE, kFillModeSolid
	);*/

	Novice::DrawSprite(
		static_cast<int>(playerData_.gameObject.center.x - playerData_.gameObject.radius.x),
		static_cast<int>(playerData_.gameObject.center.y - playerData_.gameObject.radius.y),
		playerData_.textureHandle,
		1.0f, 1.0f, 0.0f, WHITE
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



