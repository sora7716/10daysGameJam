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

	const Vector2Int mapPos = {};

	//チャンクの生成
	ChunkManager::GetInstance()->LoadChunk("chunk1");
	ChunkManager::GetInstance()->LoadChunk("chunk2");

	//マップの生成
	std::unique_ptr<Map>map = std::make_unique<Map>();
	map->Initialize();
	map->SetMap(ChunkManager::GetInstance()->FindChunk("chunk1")->GetChunk(), { 0,0 });
	map->SetMap(ChunkManager::GetInstance()->FindChunk("chunk2")->GetChunk(), { 0,7 });
	collision->SetMap(map->GetMap());

	AABB startButton{
		.min{200.0f,500.0f},
		.max{250.0f,550.0f}
	};

	int color = BLUE;

	AABB swapButton{
		.min{300.0f,500.0f},
		.max{350.0f,550.0f}
	};

	AABB flipButton{
		.min{500.0f,500.0f},
		.max{550.0f,550.0f}
	};

	bool isSwap = false;
	bool isFlip = false;

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

		if (Collision::IsMouseOverRect(startButton))
		{
			color = RED;
			if (Novice::IsTriggerMouse(0))
			{
				player->SetIsMove(true);
			}
		}
		else
		{
			color = BLUE;
		}


		if (Collision::IsMouseOverRect(swapButton))
		{
			if (Novice::IsTriggerMouse(0))
			{
				isSwap = !isSwap;
			}

		}

		if (Collision::IsMouseOverRect(flipButton))
		{
			if (Novice::IsTriggerMouse(0))
			{
				isFlip = !isFlip;
			}

		}

		ImGui::Checkbox("isSwap", &isSwap);
		ImGui::Checkbox("isFlip", &isFlip);
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

		Novice::DrawBox(
			static_cast<int>(startButton.min.x),
			static_cast<int>(startButton.min.y),
			static_cast<int>(startButton.max.x - startButton.min.x),
			static_cast<int>(startButton.max.y - startButton.min.y),
			0.0f, color, kFillModeWireFrame
		);

		Novice::DrawBox(
			static_cast<int>(swapButton.min.x),
			static_cast<int>(swapButton.min.y),
			static_cast<int>(swapButton.max.x - swapButton.min.x),
			static_cast<int>(swapButton.max.y - swapButton.min.y),
			0.0f, RED, kFillModeWireFrame
		);

		Novice::DrawBox(
			static_cast<int>(flipButton.min.x),
			static_cast<int>(flipButton.min.y),
			static_cast<int>(flipButton.max.x - flipButton.min.x),
			static_cast<int>(flipButton.max.y - flipButton.min.y),
			0.0f, RED, kFillModeWireFrame
		);

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
