#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG
#include <cmath>
#include <vector>
#include "calc/Vector2.h"
#include "calc/Collision.h"
#include"gameObject/Player.h"
#include "gameObject/Map.h"
#include "gameObject/ChunkManager.h"
#include "gameObject/GameSwitch.h"
const char kWindowTitle[] = "MyGame";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1312, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2Int mousePos = {};

	Player* player = new Player();
	Collision* collision = new Collision();
	collision->SetPlayer(player);

	/*Line line1;
	line1.startPos = { 160,0 };
	line1.endPos = { 160,416 };*/

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

	int soundEffects[static_cast<int>(soundEffects::kCount)] =
	{
		Novice::LoadAudio("./resources/sound/reset.mp3"),
		Novice::LoadAudio("./resources/sound/jump.mp3"),
		Novice::LoadAudio("./resources/sound/select.mp3"),
		Novice::LoadAudio("./resources/sound/bgm.mp3"),
		Novice::LoadAudio("./resources/sound/goal.mp3"),
		Novice::LoadAudio("./resources/sound/start.mp3"),

	};


	//チャンクの生成
	ChunkManager::GetInstance()->LoadChunk("map/up_0-1", "up_0-1", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-2", "up_0-2", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-3", "up_0-3", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-4", "up_0-4", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-5", "up_0-5", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-6", "up_0-6", blockTextures[static_cast<int>(TileTex::kUpper)]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-7", "up_0-7", blockTextures[static_cast<int>(TileTex::kUpper)]);

	ChunkManager::GetInstance()->LoadChunk("map/under_0-1", "under_0-1", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-2", "under_0-2", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-3", "under_0-3", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-4", "under_0-4", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-5", "under_0-5", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-6", "under_0-6", blockTextures[static_cast<int>(TileTex::kUnder)]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-7", "under_0-7", blockTextures[static_cast<int>(TileTex::kUnder)]);

	//マップの生成
	std::unique_ptr<Map>map = std::make_unique<Map>();
	map->Initialize(&mousePos, player);
	Chunk* upperChunk1 = ChunkManager::GetInstance()->FindChunk("up_0-1");
	Chunk* upperChunk2 = ChunkManager::GetInstance()->FindChunk("up_0-2");
	Chunk* upperChunk3 = ChunkManager::GetInstance()->FindChunk("up_0-3");
	Chunk* upperChunk4 = ChunkManager::GetInstance()->FindChunk("up_0-4");
	Chunk* upperChunk5 = ChunkManager::GetInstance()->FindChunk("up_0-5");
	Chunk* upperChunk6 = ChunkManager::GetInstance()->FindChunk("up_0-6");
	Chunk* upperChunk7 = ChunkManager::GetInstance()->FindChunk("up_0-7");
	Chunk* underChunk1 = ChunkManager::GetInstance()->FindChunk("under_0-1");
	Chunk* underChunk2 = ChunkManager::GetInstance()->FindChunk("under_0-2");
	Chunk* underChunk3 = ChunkManager::GetInstance()->FindChunk("under_0-3");
	Chunk* underChunk4 = ChunkManager::GetInstance()->FindChunk("under_0-4");
	Chunk* underChunk5 = ChunkManager::GetInstance()->FindChunk("under_0-5");
	Chunk* underChunk6 = ChunkManager::GetInstance()->FindChunk("under_0-6");
	Chunk* underChunk7 = ChunkManager::GetInstance()->FindChunk("under_0-7");

	//map->CreateChunkInvertSwitch(underChunk1, { 3,9 }, switchTexture[static_cast<int>(SwitchTex::kInvert)]);
	//map->CreateChunkInvertSwitch(underChunk2, { 8,9 }, switchTexture[static_cast<int>(SwitchTex::kInvert)]);
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
	AABB startSwitchData
	{
		.min = startSwitchOrigin,
		.max = startSwitchOrigin + startSwitchSize,
	};

	std::unique_ptr<GameSwitch> startSwitch = std::make_unique<GameSwitch>();
	startSwitch->Initialize(startSwitchData.min, startSwitchSize, switchTextures[static_cast<int>(SwitchTex::kStart)]);

	Vector2 resetSwitchOrigin = { 326.0f, 550.0f };
	Vector2 resetSwitchSize{ 256.0f,128.0f };
	AABB resetSwitchData
	{
		.min = resetSwitchOrigin,
		.max = resetSwitchOrigin + resetSwitchSize,
	};

	std::unique_ptr<GameSwitch> resetSwitch = std::make_unique<GameSwitch>();
	resetSwitch->Initialize(resetSwitchData.min, resetSwitchSize, switchTextures[static_cast<int>(SwitchTex::kReset)]);
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetMousePosition(&mousePos.x, &mousePos.y);

		///
		/// ↓更新処理ここから
		///
		collision->SetMap(map->GetMap());
		map->Update();
		player->Update();
		startSwitch->SetMousePos(mousePos);
		startSwitch->Update();

		resetSwitch->SetMousePos(mousePos);
		resetSwitch->Update();

		player->SetIsMove(startSwitch->IsPressSwitch());

		collision->IsMapChipCollision();

		if (resetSwitch->IsPressSwitch())
		{
			player->SetIsReset(true);
			startSwitch->SetIsPressSwitch(false);
			resetSwitch->SetIsPressSwitch(false);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		map->Draw();
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

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0)
		{
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	//マップの終了
	map->Finalize();
	//チャンクマネージャーの終了
	ChunkManager::GetInstance()->Finalize();
	return 0;
}
