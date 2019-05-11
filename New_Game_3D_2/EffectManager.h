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
	// �v���C���[�̃G�t�F�N�g
	void UpdatePlayer(CharacterBase *_player);
	// �G���I�̃_���[�W�G�t�F�N�g
	void UpdateWeakEnemy(Enemy *_enemy);
	// ���{�X�̃G�t�F�N�g
	void UpdateMedium(MediumBoss *_mediumBoss);
	// �{�X�̃G�t�F�N�g
	void UpdateBoss(Boss *_boss[], int i);

	// �{�X�̏o���G�t�F�N�g
	void UpdateAppearBoss(Boss *_boss);
	// ���{�X�̏o���G�t�F�N�g
	void UpdateAppearMediumBoss(MediumBoss *_mediumBoss);

	// �G���G�̃_�E�����G�t�F�N�g
	void UpdateDownSmallEnemy(Enemy *_enemy[], int i);
	// ���{�X�̃_�E�����G�t�F�N�g
	void UpdateDownMediumBoss(MediumBoss *_mediumBoss[], int i);
	// �{�X�̃_�E�����G�t�F�N�g
	void UpdateDownBoss(Boss *_boss[], int i);

	// ���G�t�F�N�g
	void UpdateFire(DefenseBase *_defense, int i);
	// �^���[�̃q�b�g�G�t�F�N�g
	void UpdateTowerHit(Tower *_tower);
	// �^���[�̏I���G�t�F�N�g
	void UpdateTowerOver(Tower *_tower);
	// �^���[�̃_�E���G�t�F�N�g
	void UpdateTowerDown(Tower *_tower);

	// �`��
	void Draw();
	// ���
	void Release();


private:
	EffectManager();
	// �e�G�t�F�N�g
	EffectBase *effect[8];

	// �K�E�Z�G�t�F�N�g
	EffectBase *effectUseDeathBlow;
	EffectBase *effectDeathBlow[5];
	// ���p�G�t�F�N�g
	EffectBase *effectFire[50];
	// �^���[�̃q�b�g�G�t�F�N�g
	EffectBase *effectTowerHit;
	// �^���[�̃_�E���G�t�F�N�g
	EffectBase *effectTowerDown;
	// �^���[�̏I���G�t�F�N�g
	EffectBase *effectTowerOver;
	// �G�̃_�E�����G�t�F�N�g
	EffectBase *effectSmallEnemyDown[20];
	EffectBase *effectMediumBossDown[8];
	EffectBase *effectBossDown[4];

};

#define EFFECT				EffectManager::EffectManagerInctance()
