#include "SelectScene.h"
#include "gameObject/ResourceData.h"
#include "Novice.h"
void SelectScene::Initialize(Vector2Int* mousePos)
{
	mousePos_ = mousePos;
	isFinised_ = false;
	nextScene_ = kNone;
}

void SelectScene::Update()
{
	if(Novice::IsTriggerMouse(0))
	{
		isFinised_ = true;
		nextScene_ = kStage1;
	}
}

void SelectScene::Draw()
{
	Novice::ScreenPrintf(0, 0, "SelectScene");
}