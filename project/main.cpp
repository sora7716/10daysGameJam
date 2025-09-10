#include <Novice.h>
#include "scene/StageScene1.h"
#include "scene/StageScene2.h"
#include"gameObject/ChunkManager.h"
#include "Scene/SelectScene.h"
#include "Scene/TitleScene.h"
const char kWindowTitle[] = "MyGame";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector2Int mousePos_ = {};

	TitleScene* titleScene = new TitleScene();
	SelectScene* selectScene = new SelectScene();

	StageScene1* stageScene1 = new StageScene1();
	StageScene2* stageScene2 = new StageScene2();

	int soundEffects[static_cast<int>(soundEffects::kCount)] =
	{
		Novice::LoadAudio("./resources/sound/goal.mp3"),
		Novice::LoadAudio("./resources/sound/jump.mp3"),
		Novice::LoadAudio("./resources/sound/select.mp3"),
		Novice::LoadAudio("./resources/sound/bgmTitle.mp3"),
		Novice::LoadAudio("./resources/sound/bgmSelect.mp3"),
		Novice::LoadAudio("./resources/sound/bgmStage.mp3"),
		Novice::LoadAudio("./resources/sound/inversion.mp3"),
		Novice::LoadAudio("./resources/sound/change.mp3"),

	};

	int soundHandle = 0;
	Scene scene = kTitle;
#ifdef _DEBUG
	scene = kTitle;
#endif // _DEBUG

	Scene preScene = kNone;
	stageScene1->Initialize(keys, preKeys, &mousePos_);
	stageScene2->Initialize(keys, preKeys, &mousePos_);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);


		///
		/// ↑更新処理ここまで
		///

		if (scene != preScene)
		{
			if (scene == kTitle)
			{
				soundHandle = Novice::PlayAudio(static_cast<int>(soundEffects::kBgmTitle), 0, 0.3f);
				titleScene->Initialize(&mousePos_);

			}
			else if (scene == kSelect)
			{
				Novice::StopAudio(soundHandle);

				if (!Novice::IsPlayingAudio(soundHandle))
				{
					soundHandle = Novice::PlayAudio(static_cast<int>(soundEffects::kBgmSelect), 0, 0.3f);
				}
				selectScene->Initialize(&mousePos_);
			}
			else if (scene == kStage1)
			{

				Novice::StopAudio(soundHandle);

				stageScene1->Initialize(keys, preKeys, &mousePos_);

				if (!Novice::IsPlayingAudio(soundHandle))
				{
					soundHandle = Novice::PlayAudio(static_cast<int>(soundEffects::kBgmStage), 0, 0.3f);
				}
			}
			else if (scene == kStage2)
			{
				Novice::StopAudio(soundHandle);
				stageScene2->Initialize(keys, preKeys, &mousePos_);

				if (!Novice::IsPlayingAudio(soundHandle))
				{
					soundHandle = Novice::PlayAudio(static_cast<int>(soundEffects::kBgmStage), 0, 0.3f);
				}
			}
		}

		preScene = scene;

		if (scene == kTitle)
		{
			titleScene->Update();

			if (titleScene->IsFinished())
			{
				scene = titleScene->GetNextScene();
			}

			titleScene->Draw();
		}
		else if (scene == kSelect)
		{
			selectScene->Update();
			if (selectScene->IsFinised())
			{
				scene = selectScene->GetNextScene();
			}
			selectScene->Draw();
		}
		else if (scene == kStage1)
		{
			stageScene1->Update();
			if (stageScene1->IsFinised())
			{
				scene = stageScene1->GetNextScene();
			}
			stageScene1->Draw();
		}
		else if (scene == kStage2)
		{
			stageScene2->Update();
			if (stageScene2->IsFinised())
			{
				scene = stageScene2->GetNextScene();
			}
			stageScene2->Draw();
		}

		///
		/// ↓描画処理ここから
		///



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
	//チャンクマネージャーの終了
	ChunkManager::GetInstance()->Finalize();
	return 0;
}
