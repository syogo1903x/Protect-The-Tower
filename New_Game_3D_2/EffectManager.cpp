#include "Common.h"

EffectManager::EffectManager()
{
	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(2000) < 0)
	{
		DxLib_End();
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

}

EffectManager::~EffectManager()
{
	Release();
}

// ������
void EffectManager::Init()
{
	// �U���q�b�g�G�t�F�N�g
	effect[PLAYER_HIT] = new EffectHit();
	effect[BOSS_HIT] = new EffectHit();
	effect[BOSS_HIT_2] = new EffectHit();
	effect[BOSS_HIT_3] = new EffectHit();
	effect[BOSS_HIT_4] = new EffectHit();
	// �W�����v�G�t�F�N�g
	effect[PLAYER_JUMP] = new EffectJump();
	// �e�e�G�t�F�N�g
	effect[PLAYER_BULLET] = new EffectBullet();
	// ���{�X�G�t�F�N�g
	effect[MEDIUM_APPEAR] = new EffectAppearMedium();
	// �{�X�o���G�t�F�N�g
	effect[BOSS_APPEAR] = new EffectAppearBoss();


	// ���U���G�t�F�N�g	
	for (int i = 0; i < 50; i++)
	{
		effectFire[i] = new EffectFire();
	}

	// �^���[�̃q�b�g���G�t�F�N�g
	effectTowerHit = new EffectTowerHit();
	// �^���[�̏I�����G�t�F�N�g
	effectTowerOver = new EffectTowerOver();
	// �^���[�̃_�E�����G�t�F�N�g
	effectTowerDown = new EffectTowerDown();


	// �K�E�Z�G�t�F�N�g
	effectDeathBlow[UKON] = new EffectDeathBlow_Ukon();
	effectDeathBlow[RUBY] = new EffectDeathBlow_Ruby();
	effectDeathBlow[CHINAMI] = new EffectDeathBlow_Chinami();
	effectDeathBlow[INU] = new EffectDeathBlow_Inu();
	effectDeathBlow[KARASU] = new EffectDeathBlow_Karasu();
	effectUseDeathBlow = new EffectDeathBlow();

	// �_�E���G�t�F�N�g
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



	// �K�E�Z�G�t�F�N�g ������
	for (int i = 0; i < 5; i++)
	{
		effectDeathBlow[i]->EffectInit();
	}
	effectUseDeathBlow->EffectInit();

	// �U���q�b�g�G�t�F�N�g ������
	effect[PLAYER_HIT]->EffectInit();
	effect[BOSS_HIT]->EffectInit();
	effect[BOSS_HIT_2]->EffectInit();
	effect[BOSS_HIT_3]->EffectInit();
	effect[BOSS_HIT_4]->EffectInit();
	// �W�����v�G�t�F�N�g ������
	effect[PLAYER_JUMP]->EffectInit();
	// �e�e�G�t�F�N�g ������
	effect[PLAYER_BULLET]->EffectInit();
	// ���{�X�G�t�F�N�g ������
	effect[MEDIUM_APPEAR]->EffectInit();
	// �{�X�o���G�t�F�N�g ������
	effect[BOSS_APPEAR]->EffectInit();


	// ���U���G�t�F�N�g ������	
	for (int i = 0; i < 50; i++)
	{
		effectFire[i]->EffectInit();
	}

	// �^���[�̃q�b�g���G�t�F�N�g ������
	effectTowerHit->EffectInit();
	// �^���[�̏I�����G�t�F�N�g ������
	effectTowerOver->EffectInit();
	// �^���[�̃_�E�����G�t�F�N�g
	effectTowerDown->EffectInit();

}

void EffectManager::Update()
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();
}

void EffectManager::UpdatePlayer(CharacterBase *_player)
{
	// �K�E�Z
	effectUseDeathBlow->UpdateCharter(_player);
	effectDeathBlow[Player::GetCharacterCount()]->UpdateCharter(_player);

	//printfDx("%d\n", Player::GetCharacterCount());

	// �v���C���[�W�����v
	effect[PLAYER_JUMP]->UpdateCharter(_player);

	// �q�b�g�G�t�F�N�g
	if (_player->GetDamage())
	{
		// �U���q�b�g
		effect[PLAYER_HIT]->UpdateCharter(_player);
	}
	else
	{
		// �U���q�b�g ������
		effect[PLAYER_HIT]->SetTime(30);
	}

	// �U���q�b�g
	//effect[PLAYER_BULLET]->Update(_player);
}

void EffectManager::UpdateWeakEnemy(Enemy * _enemy)
{

}

void EffectManager::UpdateMedium(MediumBoss * _mediumBoss)
{

}

// �q�b�g�G�t�F�N�g
void EffectManager::UpdateBoss(Boss * _boss[], int i)
{
	if (_boss[i]->GetDamage() && !_boss[i]->GetDead())
	{
		// �U���q�b�g
		effect[BOSS_HIT + i]->UpdateCharter(_boss[i]);
	}
	else
	{
		// �U���q�b�g ������
		effect[BOSS_HIT + i]->SetTime(30);
	}

}

// �{�X�̏o���G�t�F�N�g
void EffectManager::UpdateAppearBoss(Boss * _boss)
{
	effect[BOSS_APPEAR]->UpdateCharter(_boss);
}

// ���{�X�̏o���G�t�F�N�g
void EffectManager::UpdateAppearMediumBoss(MediumBoss * _mediumBoss)
{
	effect[MEDIUM_APPEAR]->UpdateCharter(_mediumBoss);
}

// �G���G�̃_�E���G�t�F�N�g
void EffectManager::UpdateDownSmallEnemy(Enemy * _enemy[], int i)
{
	effectSmallEnemyDown[i]->UpdateCharter(_enemy[i]);
}

// ���{�X�̃_�E���G�t�F�N�g
void EffectManager::UpdateDownMediumBoss(MediumBoss * _mediumBoss[], int i)
{
	effectMediumBossDown[i]->UpdateCharter(_mediumBoss[i]);
}

// �{�X�̃_�E���G�t�F�N�g
void EffectManager::UpdateDownBoss(Boss * _boss[], int i)
{
	effectBossDown[i]->UpdateCharter(_boss[i]);
}

// �f�B�t�F���X�̉��U���G�t�F�N�g
void EffectManager::UpdateFire(DefenseBase * _defense, int i)
{
	effectFire[i]->UpdateDefense(_defense);
}

// �^���[�q�b�g���G�t�F�N�g
void EffectManager::UpdateTowerHit(Tower *_tower)
{
	effectTowerHit->UpdateTower(_tower);
}

// �^���[�̏I�����G�t�F�N�g
void EffectManager::UpdateTowerOver(Tower * _tower)
{
	effectTowerOver->UpdateTower(_tower);
}

// �^���[�̃_�E�����G�t�F�N�g
void EffectManager::UpdateTowerDown(Tower * _tower)
{
	effectTowerDown->UpdateTower(_tower);
}

void EffectManager::Draw()
{
	// �e�G�t�F�N�g�\��
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}

void EffectManager::Release()
{

	// ���
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
