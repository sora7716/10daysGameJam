#pragma once
#pragma once
#include "gameObject/ResourceData.h"

class Player;
class Collision;
class Map;
class GameSwitch;
/// <summary>
/// �X�e�[�W1
/// </summary>
class StageScene3
{
private://�����o�ϐ�
	Player* player = nullptr;
	Collision* collision = nullptr;
	Vector2Int* mousePos_ = nullptr;

	int playerTexture = 0;

	//���̃V�[��
	Scene nextScene_ = kNone;

	//�V�[���̏I���t���O
	bool isFinised_ = false;

	Map* map = nullptr;

	GameSwitch* startSwitch = nullptr;

	AABB startSwitchData
	{
	.min{100.0f,600.0f},
	.max{132.0f,632.0f}
	};

	GameSwitch* resetSwitch = nullptr;

	AABB resetSwitchData
	{
	.min{150.0f,600.0f},
	.max{182.0f,632.0f}
	};

	//�X�^�[�ƃ{�^�������������ǂ����@
	bool isPressStart_ = false;

public://�����o�֐�

	void Initialize(char* keys, char* preKeys, Vector2Int* mousePos);

	void Update();

	void Draw();

	~StageScene3();

	Scene GetNextScene() { return nextScene_; };

	bool IsFinised() { return isFinised_; };
};

