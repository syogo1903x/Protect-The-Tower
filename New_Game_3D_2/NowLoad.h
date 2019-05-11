#pragma once

enum MODEL_HANDLE
{
	GAMESTAGE,
	GAMESTAGE_OUT,
	SKYDOOM,
	TOWER,
	PLAYER,
	BULLET_SHOT,
	ENEMY_SMALL,
	ENEMY_MEDIUM,
	ENEMY_BOSS,
	ITEM_COIN,
	ITEM_RECOVERY,
	DEFENSE_WALL,
	DEFENSE_ATACKBALL,
	DEFENSE_FIRE,
	DEFENSE_SOLDIER,
	DEFENSE_BUY,
	DEFENSE_ARROW,

};


class NowLoad
{
public:
	NowLoad();
	~NowLoad();

	void CreateSubThread();
	void SubThreadUpdate();
	void Release();

	static int GetModelHandle(MODEL_HANDLE _set) { return modelHandle[_set]; }

private:
	const static int MODEL_MAX = 17;
	int count;
	static int modelHandle[MODEL_MAX];

};