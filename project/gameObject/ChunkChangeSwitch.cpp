#include "ChunkChangeSwitch.h"
#include "calc/Collision.h"
#include <Novice.h>

//初期化
void ChunkChangeSwitch::Initialize(const Vector2& position)
{
	//座標を受け取る
	position_ = position;
	//サイズを設定
	size_ = { 32.0f,32.0f };
}

//更新
void ChunkChangeSwitch::Update()
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
		color_ = RED;
		//スイッチをクリックしたか
		if (Novice::IsTriggerMouse(0)) 
		{
 			isPressSwitch_ = !isPressSwitch_;
		}
	}
	else
	{
		color_ = BLUE;
	}

	if (isPressSwitch_) 
	{
		color_ = GREEN;
	}
}

//描画
void ChunkChangeSwitch::Draw() 
{
	Novice::DrawBox
	(
		static_cast<int>(position_.x),
		static_cast<int>(position_.y),
		static_cast<int>(size_.x),
		static_cast<int>(size_.y),
		0.0f, color_, kFillModeWireFrame
	);
}