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
	playerData_.gameObject.size = { 32.0f,32.0f };
	playerData_.gameObject.radius = playerData_.gameObject.size / 2.0f;
	playerData_.gameObject.acceleration = { 0.0f,0.8f };
	playerData_.gameObject.center = { playerData_.gameObject.radius.x+64.0f,288.0f + playerData_.gameObject.radius.y };
}

void Player::Update()
{
	CheackMapChipPosition();

	//playerData_.pos.x += playerData_.velocity.x;//プレイヤー前進前スピード

	playerData_.gameObject.velocity += playerData_.gameObject.acceleration;//速度に加速度を足す
	playerData_.gameObject.center += playerData_.gameObject.velocity;//位置に速度を足す


	if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE])
	{
		isMove_ = true;
	}

	if (isJump_&&isOnGround_)
	{
		isOnGround_ = false;
		isJump_ = false;
		playerData_.gameObject.velocity.y = -8.0f;
	}


	/*if (playerData_.gameObject.center.y > 352.0f + playerData_.gameObject.radius.y)
	{
		playerData_.gameObject.center.y = 352.0f + playerData_.gameObject.radius.y;
		isOnGround_ = true;
	}*/

	if (isOnGround_)
	{
		playerData_.gameObject.velocity.y = 0.0f;
		playerData_.gameObject.acceleration.y = 0.0f;
		//playerData_.pos.y = center_.y - (playerData_.height / 2.0f);
	}
	else
	{
		playerData_.gameObject.acceleration.y = 0.8f;
	}

	if (isMove_)
	{
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
	//Novice::DrawBox(static_cast<int>(playerData_.pos.x),
	//	static_cast<int>(playerData_.pos.y),
	//	static_cast<int>(playerData_.width),
	//	static_cast<int>(playerData_.height),
	//	0.0f, RED, kFillModeSolid);

	Novice::DrawBox
	(
		static_cast<int>(playerData_.gameObject.center.x - playerData_.gameObject.radius.x),
		static_cast<int>(playerData_.gameObject.center.y - playerData_.gameObject.radius.y),
		static_cast<int>(playerData_.gameObject.size.x),
		static_cast<int>(playerData_.gameObject.size.y),
		0.0f, BLUE, kFillModeSolid
	);
}

void Player::CheackMapChipPosition()
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

	//// 右上
	//playerData_.rightTop.x = static_cast<int>(playerData_.pos.x + playerData_.width - 1.0f) / kBlockSize;
	//playerData_.rightTop.y = static_cast<int>(playerData_.pos.y) / kBlockSize;

	//// 右下
	//playerData_.rightBottom.x = static_cast<int>(playerData_.pos.x + playerData_.width - 1.0f) / kBlockSize;
	//playerData_.rightBottom.y = static_cast<int>(playerData_.pos.y + playerData_.height - 1.0f) / kBlockSize;

	//// 左上
	//playerData_.leftTop.x = static_cast<int>(playerData_.pos.x) / kBlockSize;
	//playerData_.leftTop.y = static_cast<int>(playerData_.pos.y) / kBlockSize;

	//// 左下
	//playerData_.leftBottom.x = static_cast<int>(playerData_.pos.x) / kBlockSize;
	//playerData_.leftBottom.y = static_cast<int>(playerData_.pos.y + playerData_.height - 1.0f) / kBlockSize;


}



