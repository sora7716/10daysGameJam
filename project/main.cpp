#include <Novice.h>
#include <imgui.h>
#include "Vector2.h"
#include <array>
#include "gameObject/Chunk.h"

const char kWindowTitle[] = "MyGame";

const int kMaxWidth = 5;
const int kMaxHeight = 5;
const int kBlockSize = 32;

enum BlockType
{
	kBlank,
	kBlock,
};

void DrowMap(std::array<std::array<int, kMaxWidth>, kMaxHeight>map, const Vector2& origin)
{

	for (int y = 0; y < kMaxHeight; y++)
	{
		for (int x = 0; x < kMaxWidth; x++)
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

	Chunk* chunk = new Chunk();
	chunk->LoadMapChipCsv("resource/map3.csv");

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
		ImGui::End();

		



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrowMap(chunk->GetChunk(), origin);

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
	return 0;
}
