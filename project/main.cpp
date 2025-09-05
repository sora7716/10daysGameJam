#include <Novice.h>
#include <imgui.h>
#include <cmath>
#include <vector>

//#include "gameObject/Player.h"
const char kWindowTitle[] = "MyGame";

const int kMapWidth = 20;
const int kMapHeight = 13;
const int kMapSize = 32;


struct Vector2 {
	float x;
	float y;
};

struct Vector2Int {
	int x;
	int y;
};

struct Player
{
	Vector2 pos;
	Vector2 posOld;
	float width;
	float height;
	Vector2 velocity;
	Vector2 accelaration;
	int isGround;
	Vector2Int rightTop;
	Vector2Int leftTop;
	Vector2Int rightBottom;
	Vector2Int leftBottom;

};


struct Field
{
	Vector2 pos;
	Vector2 screenPos;
	float width;
	float height;
	float screenWidth;
	float screenHidth;
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

	Player player;
	player.pos = { 0.0f,0.0f };
	player.posOld = { 0.0f,0.0f };
	player.width = 32.0f;
	player.height = 32.0f;
	player.velocity = { 4.0f,4.0f };
	player.accelaration = { 0.0f,0.8f };
	player.isGround = false;

	player.rightTop = { 0,0 };
	player.leftTop = { 0,0 };
	player.leftTop = { 0,0 };
	player.leftBottom = { 0,0 };



	Field field;
	field.pos = { 0.0f,540.0f };
	field.width = 1280.0f;
	field.height = 200.0f;
	field.screenPos = { 0.0f,0.0f };
	field.screenWidth = 1280.0f;
	field.screenHidth = 720.0f;

	/*Player* player=new Player();*/

	/*std::vector<std::vector<int>> map =
	{
		{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,0,0,0,0,0,1,0,0,0,0},
		{0,1,1,1,1,0,0,0,0,1,1,1,0,0,0},
		{1,1,1,1,1,0,0,0,1,1,1,1,1,0,0}
	};*/
	int map[kMapHeight][kMapWidth] =
	{


		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0},
		{0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	};
	Vector2 origin = { 0.0f,0.0f };
	Vector2Int mapPos = { 0,0 };
	Vector2Int mapSize = { 5,5 };

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


	// プレイヤーの下のチップ座標を計算

	// 右上
		player.rightTop.x = static_cast<int>(player.pos.x + player.width - 1.0f) / kMapSize;
		player.rightTop.y = static_cast<int>(player.pos.y) / kMapSize;

		// 右下
		player.rightBottom.x = static_cast<int>(player.pos.x + player.width - 1.0f) / kMapSize;
		player.rightBottom.y = static_cast<int>(player.pos.y + player.height - 1.0f) / kMapSize;

		// 左上
		player.leftTop.x = static_cast<int>(player.pos.x) / kMapSize;
		player.leftTop.y = static_cast<int>(player.pos.y) / kMapSize;

		// 左下
		player.leftBottom.x = static_cast<int>(player.pos.x) / kMapSize;
		player.leftBottom.y = static_cast<int>(player.pos.y + player.height - 1.0f) / kMapSize;

		// --- 前フレーム座標 ---
		player.posOld.x = player.pos.x;
		player.posOld.y = player.pos.y;



