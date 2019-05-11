#pragma once
//#pragma warning (disable : 4996)

class EffectBase;
class EffectLaser;
class EffectMagicTeam;
class EffectHit;
class EffectDeathBlow;
class EffectDeathBlow_Ukon;
class EffectDeathBlow_Ruby;
class EffectDeathBlow_Chinami;
class EffectDeathBlow_Inu;
class EffectDeathBlow_Karasu;
class EffectJump;
class EffectBullet;
class EffectDown;

enum EFFECT
{
	PLAYER_HIT,
	BOSS_HIT,
	BOSS_HIT_2,
	BOSS_HIT_3,
	BOSS_HIT_4,
	PLAYER_JUMP,
	PLAYER_BULLET,

	MEDIUM_APPEAR,
	BOSS_APPEAR,
};

enum EFFECT_DEATHBLOW
{
	UKON,
	RUBY,
	CHINAMI,
	INU,
	KARASU,
};

class EffectManager
{
public:
	~EffectManager();

	static EffectManager &EffectManagerInctance()
	{
		static EffectManager effectManagerInstance;
		return effectManagerInstance;
	}

	void Init();
	void Update();
	// プレイヤーのエフェクト
	void UpdatePlayer(CharacterBase *_player);
	// 雑魚的のダメージエフェクト
	void UpdateWeakEnemy(Enemy *_enemy);
	// 中ボスのエフェクト
	void UpdateMedium(MediumBoss *_mediumBoss);
	// ボスのエフェクト
	void UpdateBoss(Boss *_boss[], int i);

	// ボスの出現エフェクト
	void UpdateAppearBoss(Boss *_boss);
	// 中ボスの出現エフェクト
	void UpdateAppearMediumBoss(MediumBoss *_mediumBoss);

	// 雑魚敵のダウン時エフェクト
	void UpdateDownSmallEnemy(Enemy *_enemy[], int i);
	// 中ボスのダウン時エフェクト
	void UpdateDownMediumBoss(MediumBoss *_mediumBoss[], int i);
	// ボスのダウン時エフェクト
	void UpdateDownBoss(Boss *_boss[], int i);

	// 炎エフェクト
	void UpdateFire(DefenseBase *_defense, int i);
	// タワーのヒットエフェクト
	void UpdateTowerHit(Tower *_tower);
	// タワーの終了エフェクト
	void UpdateTowerOver(Tower *_tower);
	// タワーのダウンエフェクト
	void UpdateTowerDown(Tower *_tower);

	// 描画
	void Draw();
	// 解放
	void Release();


private:
	EffectManager();
	// 各エフェクト
	EffectBase *effect[8];

	// 必殺技エフェクト
	EffectBase *effectUseDeathBlow;
	EffectBase *effectDeathBlow[5];
	// 炎用エフェクト
	EffectBase *effectFire[50];
	// タワーのヒットエフェクト
	EffectBase *effectTowerHit;
	// タワーのダウンエフェクト
	EffectBase *effectTowerDown;
	// タワーの終了エフェクト
	EffectBase *effectTowerOver;
	// 敵のダウン時エフェクト
	EffectBase *effectSmallEnemyDown[20];
	EffectBase *effectMediumBossDown[8];
	EffectBase *effectBossDown[4];

};

#define EFFECT				EffectManager::EffectManagerInctance()
