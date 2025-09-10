#include "SelectScene.h"
#include "gameObject/ResourceData.h"
#include "Novice.h"
#include "gameObject/GameSwitch.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG


void SelectScene::Initialize(Vector2Int* mousePos)
{
	mousePos_ = mousePos;
	isFinished_ = false;
	nextScene_ = kNone;

	bgTex_[0] = Novice::LoadTexture("./resources/selectBackGround.png");
	bgTex_[1] = Novice::LoadTexture("./resources/selectBelt.png");
	bgTex_[2] = Novice::LoadTexture("./resources/selectFrame.png");
	switchTex = Novice::LoadTexture("./resources/selectPoint.png");

	stageMoji_[0] = Novice::LoadTexture("./resources/selectStage1Text.png");
	stageMoji_[1] = Novice::LoadTexture("./resources/selectStage2Text.png");
	stageMoji_[2] = Novice::LoadTexture("./resources/selectStage3Text.png");

	stageTitleName = stageMoji_[0];

	for (int i = 1; i < 5; i++)
	{
		gameSwitch_[i - 1] = new GameSwitch();
		gameSwitchPos_[i - 1] = { 250.0f * i,550.0f };
		gameSwitch_[i - 1]->Initialize(gameSwitchPos_[i - 1], { 32.0f,32.0f }, switchTex);
	}

}

void SelectScene::Update()
{
	for (int i = 0; i < 4; i++) 
	{
		gameSwitch_[i]->SetMousePos(*mousePos_);
		gameSwitch_[i]->Update();
	}

	if (gameSwitch_[0]->IsCross()) 
	{
		stageTitleName = stageMoji_[0];
	}
	else if (gameSwitch_[1]->IsCross())
	{
		stageTitleName = stageMoji_[1];
	}
	else if (gameSwitch_[2]->IsCross())
	{
		stageTitleName = stageMoji_[2];
	}
	else if (gameSwitch_[3]->IsCross())
	{
		stageTitleName = stageMoji_[3];
	}

	if (gameSwitch_[0]->IsPressSwitch())
	{
		isFinished_ = true;
		nextScene_ =kStage1;
	}
	else if (gameSwitch_[1]->IsPressSwitch())
	{
		isFinished_ = true;
		nextScene_ = kStage2;
	}
	else if (gameSwitch_[2]->IsPressSwitch())
	{
		isFinished_ = true;
		nextScene_ = kStage3;
	}
	else if (gameSwitch_[3]->IsPressSwitch())
	{
		isFinished_ = true;
		nextScene_ = kStage4;
	}


#ifdef _DEBUG
	ImGui::Begin("stageName");
	ImGui::DragFloat2("translate", &stageNamePos.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

}

void SelectScene::Draw()
{
	for (int i = 0; i < 5; i++) 
	{
		Novice::DrawSprite(0, 0, bgTex_[i], 1.0f, 1.0f, 0.0f, WHITE);
	}

	for (int i = 0; i < 4; i++)
	{
		gameSwitch_[i]->Draw();
	}

	Novice::DrawSprite
	(
		static_cast<int>(stageNamePos.x),
		static_cast<int>(stageNamePos.y),
		stageTitleName,
		1.0f, 1.0f, 0.0f, WHITE
	);

}