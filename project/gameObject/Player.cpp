#include "Player.h"
#include"Novice.h"
#include "Collision.h"
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

float boxPosX[2] = { 250.0f,750.0f };
float boxPosY[2] = { 550.0f,350.0f };
float boxSide[2] = { 100.0f,300.0f };

void Player::Initialize(char* keys, char* preKeys)//初期化
{
	keys_ = keys;
	preKeys_ = preKeys;
	playerData_.pos = { 0.0f,352.0f };
	Vector2 radius = { playerData_.width / 2.0f,playerData_.height / 2.0f };
	center_ = playerData_.pos + radius;
	playerData_.height = 32.0f;
	playerData_.width = 32.0f;
	playerData_.acceleration.y = 0.8f;
}

void Player::Update()
{
	CheackMapChipPosition();

	//playerData_.pos.x += playerData_.velocity.x;//プレイヤー前進前スピード

	playerData_.velocity += playerData_.acceleration;//速度に加速度を足す
	playerData_.pos += playerData_.velocity;//位置に速度を足す

	if (keys_[DIK_SPACE] && preKeys_[DIK_SPACE])
	{
		if (!isOnGround_)
		{
			isOnGround_ = true;
			playerData_.velocity.y = -10.0f;
		}
	}

	if (!isOnGround_) 
	{
		playerData_.velocity.y = 0.0f;
		playerData_.acceleration.y = 0.0f;
		playerData_.pos.y = center_.y - (playerData_.height / 2.0f);
	}
	else 
	{
		playerData_.acceleration.y = 0.8f;
	}

	if (keys_[DIK_D])
	{
		playerData_.velocity.x = 5.0f;
	}
	else if (keys_[DIK_A])
	{
		playerData_.velocity.x = -5.0f;
	}
	else
	{
		playerData_.velocity.x = 0.0f;
	}

#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::DragFloat2("position", &playerData_.pos.x, 0.1f);
	ImGui::Checkbox("isJump", &isOnGround_);
	ImGui::DragInt2("leftBottomNum", &playerData_.leftBottom.x);
	ImGui::DragInt2("rightBottomNum", &playerData_.rightBottom.x);
	ImGui::End();
#endif // _DEBUG

	//if (keys_[DIK_SPACE])//プレイヤー前進
	//{
	//	isMove = true;
	//}

	//if (isMove)//プレイヤー前進後スピード
	//{
	//	playerData_.velocity.x = 5.0f;
	//} else
	//{
	//	playerData_.velocity.x = 0.0f;
	//}



	/*if (isMove)
	{*/

	//if (playerData_.velocity.x <= 0.0f)//ジャンプキー
	//{
	//	if (!isJump)
	//	{
	//		isJump = true;
	//		playerData_.velocity.x = -15.0f;
	//	}

	//}


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
	Novice::DrawBox(static_cast<int>(playerData_.pos.x),
		static_cast<int>(playerData_.pos.y),
		static_cast<int>(playerData_.width),
		static_cast<int>(playerData_.height),
		0.0f, RED, kFillModeSolid);





	
}

void Player::SetLeftTop(const Vector2Int& leftTop)
{
	playerData_.leftTop = leftTop;
}

void Player::SetLeftBottom(const Vector2Int& leftBottom)
{
	playerData_.leftBottom = leftBottom;

}

void Player::SetRightTop(const Vector2Int& rightTop)
{
	playerData_.rightTop = rightTop;
}

void Player::SetRightBottom(const Vector2Int& rightBottom)
{
	playerData_.rightBottom = rightBottom;
}

void Player::SetPosition(const Vector2& pos)
{
	playerData_.pos = pos;
}

void Player::SetVelocity(const Vector2& velocity)
{
	playerData_.velocity = velocity;
}

void Player::CheackMapChipPosition()
{
	// プレイヤーの下のチップ座標を計算

	// 右上
	playerData_.rightTop.x = static_cast<int>(playerData_.pos.x + playerData_.width - 1.0f) / kBlockSize;
	playerData_.rightTop.y = static_cast<int>(playerData_.pos.y) / kBlockSize;

	// 右下
	playerData_.rightBottom.x = static_cast<int>(playerData_.pos.x + playerData_.width - 1.0f) / kBlockSize;
	playerData_.rightBottom.y = static_cast<int>(playerData_.pos.y + playerData_.height - 1.0f) / kBlockSize;

	// 左上
	playerData_.leftTop.x = static_cast<int>(playerData_.pos.x) / kBlockSize;
	playerData_.leftTop.y = static_cast<int>(playerData_.pos.y) / kBlockSize;

	// 左下
	playerData_.leftBottom.x = static_cast<int>(playerData_.pos.x) / kBlockSize;
	playerData_.leftBottom.y = static_cast<int>(playerData_.pos.y + playerData_.height - 1.0f) / kBlockSize;

	
}



