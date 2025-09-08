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
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	Player* player = new Player();
	Collision* collision = new Collision();
	player->Initialize(keys, preKeys);
	collision->SetPlayer(player);

	Line line1;
	line1.startPos = { 160,0 };
	line1.endPos = { 160,416 };

	//チャンクの生成
	ChunkManager::GetInstance()->LoadChunk("chunk1");
	ChunkManager::GetInstance()->LoadChunk("chunk2");

	//マップの生成
	std::unique_ptr<Map>map = std::make_unique<Map>();
	map->Initialize();
	map->SetMap(ChunkManager::GetInstance()->FindChunk("chunk1")->GetChunk(), { 0,0 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("chunk2")->GetChunk(), { 0,7 });
	collision->SetMap(map->GetMap());

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
		collision->IsMapChip();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///





		//collision->Draw();
		player->Draw();

		map->Draw();

		for (int i = 0; i < 6; i++)
		{
			Novice::DrawLine(line1.startPos.x + (i * 32 * 5),
				line1.startPos.y,
				line1.endPos.x + (i * 32 * 5),
				line1.endPos.y,
				RED);
		}
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
