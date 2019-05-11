#include "EnemyManager.h"

int EnemyManager::enemyCount;

// �R���X�g���N�^
EnemyManager::EnemyManager()
{
	// ���f���̓��ꍞ��
	modelHandle[0] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ENEMY_MEDIUM));
	modelHandle[1] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ENEMY_SMALL));
	modelHandle[2] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ENEMY_BOSS));
}

// �f�X�g���N�^
EnemyManager::~EnemyManager()
{

}

// �G�l�~�[������
void EnemyManager::CreateEnemy()
{
	// �����_��������
	srand((unsigned int)time(NULL));

	// �G�J�E���g������
	enemyCount = 0;
	enemyEmergenceCount = 0;
	count = 0;

	// ���{�X�@������
	for (int i = 0; i < 8; i++)
	{
		medium[i] = new MediumBoss();
		notMedium.push_back(medium[i]);
	}

	// �G���L����
	for (int i = 0; i < 20; i++)
	{
		enemy[i] = new Enemy();
		notEnemy.push_back(enemy[i]);
	}

	// �{�X�̏�����
	for (int i = 0; i < 4; i++)
	{
		boss[i] = new Boss();
		notBoss.push_back(boss[i]);
	}


	// ���{�X ���g�p���X�g�o�^
	if (!notMedium.empty())
	{
		for (notMediumItr = notMedium.begin(); notMediumItr != notMedium.end(); notMediumItr++)
		{
			(*notMediumItr)->SetPos(VGet(-300 + (float)(rand() % 500), 5, -400));
			(*notMediumItr)->Init(modelHandle[0]);
			(*notMediumItr)->SetColor(1.0f, 1.0f, 1.0f);
		}
	}

	// �U�R�G ���g�p���X�g�o�^
	if (!notEnemy.empty())
	{
		for (notEnemyItr = notEnemy.begin(); notEnemyItr != notEnemy.end(); notEnemyItr++)
		{
			(*notEnemyItr)->SetPos(VGet(-300 + (float)(rand() % 600), 5, -300));
			(*notEnemyItr)->Init(modelHandle[1]);
			MV1SetDifColorScale((*notEnemyItr)->GetModel(), GetColorF(0.1f, 0.1f, 0.1f, 1.0f));
		}
	}

	// �{�X ���g�p���X�g�o�^
	if (!notBoss.empty())
	{
		for (notBossItr = notBoss.begin(); notBossItr != notBoss.end(); notBossItr++)
		{
			(*notBossItr)->SetPos(VGet(-300 + (float)(rand() % 600), 7, -300));
			(*notBossItr)->Init(modelHandle[2]);
			MV1SetScale((*notBossItr)->GetModel(), VGet(2.5f, 2.5f, 2.5f));
		}
	}
}

// �G�l�~�[�̓����蔻��X�V
void EnemyManager::EnemyManagerUpdate(CharacterBase * _player, Stage * _stage)
{

	// �Q�[�����n�܂�΃J�E���g�_�E��
	if (SceneGame::GetStart())
	{
		enemyEmergenceCount++;
	}

	// �����蔻��
	if (!bossList.empty())
	{
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			// �{�X�ƃX�e�[�W�̓����蔻��
			HitCheck::HitCheckPlayerToGound((*bossItr), _stage, 2.5f);
			// �v���C���[�ƃ{�X�̎l�p�̓����蔻��
			if (!(*bossItr)->GetDead())
			{
				HitCheck::HitCheckCirclePlayerToOtherPlayer(_player, (*bossItr));
			}
			// �v���C���[�ƃ{�X�̉~�̓����蔻��
			if (!(*bossItr)->GetDead())
			{
				HitCheck::HitCheckBoxPlayerToBoss(_player, (*bossItr));
			}
		}
	}

	// �����蔻��
	if (!enemyList.empty())
	{
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			// �U�R�G�ƒn�ʂ̓����蔻��
			HitCheck::HitCheckPlayerToGound((*enemyItr), _stage, 1.0f);

			// �v���C���[�ƃG�l�~�[�̎l�p�̓����蔻��
			if (!(*enemyItr)->GetDead()) 
			{
				HitCheck::HitCheckBoxPlayerToOtherPlayer(_player, (*enemyItr)); 
			}

			// �v���C���[�ƃG�l�~�[�̉~�̓����蔻��
			if (!(*enemyItr)->GetDead())
			{
				HitCheck::HitCheckCirclePlayerToOtherPlayer(_player, (*enemyItr));
			}
			//HitCheck::HitCheckCirclePlayerToOtherPlayer((*enemyItr), (*enemyItr));
		}
	}

	// �����蔻��
	if (!mediumList.empty())
	{
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{

			// ���{�X�ƃX�e�[�W�̓����蔻��
			HitCheck::HitCheckPlayerToGound((*mediumItr), _stage, 1.0f);
			// �v���C���[�ƃG�l�~�[�̎l�p�̓����蔻��
			if (!(*mediumItr)->GetDead())
			{
				HitCheck::HitCheckBoxPlayerToOtherPlayer(_player, (*mediumItr));
			}
			// �v���C���[�ƃG�l�~�[�̉~�̓����蔻��
			if (!(*mediumItr)->GetDead())
			{
				HitCheck::HitCheckCirclePlayerToOtherPlayer(_player, (*mediumItr));
			}
		}
	}

}

