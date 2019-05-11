#pragma once
#include "Common.h"

class CharacterBase;
class ItemBase;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Init();
	void UpdateSmallEnemy(CharacterBase *_enemy, int i);
	void UpdateMediumBoss(CharacterBase *_enemy, int i);
	void UpdateBoss(CharacterBase *_enemy, int i);
	void UpdatePlayer(CharacterBase *_player);
	void Draw();
	void Release();

	// 雑魚敵用
	ItemBase &GetSmallEnemyItemRecovery(int _set) { return *itemSmallEnemyRecovery[_set]; }
	ItemBase &GetSmallEnemyItemCoin(int _set) { return *itemSmallEnemyCoin[_set]; }
	// 中ボス用
	ItemBase &GetMediumBossItemRecovery(int _set) { return *itemMediumBossRecovery[_set]; }
	ItemBase &GetMediumBossItemCoin(int _set) { return *itemMediumBossCoin[_set]; }
	// ボス用
	ItemBase &GetBossItemRecovery(int _set) { return *itemBossRecovery[_set]; }
	ItemBase &GetBossItemCoin(int _set) { return *itemBossCoin[_set]; }


	const static int SMALL_ENEMY_ITEM_MAX = 20;
	const static int MEDIUM_BOSS_ITEM_MAX = 8;
	const static int BOSS_ITEM_MAX = 4;
private:

	// 雑魚敵用アイテム
	ItemBase *itemSmallEnemyRecovery[SMALL_ENEMY_ITEM_MAX];
	ItemBase *itemSmallEnemyCoin[SMALL_ENEMY_ITEM_MAX];

	// 中ボス用アイテム
	ItemBase *itemMediumBossRecovery[MEDIUM_BOSS_ITEM_MAX];
	ItemBase *itemMediumBossCoin[MEDIUM_BOSS_ITEM_MAX];

	// ボス用アイテム
	ItemBase *itemBossRecovery[BOSS_ITEM_MAX];
	ItemBase *itemBossCoin[BOSS_ITEM_MAX];


	int smallEnemyItemCount[SMALL_ENEMY_ITEM_MAX];
	int mediumBossItemCount[MEDIUM_BOSS_ITEM_MAX];
	int bossItemCount[BOSS_ITEM_MAX];

	int coinModelHandle;
	int recoveryModelHandle;

};