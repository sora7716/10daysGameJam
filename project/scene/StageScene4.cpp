#include "StageScene4.h"
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


void StageScene4::Initialize(char* keys, char* preKeys, Vector2Int* mousePos)
{
	mousePos_ = mousePos;
	player = new Player();
	collision = new Collision();
	collision->SetPlayer(player);

	//背景
	bgTex_ = Novice::LoadTexture("./resources/stageBackGround.png");

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
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_1_stage4", "up4_1", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_2_stage4", "up4_2", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_3_stage4", "up4_3", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_4_stage4", "up4_4", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_5_stage4", "up4_5", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_6_stage4", "up4_6", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/up_7_stage4", "up4_7", blockTextures[static_cast<int>(TileTex::kUpper)]);

	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_1_stage4", "under4_1", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_2_stage4", "under4_2", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_3_stage4", "under4_3", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_4_stage4", "under4_4", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_5_stage4", "under4_5", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_6_stage4", "under4_6", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/stage4/under_7_stage4", "under4_7", blockTextures[static_cast<int>(TileTex::kUnder)]);

	//マップの生成
	map = new Map();
	map->Initialize(mousePos, player);
	Chunk* upperChunk1 = ChunkManager::GetInstance()->FindChunk("up4_1");
	Chunk* upperChunk2 = ChunkManager::GetInstance()->FindChunk("up4_2");
	Chunk* upperChunk3 = ChunkManager::GetInstance()->FindChunk("up4_3");
	Chunk* upperChunk4 = ChunkManager::GetInstance()->FindChunk("up4_4");
	Chunk* upperChunk5 = ChunkManager::GetInstance()->FindChunk("up4_5");
	Chunk* upperChunk6 = ChunkManager::GetInstance()->FindChunk("up4_6");
	Chunk* upperChunk7 = ChunkManager::GetInstance()->FindChunk("up4_7");
	Chunk* underChunk1 = ChunkManager::GetInstance()->FindChunk("under4_1");
	Chunk* underChunk2 = ChunkManager::GetInstance()->FindChunk("under4_2");
	Chunk* underChunk3 = ChunkManager::GetInstance()->FindChunk("under4_3");
	Chunk* underChunk4 = ChunkManager::GetInstance()->FindChunk("under4_4");
	Chunk* underChunk5 = ChunkManager::GetInstance()->FindChunk("under4_5");
	Chunk* underChunk6 = ChunkManager::GetInstance()->FindChunk("under4_6");
	Chunk* underChunk7 = ChunkManager::GetInstance()->FindChunk("under4_7");

	map->CreateTowLineMap(upperChunk1, underChunk1, { 3,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk2, underChunk2, { 8,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk3, underChunk3, { 13,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk4, underChunk4, { 18,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk5, underChunk5, { 23,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk6, underChunk6, { 28,3 }, switchTextures, true);
	map->CreateTowLineMap(upperChunk7, underChunk7, { 33,3 }, switchTextures, true);
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

void StageScene4::Update()
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

	player->SetIsMove(startSwitch->IsPressSwitch());

	collision->IsMapChipCollision();

	if (resetSwitch->IsPressSwitch())
	{
		player->SetIsReset(true);
		startSwitch->SetIsPressSwitch(false);
		resetSwitch->SetIsPressSwitch(false);
		isPressStart_ = false;
	}

	if (goal->IsCollision())
	{
		isFinised_ = true;
		nextScene_ = kSelect;
	}

	goal->SetTargetPos(player->GetPlayerData().gameObject.center);
	goal->Update();
}

void StageScene4::Draw()
{
	Novice::DrawSprite(0, 0, bgTex_, 1.0f, 1.0f, 0.0f, WHITE);
	map->Draw();
	goal->Draw();
	player->Draw();
	startSwitch->DrawRect();
	resetSwitch->DrawRect();
}

StageScene4::~StageScene4()
{
	delete player;
	delete map;
	delete startSwitch;
	delete resetSwitch;
	delete collision;
}
