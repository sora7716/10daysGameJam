#include <Novice.h>
#include"gameObject/Player.h"
#include <imgui.h>
#include <cmath>
#include <vector>
#include "Vector2.h"
#include "Collision.h"
//#include "gameObject/Player.h"
const char kWindowTitle[] = "MyGame";




struct Field
{
	Vector2 pos;
	Vector2 screenPos;
	float width;
	float height;
	float screenWidth;
	float screenHidth;
};

struct Line
{
	Vector2Int stratPos;
	Vector2Int endPos;
};


//void RotateBlock180(std::vector<std::vector<int>>& mapList,
//	int xIndex, int yIndex, int width, int height) {
//
//	// 指定した位置を保存
//	std::vector<std::vector<int>> temp(height, std::vector<int>(width));
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//			temp[y][x] = mapList[yIndex + y][xIndex + x];
//		}
//	}
//
//	// 180°回転して書き戻し
//	for (int y = 0; y < height; y++) {
//		for (int x = 0; x < width; x++) {
//			int newX = width - 1 - x;
//			int newY = height - 1 - y;
//			mapList[yIndex + y][xIndex + x] = temp[newY][newX];
//		}
//	}
//}




/// <summary>
/// 座標変換
/// </summary>
/// <param name="y">Y座標</param>
/// <returns>座標変換されたY座標</returns>
float ConversionPosY(float y, float origin) {
	return (y - origin) * -1.0f;
}
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
	collision->Initialize(player, keys, preKeys);

	Field field;
	field.pos = { 0.0f,540.0f };
	field.width = 1280.0f;
	field.height = 200.0f;
	field.screenPos = { 0.0f,0.0f };
	field.screenWidth = 1280.0f;
	field.screenHidth = 720.0f;

	Line line1;
	line1.stratPos = { 160,0 };
	line1.endPos = { 160,416 };
	
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
		collision->Update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///





		collision->Draw();
		player->Draw();

		for (int i = 0; i < 6; i++)
		{
			Novice::DrawLine(line1.stratPos.x+(i*32*5),
				line1.stratPos.y,
				line1.endPos.x+(i * 32*5),
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
	return 0;
}