		// 上方向の移動
		if (keys[DIK_W]) {
			player.leftTop.y = static_cast<int>(player.pos.y - player.velocity.y) / kMapSize;
			player.rightTop.y = static_cast<int>(player.pos.y - player.velocity.y) / kMapSize;

			if (map[player.leftTop.y][player.leftTop.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else if (map[player.rightTop.y][player.rightTop.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else {
				player.pos.y -= player.velocity.y;
			}

		}

		// 左方向の移動
		if (keys[DIK_A]) {
			player.leftTop.x = static_cast<int>(player.pos.x - player.velocity.x) / kMapSize;
			player.leftBottom.x = static_cast<int>(player.pos.x - player.velocity.x) / kMapSize;

			if (map[player.leftTop.y][player.leftTop.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else if (map[player.leftBottom.y][player.leftBottom.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else {
				player.pos.x -= player.velocity.x;
			}

		}

		// 下方向の移動
		if (keys[DIK_S]) {
			player.leftBottom.y = static_cast<int>(player.pos.y + player.height - 1.0f + player.velocity.y) / kMapSize;
			player.rightBottom.y = static_cast<int>(player.pos.y + player.height - 1.0f + player.velocity.y) / kMapSize;

			if (map[player.leftBottom.y][player.leftBottom.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else if (map[player.rightBottom.y][player.rightBottom.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else {
				player.pos.y += player.velocity.y;
			}

		}
		// 右方向の移動
		if (keys[DIK_D]) {
			player.rightTop.x = static_cast<int>(player.pos.x + player.width - 1.0f + player.velocity.x) / kMapSize;
			player.rightBottom.x = static_cast<int>(player.pos.x + player.height - 1.0f + player.velocity.x) / kMapSize;

			if (map[player.rightTop.y][player.rightTop.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else if (map[player.rightBottom.y][player.rightBottom.x] == 1) {
				player.pos.x = player.posOld.x;
				player.pos.y = player.posOld.y;

			} else {
				player.pos.x += player.velocity.x;
			}

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		//backGround
		Novice::ScreenPrintf(100, 100, "%f", player.velocity.y);


		/*	Novice::DrawBox(static_cast<int>(field.screenPos.x),
				static_cast<int>(field.screenPos.y),
				static_cast<int>(field.screenWidth),
				static_cast<int>(field.screenHidth),
				0.0f, 0Xa9a9a9FF, kFillModeSolid);

			Novice::DrawBox(static_cast<int>(field.pos.x),
				0,
				static_cast<int>(field.width),
				static_cast<int>(field.height),
				0.0f, BLACK, kFillModeSolid);

			Novice::DrawBox(static_cast<int>(field.pos.x),
				static_cast<int>(field.pos.y),
				static_cast<int>(field.width),
				static_cast<int>(field.height),
				0.0f, BLACK, kFillModeSolid);
	*/




		Novice::DrawBox(
			static_cast<int>(origin.x) + mapPos.x * kMapSize,
			static_cast<int>(origin.y) + mapPos.y * kMapSize,
			mapSize.x * kMapSize,
			mapSize.y * kMapSize,
			0.0f, 0x00FF0055, kFillModeSolid
		);


		//ブロック
		for (int y = 0; y < kMapHeight; ++y) {
			for (int x = 0; x < kMapWidth; ++x) {
				if (map[y][x] == 1) {
					Novice::DrawBox(
						static_cast<int>(origin.x) + x * kMapSize,
						static_cast<int>(origin.y) + y * kMapSize,
						kMapSize, kMapSize, 0.0f, 0Xa9a9a9FF, kFillModeSolid
					);
					Novice::DrawBox(
						static_cast<int>(origin.x) + x * kMapSize,
						static_cast<int>(origin.y) + y * kMapSize,
						kMapSize, kMapSize, 0.0f, BLACK, kFillModeWireFrame
					);
				} else if (map[y][x] == 2)
				{
					Novice::DrawBox(
						static_cast<int>(origin.x) + x * kMapSize,
						static_cast<int>(origin.y) + y * kMapSize,
						kMapSize, kMapSize, 0.0f, RED, kFillModeSolid
					);
					Novice::DrawBox(
						static_cast<int>(origin.x) + x * kMapSize,
						static_cast<int>(origin.y) + y * kMapSize,
						kMapSize, kMapSize, 0.0f, BLACK, kFillModeWireFrame
					);
				} else if (map[y][x] == 0)
				{
					Novice::DrawBox(
						static_cast<int>(origin.x) + x * kMapSize,
						static_cast<int>(origin.y) + y * kMapSize,
						kMapSize, kMapSize, 0.0f, WHITE, kFillModeSolid
					);
					Novice::DrawBox(
						static_cast<int>(origin.x) + x * kMapSize,
						static_cast<int>(origin.y) + y * kMapSize,
						kMapSize, kMapSize, 0.0f, BLACK, kFillModeWireFrame
					);
				}
			}
		}

		Novice::DrawBox(static_cast<int>(player.pos.x),
			static_cast<int>(player.pos.y),
			static_cast<int>(player.width),
			static_cast<int>(player.height),
			0.0f, RED, kFillModeSolid);



		Novice::ScreenPrintf(820, 400, "LeftTop: map[%d][%d]", player.leftTop.y, player.leftTop.x);
		Novice::ScreenPrintf(820, 440, "LeftBottom: map[%d][%d]", player.leftBottom.y, player.leftBottom.x);
		Novice::ScreenPrintf(1070, 400, "RightTop: map[%d][%d]", player.rightTop.y, player.rightTop.x);
		Novice::ScreenPrintf(1070, 440, "RightBottom: map[%d][%d]", player.rightBottom.y, player.rightBottom.x);

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
