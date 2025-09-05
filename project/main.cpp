#include <Novice.h>
#include <imgui.h>
#include "Vector2.h"
#include <array>
#include "gameObject/ChunkManager.h"
#include <vector>

const char kWindowTitle[] = "MyGame";
const int kBlockSize = 32;

enum BlockType
{
	kBlank,
	kBlock,
};

void DrowMap(std::vector<std::vector<int>>map, const Vector2& origin)
{

	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{

			if (map[y][x] == kBlock)
			{
				Novice::DrawBox(
					static_cast<int>(origin.x) + x * kBlockSize,
					static_cast<int>(origin.y) + y * kBlockSize, kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeWireFrame);
			}
		}
	}
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2 origin = {};

	ChunkManager::GetInstance()->LoadChunk("chunk1");
	ChunkManager::GetInstance()->LoadChunk("chunk2");
	ChunkManager::GetInstance()->LoadChunk("chunk3");
	Chunk* chunk1 = ChunkManager::GetInstance()->FindChunk("chunk1");
	Chunk* chunk2 = ChunkManager::GetInstance()->FindChunk("chunk2");
	Chunk* chunk3 = ChunkManager::GetInstance()->FindChunk("chunk3");

	std::vector<std::vector<int>>map;
	map.resize(Chunk::kMaxHeight);

	for (int y = 0; y < Chunk::kMaxHeight; y++)
	{
		map[y].resize(Chunk::kMaxWidth * 3);

		for (int x = 0; x < Chunk::kMaxWidth * 3; x++)
		{
			if (x < 5)
			{
				map[y][x] = chunk1->GetChunk()[y][x];
			}
			else if (x < 10)
			{
				map[y][x] = chunk2->GetChunk()[y][x - Chunk::kMaxWidth];
			}
			else
			{
				map[y][x] = chunk3->GetChunk()[y][x - Chunk::kMaxWidth * 2];
			}
		}
	}



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

		if (ImGui::Button("chunk1"))
		{
			chunk1 = ChunkManager::GetInstance()->FindChunk("chunk1");
		}
		else if (ImGui::Button("chunk2"))
		{
			chunk1 = ChunkManager::GetInstance()->FindChunk("chunk2");
		}
		else if (ImGui::Button("chunk3"))
		{
			chunk1 = ChunkManager::GetInstance()->FindChunk("chunk3");
		}
		ImGui::End();





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrowMap(map, origin);

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
