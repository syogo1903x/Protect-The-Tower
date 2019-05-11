#pragma once
#include "SceneBase.h"
#include "Shot.h"
#include <list>

using namespace std;

struct GunShot;
class BackGroundMusic;
class NowLoad;

class SceneGame :public SceneBase
{
public:
	SceneGame();
	~SceneGame();

	void Init() override;
	SceneBase *Update() override;
	void Draw() override;
	void Release() override;

	static char *GetResult() { return result; }
	static bool GetStart() { return isStart; }
	static int GetTimer() { return gameTime; }

	static bool GetGameClear() { return isGameClear; }
	static bool GetGameOver() { return isGameOver; }

private:
	int descriptionGraphHandle[2];
	bool isDescription;
	int descriptionTimeCount;
	bool isOptionDescription;


	static char *result;
	int startCount;

	static 	bool isStart;

	list<GunShot*> bullet;
	list<GunShot*>::iterator itr;

	int gameCount;
	static int gameTime;
	int gameTimeCount;

	// 定数
	const int GAME_START_COUNT = 260;
	const int GAME_CLEAR_COUNT = 90;
	const int GAME_CLEAR_TIME = 100;

	const int GAME_OVER = 0;
	const int ONE_SECOND = 60;

	const int COUNT_THREE = 20;
	const int COUNT_TWO = 80;
	const int COUNT_ONE = 140;
	const int COUNT_GAME_START = 200;
	const int COUNT_BLANK = 260;

	const int WEAV_TWO_COUNT = 30;
	const int WEAV_THREE_COUNT = 60;

	const int TOWER_LIFE_ZERO_COUNT = 320;
	const int WEAV_THREE = 3;
	const int WEAV_THREE_INTERVAL = 150;

	BackGroundMusic *shopBGM;
	SoundEffect *se[4];
	SoundEffect *menuSe[4];

	// ローディング
	NowLoad *nowLoading;

	int waveGraphHandle;
	int timeGraphHandle;

	static bool isGameClear;
	static bool isGameOver;

	int moneyCountGraphHandle;
	int gameStartGraphHandle;
	int numberGraphHandle[10];
	int timeCountGraphHandle[3];

	int playerMoneyCount;
	int gameTimeNumber;


	bool isGameMenu;
	int menuCount;
	int menuY;
	int menuSizeCount;
	float menuSizeUp;
	int menuGraphHandle;
	int descriptionRuleGraphHandle[2];
	int descriptionOperationGraphHandle[2];
	int descriptionRuleCount;
	int descriptionOperationCount;
	bool isDescriptionRule;
	bool isDescriptionOperation;
	int menuFrameGraphHandle;

	//
	bool isPush;
	int pushingCount;
	bool isMenuPush;
	int menuPushingCount;
};