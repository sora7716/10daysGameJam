#include "GameSwitch.h"
#include "calc/Collision.h"
#include <Novice.h>

//初期化
void GameSwitch::Initialize(const Vector2& position, int textureHandle)
{
	//座標を受け取る
	position_ = position;
	//サイズを設定
	size_ = { 32.0f,32.0f };
	//テクスチャハンドル
	textureHandle_ = textureHandle;
}

//更新
void GameSwitch::Update()
{
	//スイッチの座標でaabbを作成
	AABB aabb =
	{
		.min = position_,
		.max = {position_.x + size_.x,position_.y + size_.y}
	};

	//スイッチに重なったか
	if (Collision::IsPointInRect(aabb, mousePos_)) 
	{
		color_ = WHITE;
		//スイッチをクリックしたか
		if (Novice::IsTriggerMouse(0)) 
		{
 			isPressSwitch_ = !isPressSwitch_;
		}
	}
	else
	{
		color_ = 0xFFFFFF55;
	}

	if (isPressSwitch_) 
	{
		color_ = 0xFDFF81FF;
	}
}

//描画
void GameSwitch::Draw() 
{
	Novice::DrawSprite
	(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		textureHandle_, 1.0f, 1.0f, 0.0f, color_
	);
}