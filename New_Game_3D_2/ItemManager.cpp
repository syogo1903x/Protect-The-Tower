#include "ItemManager.h"

ItemManager::ItemManager()
{
	// �R�C���Ɖ񕜂̃��f���̓ǂݍ���
	coinModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ITEM_COIN));
	recoveryModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ITEM_RECOVERY));
}

ItemManager::~ItemManager()
{

}

// ������
void ItemManager::Init()
{
	// �G���G�p�A�C�e��
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// ��
		itemSmallEnemyRecovery[i] = new Recovery();
		itemSmallEnemyRecovery[i]->Init(recoveryModelHandle);
		// ����
		itemSmallEnemyCoin[i] = new Coin();
		itemSmallEnemyCoin[i]->Init(coinModelHandle);

		// �G���G�p�J�E���g ������
		smallEnemyItemCount[i] = 0;
	}

	// ���{�X�G�p�A�C�e��
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// ��
		itemMediumBossRecovery[i] = new Recovery();
		itemMediumBossRecovery[i]->Init(recoveryModelHandle);
		// ����
		itemMediumBossCoin[i] = new Coin();
		itemMediumBossCoin[i]->Init(coinModelHandle);

		// ���{�X�p�J�E���g ������
		mediumBossItemCount[i] = 0;

	}

	// �{�X�G�p�A�C�e��
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// ��
		itemBossRecovery[i] = new Recovery();
		itemBossRecovery[i]->Init(recoveryModelHandle);
		// ����
		itemBossCoin[i] = new Coin();
		itemBossCoin[i]->Init(coinModelHandle);

		// �{�X�p�J�E���g ������
		bossItemCount[i] = 0;
	}

}

// �G���G�̍X�V
void ItemManager::UpdateSmallEnemy(CharacterBase *_enemy, int i)
{
	// �G���G���o�����Ă���΃J�E���g�J�n
	if (_enemy->GetLife() > 0) { smallEnemyItemCount[i]++; }

	// �Ƃ肠�����o���o���\��
	if (smallEnemyItemCount[i] % 2 == 0)
	{
		itemSmallEnemyCoin[i]->Update(_enemy);
	}
	else
	{
		itemSmallEnemyRecovery[i]->Update(_enemy);
	}
}

// ���{�X�̍X�V
void ItemManager::UpdateMediumBoss(CharacterBase *_enemy, int i)
{
	// ���{�X���o�����Ă���΃J�E���g�J�n
	if (_enemy->GetLife() > 0) { mediumBossItemCount[i]++; }

	// �Ƃ肠�����o���o���\��
	if (mediumBossItemCount[i] % 2 == 0)
	{
		itemMediumBossCoin[i]->Update(_enemy);
	}
	else
	{
		itemMediumBossRecovery[i]->Update(_enemy);
	}
}

// �{�X�̍X�V
void ItemManager::UpdateBoss(CharacterBase *_enemy, int i)
{
	// �{�X���o�����Ă���΃J�E���g�J�n
	if (_enemy->GetLife() > 0) { bossItemCount[i]++; }

	// �Ƃ肠�����o���o���\��
	if (bossItemCount[i] % 2 == 0)
	{
		itemBossCoin[i]->Update(_enemy);
	}
	else
	{
		itemBossRecovery[i]->Update(_enemy);
	}
}

// �v���C���[�̍X�V
void ItemManager::UpdatePlayer(CharacterBase * _player)
{
	// �G���I
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// ��
		itemSmallEnemyRecovery[i]->UpdatePlayerToItem(_player);
		// ����
		itemSmallEnemyCoin[i]->UpdatePlayerToItem(_player);
	}
	
	// ���{�X�G�p�A�C�e��
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// ��
		itemMediumBossRecovery[i]->UpdatePlayerToItem(_player);
		// ����
		itemMediumBossCoin[i]->UpdatePlayerToItem(_player);
	}

	// �{�X�G�p�A�C�e��
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// ��
		itemBossRecovery[i]->UpdatePlayerToItem(_player);
		// ����
		itemBossCoin[i]->UpdatePlayerToItem(_player);
	}
}

// �`��
void ItemManager::Draw()
{
	// �G���I
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// ��
		itemSmallEnemyRecovery[i]->Draw();
		// ����
		itemSmallEnemyCoin[i]->Draw();
	}

	// ���{�X�G�p�A�C�e��
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// ��
		itemMediumBossRecovery[i]->Draw();
		// ����
		itemMediumBossCoin[i]->Draw();
	}

	// �{�X�G�p�A�C�e��
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// ��
		itemBossRecovery[i]->Draw();
		// ����
		itemBossCoin[i]->Draw();
	}
}

// ���
void ItemManager::Release()
{
	// �G���G�p�A�C�e��
	for (int i = 0; i < SMALL_ENEMY_ITEM_MAX; i++)
	{
		// ��
		itemSmallEnemyRecovery[i]->Release();
		delete(itemSmallEnemyRecovery[i]);
		itemSmallEnemyRecovery[i] = NULL;
		// ����
		itemSmallEnemyCoin[i]->Release();
		delete(itemSmallEnemyCoin[i]);
		itemSmallEnemyCoin[i] = NULL;
	}

	// ���{�X�G�p�A�C�e��
	for (int i = 0; i < MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// ��
		itemMediumBossRecovery[i]->Release();
		delete(itemMediumBossRecovery[i]);
		itemMediumBossRecovery[i] = NULL;
		// ����
		itemMediumBossCoin[i]->Release();
		delete(itemMediumBossCoin[i]);
		itemMediumBossCoin[i] = NULL;
	}

	// �{�X�G�p�A�C�e��
	for (int i = 0; i < BOSS_ITEM_MAX; i++)
	{
		// ��
		itemBossRecovery[i]->Release();
		delete(itemBossRecovery[i]);
		itemBossRecovery[i] = NULL;
		// ����
		itemBossCoin[i]->Release();
		delete(itemBossCoin[i]);
		itemBossCoin[i] = NULL;
	}

	// ���f���̍폜
	MV1DeleteModel(coinModelHandle);
	coinModelHandle = NULL;

	MV1DeleteModel(recoveryModelHandle);
	recoveryModelHandle = NULL;
}
