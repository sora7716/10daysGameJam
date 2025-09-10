#include "TitleScene.h"
#include "gameObject/ResourceData.h"
#include "Novice.h"

void TitleScene::Initialize(Vector2Int*mousePos)
{
	mousePos_ = mousePos;
	isFinised_ = false;
	nextScene_ = kNone;
}

void TitleScene::Update()
{
	if (Novice::IsTriggerMouse(0))
	{
		isFinised_ = true;
		nextScene_ = kSelect;
	}
}

void TitleScene::Draw()
{
	Novice::ScreenPrintf(0, 0, "TitleScene");
}