// �̗͕`��
void EnemyManager::EnemyManagerDraw(CharacterBase * _player, Camera *_camera)
{

	// �U�R�G�͈͓̔��ɂ���΃U�R�G�̗̑͂�\��
	if (!enemyList.empty())
	{
		// �g�p���X�g
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			if (HitCheck::HitCheckCirclePlayerToEnemy(_player, (*enemyItr)))
			{
				if ((*enemyItr)->GetLife() > 0)
				{
					DrawLifeBoxSmallEnemy((*enemyItr), _camera);
				}
			}
		}
	}


	// ���{�X�͈͓̔��ɂ���Β��{�X�̗̑͂�\��
	if (!mediumList.empty())
	{
		// �g�p���X�g
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{
			if (HitCheck::HitCheckCirclePlayerToEnemy(_player, (*mediumItr)))
			{
				if ((*mediumItr)->GetLife() > 0)
				{
					DrawLifeBoxMediumBoss((*mediumItr), _camera);
				}
			}
		}
	}


	// �{�X�͈͓̔��ɂ���΃{�X�̗̑͂�\��
	if (!bossList.empty())
	{
		// �g�p���X�g
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			// �{�X�͈͓̔��ɂ���΃{�X�̗̑͂�\��
			if (HitCheck::HitCheckCirclePlayerToEnemy(_player, (*bossItr)))
			{
				if ((*bossItr)->GetLife() > 0)
				{
					DrawLifeBoxBoss((*bossItr), _camera);
				}
			}
		}
	}
}

