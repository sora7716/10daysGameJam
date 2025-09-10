#include "TitleScene.h"
#include "gameObject/ResourceData.h"
#include "Novice.h"

void TitleScene::Initialize(Vector2Int*mousePos)
{
	mousePos_ = mousePos;
	isFinised_ = false;
	nextScene_ = kNone;

	bgTexs_[0] = Novice::LoadTexture("./resources/titleBackground.png");
	bgTexs_[1] = Novice::LoadTexture("./resources/titleObject.png");
	bgTexs_[2] = Novice::LoadTexture("./resources/titleObi.png");
	bgTexs_[3] = Novice::LoadTexture("./resources/titleText.png");
	bgTexs_[4] = Novice::LoadTexture("./resources/titleLogo.png");
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
	for (int i = 0; i < 5; i++) {
		Novice::DrawSprite(0, 0, bgTexs_[i], 1.0f, 1.0f, 0.0f, WHITE);
	}
}