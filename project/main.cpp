#include <Novice.h>
#include <imgui.h>
#include "gameObject/ChunkManager.h"
#include "gameObject/Map.h"

const char kWindowTitle[] = "MyGame";
const int kBlockSize = 32;


//void DrowMap(std::vector<std::vector<int>>map, const Vector2& origin)
//{
//
//	for (int y = 0; y < map.size(); y++)
//	{
//		for (int x = 0; x < map[y].size(); x++)
//		{
//
//			if (map[y][x] == kBlock)
//			{
//				Novice::DrawBox(
//					static_cast<int>(origin.x) + x * kBlockSize,
//					static_cast<int>(origin.y) + y * kBlockSize, kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeWireFrame);
//			}
//		}
//	}
//};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2 origin = {};

	//チャンクの読み込み
	ChunkManager::GetInstance()->LoadChunk("chunk1");
	ChunkManager::GetInstance()->LoadChunk("chunk2");
	ChunkManager::GetInstance()->LoadChunk("chunk3");

	//検索したチャンクを変数にする
	Chunk* chunk1 = ChunkManager::GetInstance()->FindChunk("chunk1");
	Chunk* chunk2 = ChunkManager::GetInstance()->FindChunk("chunk2");
	Chunk* chunk3 = ChunkManager::GetInstance()->FindChunk("chunk3");

	//マップの生成
	std::unique_ptr<Map>map = std::make_unique<Map>();

	//マップの初期化
	map->Initialize({ Chunk::kMaxWidth * 3,Chunk::kMaxHeight * 3 });
	
	//マップの原点の設定
	map->SetOrigin({ 0.0f, 0.0f });

	//横に配置
	map->SetMap(chunk1->GetChunk(), { 0,0 });
	map->SetMap(chunk2->GetChunk(), { 5,0 });
	map->SetMap(chunk3->GetChunk(), { 10,0 });
	//縦に配置する
	map->SetMap(chunk2->GetChunk(), { 0,5 });
	map->SetMap(chunk3->GetChunk(), { 0,10 });

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

		ImGui::Begin("Chunk");
		ImGui::DragFloat2("origin", &origin.x, 1.0f);

		if (ImGui::Button("chunk2"))
		{
			map->SetMap(chunk2->GetChunk(), { 0,0 });

		}
		/*else if (ImGui::Button("chunk2"))
		{
			chunk1 = ChunkManager::GetInstance()->FindChunk("chunk2");
		}
		else if (ImGui::Button("chunk3"))
		{
			chunk1 = ChunkManager::GetInstance()->FindChunk("chunk3");
		}*/
		ImGui::End();

		
		




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//DrowMap(map, origin);
		map->Draw();

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
	ChunkManager::GetInstance()->Finalize();
	return 0;
}
