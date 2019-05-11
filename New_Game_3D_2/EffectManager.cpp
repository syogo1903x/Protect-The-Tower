#include "Common.h"

EffectManager::EffectManager()
{
	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(2000) < 0)
	{
		DxLib_End();
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

}

EffectManager::~EffectManager()
{
	Release();
}

// 初期化
void EffectManager::Init()
{
	// 攻撃ヒットエフェクト
	effect[PLAYER_HIT] = new EffectHit();
	effect[BOSS_HIT] = new EffectHit();
	effect[BOSS_HIT_2] = new EffectHit();
	effect[BOSS_HIT_3] = new EffectHit();
	effect[BOSS_HIT_4] = new EffectHit();
	// ジャンプエフェクト
	effect[PLAYER_JUMP] = new EffectJump();
	// 銃弾エフェクト
	effect[PLAYER_BULLET] = new EffectBullet();
	// 中ボスエフェクト
	effect[MEDIUM_APPEAR] = new EffectAppearMedium();
	// ボス出現エフェクト
	effect[BOSS_APPEAR] = new EffectAppearBoss();


	// 炎攻撃エフェクト	
	for (int i = 0; i < 50; i++)
	{
		effectFire[i] = new EffectFire();
	}

	// タワーのヒット時エフェクト
	effectTowerHit = new EffectTowerHit();
	// タワーの終了時エフェクト
	effectTowerOver = new EffectTowerOver();
	// タワーのダウン時エフェクト
	effectTowerDown = new EffectTowerDown();


	// 必殺技エフェクト
	effectDeathBlow[UKON] = new EffectDeathBlow_Ukon();
	effectDeathBlow[RUBY] = new EffectDeathBlow_Ruby();
	effectDeathBlow[CHINAMI] = new EffectDeathBlow_Chinami();
	effectDeathBlow[INU] = new EffectDeathBlow_Inu();
	effectDeathBlow[KARASU] = new EffectDeathBlow_Karasu();
	effectUseDeathBlow = new EffectDeathBlow();

	// ダウンエフェクト
	for (int i = 0; i < 20; i++)
	{
		effectSmallEnemyDown[i] = new EffectDown();
		effectSmallEnemyDown[i]->EffectInit();
	}
	for (int i = 0; i < 8; i++)
	{
		effectMediumBossDown[i] = new EffectDown();
		effectMediumBossDown[i]->EffectInit();
	}
	for (int i = 0; i < 4; i++)
	{
		effectBossDown[i] = new EffectDown();
		effectBossDown[i]->EffectInit();
	}



	// 必殺技エフェクト 初期化
	for (int i = 0; i < 5; i++)
	{
		effectDeathBlow[i]->EffectInit();
	}
	effectUseDeathBlow->EffectInit();

	// 攻撃ヒットエフェクト 初期化
	effect[PLAYER_HIT]->EffectInit();
	effect[BOSS_HIT]->EffectInit();
	effect[BOSS_HIT_2]->EffectInit();
	effect[BOSS_HIT_3]->EffectInit();
	effect[BOSS_HIT_4]->EffectInit();
	// ジャンプエフェクト 初期化
	effect[PLAYER_JUMP]->EffectInit();
	// 銃弾エフェクト 初期化
	effect[PLAYER_BULLET]->EffectInit();
	// 中ボスエフェクト 初期化
	effect[MEDIUM_APPEAR]->EffectInit();
	// ボス出現エフェクト 初期化
	effect[BOSS_APPEAR]->EffectInit();


	// 炎攻撃エフェクト 初期化	
	for (int i = 0; i < 50; i++)
	{
		effectFire[i]->EffectInit();
	}

	// タワーのヒット時エフェクト 初期化
	effectTowerHit->EffectInit();
	// タワーの終了時エフェクト 初期化
	effectTowerOver->EffectInit();
	// タワーのダウン時エフェクト
	effectTowerDown->EffectInit();

}

void EffectManager::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffectManager::UpdatePlayer(CharacterBase *_player)
{
	// 必殺技
	effectUseDeathBlow->UpdateCharter(_player);
	effectDeathBlow[Player::GetCharacterCount()]->UpdateCharter(_player);

	//printfDx("%d\n", Player::GetCharacterCount());

	// プレイヤージャンプ
	effect[PLAYER_JUMP]->UpdateCharter(_player);

	// ヒットエフェクト
	if (_player->GetDamage())
	{
		// 攻撃ヒット
		effect[PLAYER_HIT]->UpdateCharter(_player);
	}
	else
	{
		// 攻撃ヒット 初期化
		effect[PLAYER_HIT]->SetTime(30);
	}

	// 攻撃ヒット
	//effect[PLAYER_BULLET]->Update(_player);
}

