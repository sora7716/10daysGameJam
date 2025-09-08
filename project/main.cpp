#include <Novice.h>
#include <imgui.h>
#include <cmath>
#include <vector>
#include "calc/Vector2.h"
#include "calc/Collision.h"
#include"gameObject/Player.h"
#include "gameObject/Map.h"
#include "gameObject/ChunkManager.h"
const char kWindowTitle[] = "MyGame";

struct  Line
{
	Vector2Int startPos;
	Vector2Int endPos;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1312, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	Player* player = new Player();
	Collision* collision = new Collision();
	collision->SetPlayer(player);

	/*Line line1;
	line1.startPos = { 160,0 };
	line1.endPos = { 160,416 };*/

	//ブロックテクスチャの読み込み
	int blockTextures[2] =
	{
		Novice::LoadTexture("./resources/tile_1.png"),
		Novice::LoadTexture("./resources/tile_2.png")
	};

	int playerTexture = Novice::LoadTexture("./resources/player.png");

	//チャンクの生成
	ChunkManager::GetInstance()->LoadChunk("map/up_0-1", "up_0-1", blockTextures[1]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-2", "up_0-2", blockTextures[1]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-3", "up_0-3", blockTextures[1]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-4", "up_0-4", blockTextures[1]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-5", "up_0-5", blockTextures[1]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-6", "up_0-6", blockTextures[1]);
	ChunkManager::GetInstance()->LoadChunk("map/up_0-7", "up_0-7", blockTextures[1]);

	ChunkManager::GetInstance()->LoadChunk("map/under_0-1", "under_0-1", blockTextures[0]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-2", "under_0-2", blockTextures[0]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-3", "under_0-3", blockTextures[0]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-4", "under_0-4", blockTextures[0]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-5", "under_0-5", blockTextures[0]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-6", "under_0-6", blockTextures[0]);
	ChunkManager::GetInstance()->LoadChunk("map/under_0-7", "under_0-7", blockTextures[0]);

	//マップの生成
	std::unique_ptr<Map>map = std::make_unique<Map>();
	map->Initialize();
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-1"), { 3 ,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-2"), { 8 ,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-3"), { 13,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-4"), { 18,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-5"), { 23,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-6"), { 28,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("up_0-7"), { 33,3 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-1"), { 3,9 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-2"), { 8,9 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-3"), { 13,9 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-4"), { 18,9 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-5"), { 23,9 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-6"), { 28,9 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("under_0-7"), { 33,9 });
	collision->SetMap(map->GetMap());

	player->Initialize(keys, preKeys, map->GetMap(),playerTexture);
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		player->Update();
		collision->IsMapChipCollision();

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
	//ChunkManager::GetInstance()->Finalize();
	return 0;
}
