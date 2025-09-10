#include "SelectScene.h"
#include "gameObject/ResourceData.h"
#include "Novice.h"
void SelectScene::Initialize(Vector2Int* mousePos)
{
	mousePos_ = mousePos;
	isFinished_ = false;
	nextScene_ = kNone;

	bgTex_[0] = Novice::LoadTexture("./resources/selectBackGround.png");
	bgTex_[1] = Novice::LoadTexture("./resources/selectBelt.png");
	bgTex_[2] = Novice::LoadTexture("./resources/selectFrame.png");
	bgTex_[3] = Novice::LoadTexture("./resources/selectUIStartObi.png");
	bgTex_[4] = Novice::LoadTexture("./resources/selectUIStartText.png");
}

void SelectScene::Update()
{
	if (Novice::IsTriggerMouse(0))
	{
		isFinished_ = true;
		nextScene_ = kStage1;
	}
}

void SelectScene::Draw()
{
	for (int i = 0; i < 5; i++) {
		Novice::DrawSprite(0, 0, bgTex_[i], 1.0f, 1.0f, 0.0f, WHITE);
	}
}