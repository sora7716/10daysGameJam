#include "GameSwitch.h"
#include "calc/Collision.h"
#include <Novice.h>

//初期化
void GameSwitch::Initialize(const Vector2& position, const Vector2& size, int textureHandle)
{
	//座標を受け取る
	position_ = position;
	//サイズを設定
	size_ = size;
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
			//Novice::PlayAudio(static_cast<int>(soundEffects::kSelect),0,1);
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
		start = 256;
	}
	else
	{
		start = 0;
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

void GameSwitch::DrawRect()
{
	Novice::DrawSpriteRect
	(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		start, 0,
		static_cast<int>(size_.x), static_cast<int>(size_.y),
		textureHandle_, 
		(size_.y/size_.x),1.0f, 0.0f, WHITE
	);
	
}
