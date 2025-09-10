#pragma once
class Particles
{
private:
	float lightPosX[200] = {};//円の位置
	float lightPosY[200] = {};
	float lightSpeed = 5.0f;//円のスピード
	int isLightShot[200] = {};//円を発射したかのフラグ
	float lightRadius[200] = {};//円の半径
	float lightCourseX[200] = {};//円の移動限界
	float lightCourseY[200] = {};
	float lenght[200] = {};//円の正規化
	unsigned int  clea[200] = {};//円の透明度
	unsigned int  Color[200] = {};//円の色
	int isStart = false;//スタートしたかのフラグ
	float centerPosX = 1000.0f;//画面の中心位置
	float centerPosY = 600.0f;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};

