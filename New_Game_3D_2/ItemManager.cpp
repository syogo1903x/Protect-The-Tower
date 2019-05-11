#include "ItemManager.h"

ItemManager::ItemManager()
{
	// コインと回復のモデルの読み込み
	coinModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ITEM_COIN));
	recoveryModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ITEM_RECOVERY));
}

ItemManager::~ItemManager()
{

}

// 初期化
void ItemManager::Init()
{
	// 雑魚敵用アイテム
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// 回復
		itemSmallEnemyRecovery[i] = new Recovery();
		itemSmallEnemyRecovery[i]->Init(recoveryModelHandle);
		// お金
		itemSmallEnemyCoin[i] = new Coin();
		itemSmallEnemyCoin[i]->Init(coinModelHandle);

		// 雑魚敵用カウント 初期化
		smallEnemyItemCount[i] = 0;
	}

	// 中ボス敵用アイテム
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemMediumBossRecovery[i] = new Recovery();
		itemMediumBossRecovery[i]->Init(recoveryModelHandle);
		// お金
		itemMediumBossCoin[i] = new Coin();
		itemMediumBossCoin[i]->Init(coinModelHandle);

		// 中ボス用カウント 初期化
		mediumBossItemCount[i] = 0;

	}

	// ボス敵用アイテム
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemBossRecovery[i] = new Recovery();
		itemBossRecovery[i]->Init(recoveryModelHandle);
		// お金
		itemBossCoin[i] = new Coin();
		itemBossCoin[i]->Init(coinModelHandle);

		// ボス用カウント 初期化
		bossItemCount[i] = 0;
	}

}

// 雑魚敵の更新
void ItemManager::UpdateSmallEnemy(CharacterBase *_enemy, int i)
{
	// 雑魚敵が出現していればカウント開始
	if (_enemy->GetLife() > 0) { smallEnemyItemCount[i]++; }

	// とりあえずバラバラ表示
	if (smallEnemyItemCount[i] % 2 == 0)
	{
		itemSmallEnemyCoin[i]->Update(_enemy);
	}
	else
	{
		itemSmallEnemyRecovery[i]->Update(_enemy);
	}
}

// 中ボスの更新
void ItemManager::UpdateMediumBoss(CharacterBase *_enemy, int i)
{
	// 中ボスが出現していればカウント開始
	if (_enemy->GetLife() > 0) { mediumBossItemCount[i]++; }

	// とりあえずバラバラ表示
	if (mediumBossItemCount[i] % 2 == 0)
	{
		itemMediumBossCoin[i]->Update(_enemy);
	}
	else
	{
		itemMediumBossRecovery[i]->Update(_enemy);
	}
}

// ボスの更新
void ItemManager::UpdateBoss(CharacterBase *_enemy, int i)
{
	// ボスが出現していればカウント開始
	if (_enemy->GetLife() > 0) { bossItemCount[i]++; }

	// とりあえずバラバラ表示
	if (bossItemCount[i] % 2 == 0)
	{
		itemBossCoin[i]->Update(_enemy);
	}
	else
	{
		itemBossRecovery[i]->Update(_enemy);
	}
}

// プレイヤーの更新
void ItemManager::UpdatePlayer(CharacterBase * _player)
{
	// 雑魚的
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// 回復
		itemSmallEnemyRecovery[i]->UpdatePlayerToItem(_player);
		// お金
		itemSmallEnemyCoin[i]->UpdatePlayerToItem(_player);
	}
	
	// 中ボス敵用アイテム
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemMediumBossRecovery[i]->UpdatePlayerToItem(_player);
		// お金
		itemMediumBossCoin[i]->UpdatePlayerToItem(_player);
	}

	// ボス敵用アイテム
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemBossRecovery[i]->UpdatePlayerToItem(_player);
		// お金
		itemBossCoin[i]->UpdatePlayerToItem(_player);
	}
}

// 描画
void ItemManager::Draw()
{
	// 雑魚的
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// 回復
		itemSmallEnemyRecovery[i]->Draw();
		// お金
		itemSmallEnemyCoin[i]->Draw();
	}

	// 中ボス敵用アイテム
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemMediumBossRecovery[i]->Draw();
		// お金
		itemMediumBossCoin[i]->Draw();
	}

	// ボス敵用アイテム
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemBossRecovery[i]->Draw();
		// お金
		itemBossCoin[i]->Draw();
	}
}

// 解放
void ItemManager::Release()
{
	// 雑魚敵用アイテム
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// 回復
		itemSmallEnemyRecovery[i]->Release();
		delete(itemSmallEnemyRecovery[i]);
		itemSmallEnemyRecovery[i] = NULL;
		// お金
		itemSmallEnemyCoin[i]->Release();
		delete(itemSmallEnemyCoin[i]);
		itemSmallEnemyCoin[i] = NULL;
	}

	// 中ボス敵用アイテム
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemMediumBossRecovery[i]->Release();
		delete(itemMediumBossRecovery[i]);
		itemMediumBossRecovery[i] = NULL;
		// お金
		itemMediumBossCoin[i]->Release();
		delete(itemMediumBossCoin[i]);
		itemMediumBossCoin[i] = NULL;
	}

	// ボス敵用アイテム
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// 回復
		itemBossRecovery[i]->Release();
		delete(itemBossRecovery[i]);
		itemBossRecovery[i] = NULL;
		// お金
		itemBossCoin[i]->Release();
		delete(itemBossCoin[i]);
		itemBossCoin[i] = NULL;
	}

	// モデルの削除
	MV1DeleteModel(coinModelHandle);
	coinModelHandle = NULL;

	MV1DeleteModel(recoveryModelHandle);
	recoveryModelHandle = NULL;
}