void EffectManager::UpdateWeakEnemy(Enemy * _enemy)
{

}

void EffectManager::UpdateMedium(MediumBoss * _mediumBoss)
{

}

// ヒットエフェクト
void EffectManager::UpdateBoss(Boss * _boss[], int i)
{
	if (_boss[i]->GetDamage() && !_boss[i]->GetDead())
	{
		// 攻撃ヒット
		effect[BOSS_HIT + i]->UpdateCharter(_boss[i]);
	}
	else
	{
		// 攻撃ヒット 初期化
		effect[BOSS_HIT + i]->SetTime(30);
	}

}

// ボスの出現エフェクト
void EffectManager::UpdateAppearBoss(Boss * _boss)
{
	effect[BOSS_APPEAR]->UpdateCharter(_boss);
}

// 中ボスの出現エフェクト
void EffectManager::UpdateAppearMediumBoss(MediumBoss * _mediumBoss)
{
	effect[MEDIUM_APPEAR]->UpdateCharter(_mediumBoss);
}

// 雑魚敵のダウンエフェクト
void EffectManager::UpdateDownSmallEnemy(Enemy * _enemy[], int i)
{
	effectSmallEnemyDown[i]->UpdateCharter(_enemy[i]);
}

// 中ボスのダウンエフェクト
void EffectManager::UpdateDownMediumBoss(MediumBoss * _mediumBoss[], int i)
{
	effectMediumBossDown[i]->UpdateCharter(_mediumBoss[i]);
}

// ボスのダウンエフェクト
void EffectManager::UpdateDownBoss(Boss * _boss[], int i)
{
	effectBossDown[i]->UpdateCharter(_boss[i]);
}

// ディフェンスの炎攻撃エフェクト
void EffectManager::UpdateFire(DefenseBase * _defense, int i)
{
	effectFire[i]->UpdateDefense(_defense);
}

// タワーヒット時エフェクト
void EffectManager::UpdateTowerHit(Tower *_tower)
{
	effectTowerHit->UpdateTower(_tower);
}

// タワーの終了時エフェクト
void EffectManager::UpdateTowerOver(Tower * _tower)
{
	effectTowerOver->UpdateTower(_tower);
}

// タワーのダウン時エフェクト
void EffectManager::UpdateTowerDown(Tower * _tower)
{
	effectTowerDown->UpdateTower(_tower);
}

void EffectManager::Draw()
{
	// 各エフェクト表示
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffectManager::Release()
{

	// 解放
	for (int i = 0; i < 8; i++)
	{
		if (effect[i])
		{
			effect[i]->Release();
			delete(effect[i]);
			effect[i] = NULL;
		}
	}

	for (int i = 0; i < 50; i++)
	{
		if (effectFire[i])
		{
			effectFire[i]->Release();
			delete(effectFire[i]);
			effectFire[i] = NULL;
		}
	}

	if (effectTowerHit)
	{
		effectTowerHit->Release();
		delete(effectTowerHit);
		effectTowerHit = NULL;
	}

	if (effectTowerOver)
	{
		effectTowerOver->Release();
		delete(effectTowerOver);
		effectTowerOver = NULL;
	}

	if (effectUseDeathBlow)
	{
		effectUseDeathBlow->Release();
		delete(effectUseDeathBlow);
		effectUseDeathBlow = NULL;
	}


	for (int i = 0; i < 20; i++)
	{
		if (effectSmallEnemyDown[i])
		{
			effectSmallEnemyDown[i]->Release();
			delete(effectSmallEnemyDown[i]);
			effectSmallEnemyDown[i] = NULL;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (effectMediumBossDown[i])
		{
			effectMediumBossDown[i]->Release();
			delete(effectMediumBossDown[i]);
			effectMediumBossDown[i] = NULL;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (effectBossDown[i])
		{
			effectBossDown[i]->Release();
			delete(effectBossDown[i]);
			effectBossDown[i] = NULL;
		}
	}


	for (int i = 0; i < 5; i++)
	{
		if (effectDeathBlow[i])
		{
			effectDeathBlow[i]->Release();
			delete(effectDeathBlow[i]);
			effectDeathBlow[i] = NULL;
		}
	}
}
