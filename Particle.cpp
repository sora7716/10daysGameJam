#include "Particle.h"
#include"Novice.h"
#include <corecrt_math.h>
void Particle::Initialize()//初期化
{
	for (int i = 0; i < 200; i++)//各変数に初期値を代入
	{
		isLightShot[i] = false;
		lightRadius[i] = 10.0f;
		clea[i] = 255;
		Color[i] = 0xFF0000 | clea[i];
	}
}

void Particle::Update()
{
	//スタート

	isStart = true;


	if (isStart)
	{
		for (int i = 0; i < 200; i++)
		{
			if (!isLightShot[i])
			{
				isLightShot[i] = true;
				lightPosX[i] = centerPosX;//円を画面中央に移動
				lightPosY[i] = centerPosY;
				lightCourseX[i] = static_cast<float>(rand() % 21 - 10);//円の方向を決める
				lightCourseY[i] = static_cast<float>(rand() % 10 - 10);

				break;
			}
		}

		for (int i = 0; i < 200; i++)
		{
			if (isLightShot[i])
			{

				lenght[i] = sqrtf(lightCourseX[i] * lightCourseX[i] + lightCourseY[i] * lightCourseY[i]);

				if (lenght[i] > 0.0f)
				{
					lightCourseX[i] /= lenght[i];//円の正規化
					lightCourseY[i] /= lenght[i];

					lightPosX[i] += lightCourseX[i] * lightSpeed;
					lightPosY[i] += lightCourseY[i] * lightSpeed;

				}


			}

		}
		for (int i = 0; i < 200; i++)
		{
			if (lightPosX[i] >= 1050.0f || lightPosY[i] <= 550.0f || lightPosX[i] <= 950.0f || lightPosY[i] >= 750.0f)
			{
				clea[i] -= 15;

				if (clea[i] <= 0.0f)//円の透明度が0になったら消える
				{
					isLightShot[i] = false;
					clea[i] = 255;
				}
			}
		}
	}
}

void Particle::Draw()
{
	for (int i = 0; i < 200; i++) {
		// 赤(R=255,G=0,B=0) に α=clea[i] を適用
		Color[i] = (0xFF0000 << 8) | (clea[i] & 0xFF);
		if (isLightShot[i]) {
			Novice::DrawEllipse(
				static_cast<int>(lightPosX[i]),
				static_cast<int>(lightPosY[i]),
				static_cast<int>(lightRadius[i]),
				static_cast<int>(lightRadius[i]),
				0.0f,
				Color[i],
				kFillModeSolid
			);
		}
	}
}