#pragma once
#include "SceneBase.h"

class SoundEffect;


class SceneMenu :public SceneBase
{
public:
	SceneMenu();
	~SceneMenu();

	void Init() override;
	SceneBase *Update() override;
	void Draw() override;
	void Release() override;

	static char *GetPlayer() { return playerModelHandle; }
	static char *GetStage() { return stageModelHandle; }

private:
	int nowLoadingGaprhHandle;
	int optionGraphHandle;
	int moouseGraphHandle[2];
	int difficultGraphHandle[3];
	int animation;
	int startGraphHandle;
	bool isPlayerSelect;
	bool isMenuSelect;

	int selectGraphHamdle[2];
	int backGraphHandle[2];

	int playerNomer;
	static char *playerModelHandle;
	char *characterModelHandle[5];

	int stageNomer;
	static char *stageModelHandle;
	char *stageObjModelHandle[3];

	int characterGraphHandle[5];
	int characterStartGraphHandle[5];
	int frameGraphHandle[2];

	int stageGraphHandle[3];

	int menuCount;

	int mouseX;
	int mouseY;

	bool isPlayerDecision[5];
	bool isMenuDecision[3];
	bool isChange;

	bool isPush;
	int pushCount;

	const int PLAYER_MAX = 4;
	const int MENU_MAX = 2;
	const int PLAYER_COUNT = 5;
	const int MENU_COUNT = 3;

	const int PLAYER_BLANK = 200;
	const int PLAYER_BLANK_Y = 250;
	const int MENU_BLANK = 350;
	const int MENU_Y = 650;

	const int HIT_CHECK = 120;
	const int HIT_SIZE = 300;

	float playerSizeUp;
	float playerSizeUpBlank;
	int   playerSizeUpCount;

	float menuSizeUp;
	float menuSizeUpBlank;
	int   menuSizeUpCount;

	SoundEffect *se[3];
	bool isSoundEffect[5];

	int selecctMenuGraphHandle[2];
	int selecctPushMenuGraphHandle[2];
};