// �X�V
void EnemyManager::Update(CharacterBase *_player, Camera * _camera, Tower *_tower)
{

	// ���g�p���X�g
	// �G�l�~�[�̏o���������^���[�̃E�F�[�u���Ƃɕς���
	if (enemyEmergenceCount % Tower::GetSmallEnemy() == 1)
	{
		if (!notEnemy.empty())
		{
			for (notEnemyItr = notEnemy.begin(); notEnemyItr != notEnemy.end(); notEnemyItr++)
			{
				(*notEnemyItr)->SetPos((*notEnemyItr)->GetEnemyPos());
				(*notEnemyItr)->SetEnemy();
				// ���g�p���X�g����g�p���X�g��
				enemyList.push_back(*notEnemyItr);
				notEnemy.remove(*notEnemyItr);
				break;
			}
		}
	}


	// �G�l�~�[�̏o���������^���[�̃E�F�[�u���Ƃɕς���
	if (enemyEmergenceCount % Tower::GetMediumEnemy() == 1)
	{
		// �E�F�[�u��0�ł͂Ȃ��Ƃ��ɏo��
		if (Tower::GetWave() != 0)
		{
			// ���g�p���X�g
			if (!notMedium.empty())
			{
				for (notMediumItr = notMedium.begin(); notMediumItr != notMedium.end(); notMediumItr++)
				{
					(*notMediumItr)->SetPos((*notMediumItr)->GetEnemyPos());
					(*notMediumItr)->SetMedium();
					// ���g�p���X�g����g�p���X�g��
					mediumList.push_back(*notMediumItr);
					notMedium.remove(*notMediumItr);
					break;
				}
			}
		}
	}

	// �G�l�~�[�̏o���������^���[�̃E�F�[�u���Ƃɕς���
	if (enemyEmergenceCount % Tower::GetBigEnemy() == 1)
	{
		// �E�F�[�u��1����ł���Ώo��
		if (Tower::GetWave() > 1)
		{
			// �{�X
			if (!notBoss.empty())
			{
				for (notBossItr = notBoss.begin(); notBossItr != notBoss.end(); notBossItr++)
				{
					(*notBossItr)->SetPos((*notBossItr)->GetEnemyPos());
					(*notBossItr)->SetBoss();
					// ���g�p���X�g����g�p���X�g��
					bossList.push_back(*notBossItr);
					notBoss.remove(*notBossItr);
					break;
				}
			}
		}
	}


	// �G�� �X�V
	if (!enemyList.empty())
	{
		// �g�p���X�g
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			if ((*enemyItr)->GetLife() < 0)
			{
				// �^���[�Ƀq�b�g���Ă��Ȃ�����
				if (!(*enemyItr)->GetHit())
				{
					// �v���C���[�̕K�E�Z�Q�[�W�����߂�
					_player->SetDeathBlowCount(5.f);
				}

				// �g�p���X�g���疢�g�p���X�g��
				notEnemy.push_back(*enemyItr);
				enemyList.remove(*enemyItr);
				break;
			}

			if (SceneGame::GetStart())
			{
				(*enemyItr)->EnemyUpdate(_player, _tower);
			}

			(*enemyItr)->Update(*_camera);
		}
	}

	// ���{�X �X�V
	if (!mediumList.empty())
	{
		// �g�p���X�g
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{
			// �o���G�t�F�N�g
			//if (enemyEmergenceCount % Tower::GetMediumEnemy() == 1)
			//{
			//	EFFECT.UpdateAppearMediumBoss((*mediumItr));
			//}

			if ((*mediumItr)->GetLife() < 0)
			{
				// �^���[�Ƀq�b�g���Ă��Ȃ�����
				if (!(*mediumItr)->GetHit())
				{
					// �v���C���[�̕K�E�Z�Q�[�W�����߂�
					_player->SetDeathBlowCount(10.f);
				}

				// �g�p���X�g���疢�g�p���X�g��
				notMedium.push_back(*mediumItr);
				mediumList.remove(*mediumItr);
				break;
			}

			if (SceneGame::GetStart())
			{
				(*mediumItr)->EnemyUpdate(_player, _tower);
			}

			(*mediumItr)->Update(*_camera);
		}
	}

	// �{�X�X�V
	if (!bossList.empty())
	{
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			// �o���G�t�F�N�g
			//if (enemyEmergenceCount % Tower::GetBigEnemy() == 1)
			//{
			//	EFFECT.UpdateAppearBoss((*bossItr));
			//}

			if ((*bossItr)->GetLife() < 0)
			{
				// �^���[�Ƀq�b�g���Ă��Ȃ�����
				if (!(*bossItr)->GetHit())
				{
					// �v���C���[�̕K�E�Z�Q�[�W�����߂�
					_player->SetDeathBlowCount(20.f);
				}

				// �g�p���X�g���疢�g�p���X�g��
				notBoss.push_back(*bossItr);
				bossList.remove(*bossItr);

				break;
			}

			if (SceneGame::GetStart())
			{
				(*bossItr)->EnemyUpdate(_player, _tower);
			}
			(*bossItr)->Update(*_camera);
		}
	}
}

// �`��
void EnemyManager::Draw()
{
	// ���{�X �`��
	if (!mediumList.empty())
	{
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{
			(*mediumItr)->Draw();
		}
	}

	// �G�� �`��
	if (!enemyList.empty())
	{
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			(*enemyItr)->Draw();
		}
	}

	// �{�X �X�V
	if (!bossList.empty())
	{
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			(*bossItr)->Draw();
		}
	}

	// �{�X�̃G�t�F�N�g
	for (int i = 0; i < 4; i++)
	{
		EFFECT.UpdateBoss(boss, i);
		if (!boss[i]->GetDead()) { EFFECT.UpdateDownBoss(boss, i); }
	}
	// �G���G�̃G�t�F�N�g
	for (int i = 0; i < 20; i++)
	{
		if (!enemy[i]->GetDead()) { EFFECT.UpdateDownSmallEnemy(enemy, i); }
	}
	// ���{�X�̃G�t�F�N�g
	for (int i = 0; i < 8; i++)
	{
		if (!medium[i]->GetDead()) { EFFECT.UpdateDownMediumBoss(medium, i); }
	}

}

// ���
void EnemyManager::Release()
{
	// ���{�X
	for (int i = 0; i < 8; i++)
	{
		medium[i]->Release();
		medium[i] = NULL;
		delete(medium[i]);
	}

	// �G��
	for (int i = 0; i < 20; i++)
	{
		enemy[i]->Release();
		enemy[i] = NULL;
		delete(enemy[i]);
	}

	// �{�X
	for (int i = 0; i < 4; i++)
	{
		boss[i]->Release();
		boss[i] = NULL;
		delete(boss[i]);
	}

	// �e���f���̊J��
	for (int i = 0; i < 3; i++)
	{
		MV1DeleteModel(modelHandle[i]);
		modelHandle[i] = NULL;
	}
}
