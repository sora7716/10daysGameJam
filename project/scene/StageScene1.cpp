#include "StageScene1.h"
#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <cmath>
#include <vector>
#include "calc/Collision.h"
#include"gameObject/Player.h"
#include "gameObject/Map.h"
#include "gameObject/ChunkManager.h"
#include "gameObject/GameSwitch.h"
#include "gameObject/Goal.h"

void StageScene1::Initialize(char* keys, char* preKeys, Vector2Int* mousePos)
{
	mousePos_ = mousePos;
	player = new Player();
	collision = new Collision();
	collision->SetPlayer(player);

	//背景
	bgTex_= Novice::LoadTexture("./resources/stageBackGround.png");


	//ブロックテクスチャの読み込み
	int blockTextures[static_cast<int>(TileTex::kCount)] =
	{
		Novice::LoadTexture("./resources/upperTile.png"),
		Novice::LoadTexture("./resources/underTile.png")
	};

	//ボタンのテクスチャ
	int switchTextures[static_cast<int>(SwitchTex::kCount)]
	{
		Novice::LoadTexture("./resources/transitionSwitch.png"),
		Novice::LoadTexture("./resources/invertSwitch.png"),
		Novice::LoadTexture("./resources/startSwitch.png"),
		Novice::LoadTexture("./resources/resetSwitch.png"),
	};

	int playerTextures[static_cast<int>(PlayerState::kCount)] =
	{ Novice::LoadTexture("./resources/player.png"),
		Novice::LoadTexture("./resources/playerWork.png"),
		Novice::LoadTexture("./resources/playerJump.png"),
	};
	//チャンクの生成
	/*ChunkManager::GetInstance()->LoadChunk("map/up_0-1", "up_0-1", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-2", "up_0-2", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-3", "up_0-3", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-4", "up_0-4", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-5", "up_0-5", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-6", "up_0-6", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-7", "up_0-7", blockTextures[static_cast<int>(TileTex::kUpper)]);*/

	ChunkManager::GetInstance()->LoadChunk("map/stage1/under_1_stage1", "under1_1", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage1/under_2_stage1", "under1_2", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage1/under_3_stage1", "under1_3", blockTextures[static_cast<int>(TileTex::kUnder)]);
	/*ChunkManager::GetInstance()->LoadChunk("map/under_0-4", "under_0-4", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-5", "under_0-5", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-6", "under_0-6", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-7", "under_0-7", blockTextures[static_cast<int>(TileTex::kUnder)]);*/

	//マップの生成
	map = new Map();
	map->Initialize(mousePos, player);
	/*Chunk* upperChunk1 = ChunkManager::GetInstance()->FindChunk("up_0-1");
	Chunk* upperChunk2 = ChunkManager::GetInstance()->FindChunk("up_0-2");
	Chunk* upperChunk3 = ChunkManager::GetInstance()->FindChunk("up_0-3");
	Chunk* upperChunk4 = ChunkManager::GetInstance()->FindChunk("up_0-4");
	Chunk* upperChunk5 = ChunkManager::GetInstance()->FindChunk("up_0-5");
	Chunk* upperChunk6 = ChunkManager::GetInstance()->FindChunk("up_0-6");
	Chunk* upperChunk7 = ChunkManager::GetInstance()->FindChunk("up_0-7");*/
	Chunk* underChunk1 = ChunkManager::GetInstance()->FindChunk("under1_1");
	Chunk* underChunk2 = ChunkManager::GetInstance()->FindChunk("under1_2");
	Chunk* underChunk3 = ChunkManager::GetInstance()->FindChunk("under1_3");
	/*Chunk* underChunk4 = ChunkManager::GetInstance()->FindChunk("under_0-4");
	Chunk* underChunk5 = ChunkManager::GetInstance()->FindChunk("under_0-5");
	Chunk* underChunk6 = ChunkManager::GetInstance()->FindChunk("under_0-6");
	Chunk* underChunk7 = ChunkManager::GetInstance()->FindChunk("under_0-7");*/

	map->CreateOneLineMap(underChunk1, { 13,9 }, switchTextures[static_cast<int>(SwitchTex::kInvert)], true);
	map->CreateOneLineMap(underChunk2, { 18,9 }, switchTextures[static_cast<int>(SwitchTex::kInvert)], true);
	map->CreateOneLineMap(underChunk3, { 23,9 }, switchTextures[static_cast<int>(SwitchTex::kInvert)], true);
	/*map->CreateTowLineMap(upperChunk1, underChunk1, { 3,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk2, underChunk2, { 8,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk3, underChunk3, { 13,3 }, switchTextures, true);*/
	/*map->CreateTowLineMap(upperChunk4, underChunk4, { 18,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk5, underChunk5, { 23,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk6, underChunk6, { 28,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk7, underChunk7, { 33,3 }, switchTextures, true);*/
	map->SettingUnderBorderLine();
	player->Initialize(keys, preKeys, map->GetMap(), playerTextures);

	Vector2 startSwitchOrigin = { 30.0f, 550.0f };
	Vector2 startSwitchSize{ 256.0f,128.0f };

	startSwitch = new GameSwitch();
	startSwitch->Initialize(startSwitchOrigin, startSwitchSize, switchTextures[static_cast<int>(SwitchTex::kStart)]);

	Vector2 resetSwitchOrigin = { 326.0f, 550.0f };
	Vector2 resetSwitchSize{ 256.0f,128.0f };

	resetSwitch = new GameSwitch();
	resetSwitch->Initialize(resetSwitchOrigin, resetSwitchSize, switchTextures[static_cast<int>(SwitchTex::kReset)]);


	isFinised_ = false;
	nextScene_ = kNone;
	isPressStart_ = false;

	goal = new Goal();
	int goalTexture = Novice::LoadTexture("./resources/goal.png");
	goal->Initialize(map->GetMap(), goalTexture);
}

void StageScene1::Update()
{

	collision->SetMap(map->GetMap());
	map->Update();
	player->Update();



	if (!isPressStart_)
	{
		isPressStart_ = startSwitch->IsPressSwitch();
		startSwitch->SetMousePos(*mousePos_);
		startSwitch->Update();
	}
	resetSwitch->SetMousePos(*mousePos_);
	resetSwitch->Update();

	if (goal->IsCollision())
	{
		isFinised_ = true;
		nextScene_ = kSelect;
	}

	player->SetIsMove(startSwitch->IsPressSwitch());

	collision->IsMapChipCollision();

	if (resetSwitch->IsPressSwitch())
	{
		player->SetIsReset(true);
		startSwitch->SetIsPressSwitch(false);
		resetSwitch->SetIsPressSwitch(false);
		isPressStart_ = false;
	}

	goal->SetTargetPos(player->GetPlayerData().gameObject.center);
	goal->Update();
}

void StageScene1::Draw()
{

	Novice::DrawSprite(0, 0, bgTex_, 1.0f, 1.0f, 0.0f, WHITE);
	map->Draw();
	goal->Draw();
	player->Draw();

	/*for (int i = 0; i < 6; i++)
	{
		Novice::DrawLine(line1.startPos.x + (i * 32 * 5),
			line1.startPos.y,
			line1.endPos.x + (i * 32 * 5),
			line1.endPos.y,
			RED);
	}*/

	startSwitch->DrawRect();
	resetSwitch->DrawRect();


}

StageScene1::~StageScene1()
{
	delete player;
	delete map;
	delete startSwitch;
	delete resetSwitch;
	delete collision;
}
