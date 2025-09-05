#include "Player.h"
#include"Novice.h"

float boxPosX[2] = { 250.0f,750.0f };
float boxPosY[2] = { 550.0f,350.0f };
float boxSide[2] = { 100.0f,300.0f };

void Player::Initialize(char* keys, char* preKeys)//初期化
{
	keys_ = keys;
	preKeys_ = preKeys;
	pos_ = { 60.0f,600.0f };
	acceleration_.y = 0.8f;
}




void Player::Update()
{


	pos_.x += Velocity_.x;//プレイヤー前進前スピード


	if (keys_[DIK_SPACE])//プレイヤー前進
	{
		Move = true;
	}

	if (Move)//プレイヤー前進後スピード
	{
		Velocity_.x = 5.0f;
	}
	else
	{
		Velocity_.x = 0.0f;
	}
	if (pos_.x + radius >= 1280)//右側壁判定
	{
		Move = false;
		pos_.x = 1280 - radius;
	}

	if (Move)
	{

		if (pos_.x + radius == boxPosX[0] && pos_.y + radius > boxPosY[0])//BOX1の当たり判定
		{
			Velocity_.x = 0.0f;
		}
		else if (pos_.x + radius != boxPosX[0] || pos_.y + radius < boxPosY[0])
		{
			Velocity_.x = 5.0f;
		}

		if (pos_.x + radius == boxPosX[1] && pos_.y + radius > boxPosY[1])//BOX2の当たり判定
		{
			Velocity_.x = 0.0f;
		}
		else if (pos_.x + radius != boxPosX[1] || pos_.y + radius < boxPosY[1])
		{
			Velocity_.x = 5.0f;
		}

		if (Velocity_.x <= 0.0f && !jamp)//ジャンプキー
		{

			jamp = true;
			Velocity_.y = -15.0f;

		}

		pos_.y += Velocity_.y;//位置に速度を足す
		Velocity_.y += acceleration_.y;//速度に加速度を足す



		if (pos_.y > 600.0f)//着地したかどうか
		{
			jamp = false;
			pos_.y = 600.0f;
		}

		if (!dead)//死亡条件
		{


			if (Velocity_.x <= 0.0f && pos_.x <= 1000)//移動が止まり、ゴールまでたどり着いてなければ
			{
				deadTimer = true;
			}
			else
			{
				timer = 0.0f;
				deadTimer = false;
			}
			if (deadTimer)//死亡までのカウントダウン
			{
				timer += 1.0f;

				if (timer >= 300.0f)//カウントダウンが溜まったら
				{
					dead = true;
				}
			}

		}



	}
	if (dead)//死亡後の処理
	{
		Velocity_ = { 0.0f , 0.0f };
		deadTimer = false;
		Move = false;
		jamp = false;
		timer -= 1.0f;

		if (timer <= 0.0f)
		{
			timer = 0.0f;
			pos_ = { 60.0f,600.0f };
			dead = false;
		}
	}
}
void Player::Draw()
{
	if (!dead)//生きていたら表示
	{
		Novice::DrawEllipse(
			static_cast<int>(pos_.x), //円のX座標
			static_cast<int>(pos_.y), //円のY座標
			static_cast<int>(radius), static_cast<int>(radius), //円の半径X方向,Y方向
			0.0f, //円の角度
			WHITE, //円の色
			kFillModeSolid //塗りつぶすか否か
		);
	}
	else//死亡したら表示
	{
		Novice::DrawEllipse(
			static_cast<int>(pos_.x), //円のX座標
			static_cast<int>(pos_.y), //円のY座標
			static_cast<int>(radius), static_cast<int>(radius), //円の半径X方向,Y方向
			0.0f, //円の角度
			BLACK, //円の色
			kFillModeSolid);//塗りつぶすか否か
	}

	
	
		Novice::DrawBox(static_cast<int>(boxPosX[1]), static_cast<int>(boxPosY[1]), static_cast<int>(boxSide[1]), static_cast<int>(boxSide[1]), 0.0f, RED, kFillModeSolid);//仮ブロック
	

	Novice::ScreenPrintf(100, 100, "timer = %f", timer);
}



