#pragma once
#include "Common.h"

class UI
{
public:
	UI() {}
	~UI() {}
	void Init(char *_playerNumber);
	void Update(CharacterBase *_player);
	void Draw(CharacterBase *_player, Tower *_tower);
	void FadeDraw();
	void Release();

private:

	int playerHeartGraphHandle;
	int playerHeartDownGraphHandle;
	int playerIconGraphHandle;
	int playerIconDownGraphHandle;
	int aimingGraphHandle;

	int playerGraphHandle[5];
	int playerPutGraphHandle;

	int deathBlowGraphHandle[4];

	int fireGraphHandle[13];
	int fireCount;
	int alhaCount;
	int blendCount;

	int openShopGraphHandle[10];
	int closeShopGraphHandle[18];

	int moneyGraphHamdle;

	int gaugeGraphHandle;

	int deathBlowStartGraphHandle[2];
};