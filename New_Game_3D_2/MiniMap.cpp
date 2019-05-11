#include "Common.h"

MiniMap::MiniMap()
{
	miniMapGraphHandle = LoadGraph("img/map.png");
	playerGraphHandle = LoadGraph("img/player.png");
	
	enemyGraphHandle[0] = LoadGraph("img/enemy1.png");
	enemyGraphHandle[1] = LoadGraph("img/enemy2.png");
	enemyGraphHandle[2] = LoadGraph("img/enemy3.png");

	enemyBackGraphHandle[0] = LoadGraph("img/enemy_1.png");
	enemyBackGraphHandle[1] = LoadGraph("img/enemy_2.png");
	enemyBackGraphHandle[2] = LoadGraph("img/enemy_3.png");

	towerGraphHandle = LoadGraph("img/tower.png");
	itemShopGraphHandle = LoadGraph("img/shop.png");
}

MiniMap::~MiniMap()
{

}

void MiniMap::Init()
{
	// �v���C���[�̈ʒu�̏�����
	playerPos = ZEROCLEAR;
	// �^���[�̏�����
	towerPos = ZEROCLEAR;

	// �G�l�~�[�̏�����
	for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
	{
		enemyPos1[i] = ZEROCLEAR;
		isEnemy1[i] = false;
	}
	// ���{�X�̏�����
	for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++)
	{
		enemyPos2[i] = ZEROCLEAR;
		isEnemy2[i] = false;
	}
	// �{�X�̏�����
	for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++)
	{
		enemyPos3[i] = ZEROCLEAR;
		isEnemy3[i] = false;
	}

	playerRota = 0.0f;
}

void MiniMap::UpdatePlayerMap(CharacterBase * _player, Tower * _tower)
{
	// �v���C���[�̈ʒu�̎擾
	playerPos = _player->GetPos();
	// �v���C���[�̉�]�̎擾
	if(SceneGame::GetStart()) playerRota = _player->GetAngle().y;
	// �^���[�ʒu�̎擾
	towerPos = _tower->GetPos();
}

void MiniMap::UpdateSmall(CharacterBase * _enemy1, int i)
{
	// �G���G���o�����Ă�����ʒu�̎擾
	if (_enemy1->GetLife() > 0 && !_enemy1->GetDead())
	{
		isEnemy1[i] = true;
		enemyPos1[i] = _enemy1->GetPos();
	}
	else
	{
		isEnemy1[i] = false;
	}
}

void MiniMap::UpdateMedium(CharacterBase * _enemy2, int i)
{
	// ���{�X���o�����Ă�����ʒu�̎擾
	if (_enemy2->GetLife() > 0 && !_enemy2->GetDead())
	{
		isEnemy2[i] = true;
		enemyPos2[i] = _enemy2->GetPos();
	}
	else
	{
		isEnemy2[i] = false;
	}
}

void MiniMap::UpdateBoss(CharacterBase * _enemy3, int i)
{
	// �{�X���o�����Ă�����ʒu�̎擾
	if (_enemy3->GetLife() > 0 && !_enemy3->GetDead())
	{
		isEnemy3[i] = true;
		enemyPos3[i] = _enemy3->GetPos();
	}
	else 
	{
		isEnemy3[i] = false;
	}
}

void MiniMap::Draw()
{
	// �~�j�}�b�v�摜
	DrawRotaGraph(MINIMAP_X, (int)MINIMAP_Y, 0.5f, 0.0f, miniMapGraphHandle, TRUE);
	// �v���C���[�摜
	DrawRotaGraph(MINIMAP_X,  (int)MINIMAP_CHARACTER_Y , 0.5f, playerRota, playerGraphHandle, TRUE);

	if (MINIMAP_Y_UP_LIMIT - playerPos.z / 2 < MINIMAP_Y_UP_LIMIT)
	{
		// �A�C�e���V���b�v�摜
		DrawRotaGraphF(MINIMAP_X + playerPos.x / 2, MINIMAP_Y_UP_LIMIT - playerPos.z / 2, 0.5f, 0.0f, itemShopGraphHandle, TRUE);
	}

	// �G���G�̉摜
	for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
	{
		// �͈͓�
		if (MINIMAP_CHARACTER_Y + enemyPos1[i].z / 2 - playerPos.z / 2 > MINIMAP_Y_DOWN_LIMIT && MINIMAP_CHARACTER_Y + enemyPos1[i].z / 2 - playerPos.z / 2 < MINIMAP_Y_UP_LIMIT &&
			MINIMAP_X - enemyPos1[i].x / 2 + playerPos.x / 2 > 50 && MINIMAP_X - enemyPos1[i].x / 2 + playerPos.x / 2 < MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MINIMAP_X - enemyPos1[i].x / 2 + playerPos.x / 2, MINIMAP_CHARACTER_Y + enemyPos1[i].z / 2 - playerPos.z / 2, 0.5f, 0.0f, enemyGraphHandle[0], TRUE);
			}
		}

		// ��
		if (MINIMAP_CHARACTER_Y + enemyPos1[i].z / 2 - playerPos.z / 2 < MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MINIMAP_X - enemyPos1[i].x / 2 + playerPos.x / 2, MINIMAP_Y_DOWN_LIMIT, 0.5f, 0.0f, enemyBackGraphHandle[0], TRUE);
			}
		}
		// ��
		else if (MINIMAP_X - enemyPos1[i].x / 2 + playerPos.x / 2 < 50)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(50, MINIMAP_CHARACTER_Y + enemyPos1[i].z / 2 - playerPos.z / 2, 0.5f, -1.5f, enemyBackGraphHandle[0], TRUE);
			}
		}
		// �E
		else if (MINIMAP_X - enemyPos1[i].x / 2 + playerPos.x / 2 > MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MINIMAP_Y_DOWN_LIMIT, MINIMAP_CHARACTER_Y + enemyPos1[i].z / 2 - playerPos.z / 2, 0.5f, 1.5f, enemyBackGraphHandle[0], TRUE);
			}
		}
	}
	// ���{�X�̉摜
	for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// �͈͓�
		if (MINIMAP_CHARACTER_Y + enemyPos2[i].z / 2 - playerPos.z / 2 > MINIMAP_Y_DOWN_LIMIT && MINIMAP_CHARACTER_Y + enemyPos2[i].z / 2 - playerPos.z / 2 < MINIMAP_Y_UP_LIMIT &&
			MINIMAP_X - enemyPos2[i].x / 2 + playerPos.x / 2 > 50 && MINIMAP_X - enemyPos2[i].x / 2 + playerPos.x / 2 < MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy2[i]) 
			{
				DrawRotaGraphF(MINIMAP_X - enemyPos2[i].x / 2 + playerPos.x / 2, MINIMAP_CHARACTER_Y + enemyPos2[i].z / 2 - playerPos.z / 2, 0.5f, 0.0f, enemyGraphHandle[1], TRUE); 
			}
		}

		// ��
		if (MINIMAP_CHARACTER_Y + enemyPos2[i].z / 2 - playerPos.z / 2 < MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy2[i]) 
			{
				DrawRotaGraphF(MINIMAP_X - enemyPos2[i].x / 2 + playerPos.x / 2, MINIMAP_Y_DOWN_LIMIT, 0.5f, 0.0f, enemyBackGraphHandle[1], TRUE); 
			}
		}
		// ��
		else if (MINIMAP_X - enemyPos2[i].x / 2 + playerPos.x / 2 < 50)
		{
			if (isEnemy2[i])
			{
				DrawRotaGraphF(50, MINIMAP_CHARACTER_Y + enemyPos2[i].z / 2 - playerPos.z / 2, 0.5f, -1.5f, enemyBackGraphHandle[1], TRUE);
			}
		}
		// �E
		else if (MINIMAP_X - enemyPos2[i].x / 2 + playerPos.x / 2 > MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy2[i])
			{
				DrawRotaGraphF(MINIMAP_Y_DOWN_LIMIT, MINIMAP_CHARACTER_Y + enemyPos2[i].z / 2 - playerPos.z / 2, 0.5f, 1.5f, enemyBackGraphHandle[1], TRUE);
			}
		}

	}
	// �{�X�̉摜
	for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++)
	{
		// �͈͓�
		if (MINIMAP_CHARACTER_Y + enemyPos3[i].z / 2 - playerPos.z / 2 > MINIMAP_Y_DOWN_LIMIT && MINIMAP_CHARACTER_Y + enemyPos3[i].z / 2 - playerPos.z / 2 < MINIMAP_Y_UP_LIMIT &&
			MINIMAP_X - enemyPos3[i].x / 2 + playerPos.x / 2 > 50 && MINIMAP_X - enemyPos3[i].x / 2 + playerPos.x / 2 < MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MINIMAP_X - enemyPos3[i].x / 2 + playerPos.x / 2, MINIMAP_CHARACTER_Y + enemyPos3[i].z / 2 - playerPos.z / 2, 0.5f, 0.0f, enemyGraphHandle[2], TRUE);
			}
		}

		// ��
		if (MINIMAP_CHARACTER_Y + enemyPos3[i].z / 2 - playerPos.z / 2 < MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MINIMAP_X - enemyPos3[i].x / 2 + playerPos.x / 2, MINIMAP_Y_DOWN_LIMIT, 0.5f, 0.0f, enemyBackGraphHandle[2], TRUE);
			}
		}
		// ��
		else if (MINIMAP_X - enemyPos3[i].x / 2 + playerPos.x / 2 < 50)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(50, MINIMAP_CHARACTER_Y + enemyPos3[i].z / 2 - playerPos.z / 2, 0.5f, -1.5f, enemyBackGraphHandle[2], TRUE);
			}
		}
		// �E
		else if (MINIMAP_X - enemyPos3[i].x / 2 + playerPos.x / 2 > MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MINIMAP_Y_DOWN_LIMIT, MINIMAP_CHARACTER_Y + enemyPos3[i].z / 2 - playerPos.z / 2, 0.5f, 1.5f, enemyBackGraphHandle[2], TRUE);
			}
		}

	}

	if (MINIMAP_CHARACTER_Y + towerPos.z / 2 - playerPos.z / 2 < 650)
	{
		// �^���[�̉摜
		DrawRotaGraphF(MINIMAP_X - towerPos.x + playerPos.x / 2, MINIMAP_CHARACTER_Y + towerPos.z / 2 - playerPos.z / 2, 0.2f, 0.0f, towerGraphHandle, TRUE);
	}
}

void MiniMap::MenuDraw()
{
	// �~�j�}�b�v�摜
	DrawRotaGraph(MENU_MINIMAP_X, (int)MINIMAP_Y, 0.8f, 0.0f, miniMapGraphHandle, TRUE);
	// �v���C���[�摜
	DrawRotaGraph(MENU_MINIMAP_X, (int)MINIMAP_CHARACTER_Y, 0.8f, playerRota, playerGraphHandle, TRUE);

	if (MINIMAP_Y_UP_LIMIT - playerPos.z / 1.5f < MINIMAP_Y_UP_LIMIT)
	{
		// �A�C�e���V���b�v�摜
		DrawRotaGraphF(MENU_MINIMAP_X + playerPos.x / 1.5f, MINIMAP_Y_UP_LIMIT - playerPos.z / 1.5f, 0.8f, 0.0f, itemShopGraphHandle, TRUE);
	}

	// �G���G�̉摜
	for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
	{
		// �͈͓�
		if (MINIMAP_CHARACTER_Y + enemyPos1[i].z / 1.5f - playerPos.z / 1.5f > MINIMAP_Y_DOWN_LIMIT && MINIMAP_CHARACTER_Y + enemyPos1[i].z / 1.5f - playerPos.z / 1.5f < MINIMAP_Y_UP_LIMIT &&
			MENU_MINIMAP_X - enemyPos1[i].x / 1.5f + playerPos.x / 1.5f > MENU_MINIMAP_X_DOWN_LIMIT && MENU_MINIMAP_X - enemyPos1[i].x / 1.5f + playerPos.x / 1.5f < MENU_MINIMAP_X_UP_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X - enemyPos1[i].x / 1.5f + playerPos.x / 1.5f, MINIMAP_CHARACTER_Y + enemyPos1[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, 0.0f, enemyGraphHandle[0], TRUE);
			}
		}

		// ��
		if (MINIMAP_CHARACTER_Y + enemyPos1[i].z / 1.5f - playerPos.z / 1.5f < MENU_MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X - enemyPos1[i].x / 1.5f + playerPos.x / 1.5f, MENU_MINIMAP_Y_DOWN_LIMIT, 0.8f, 0.0f, enemyBackGraphHandle[0], TRUE);
			}
		}
		// ��
		else if (MENU_MINIMAP_X - enemyPos1[i].x / 1.5f + playerPos.x / 1.5f < MENU_MINIMAP_X_DOWN_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X_DOWN_LIMIT, MINIMAP_CHARACTER_Y + enemyPos1[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, -1.5f, enemyBackGraphHandle[0], TRUE);
			}
		}
		// �E
		else if (MENU_MINIMAP_X - enemyPos1[i].x / 1.5f + playerPos.x / 1.5f > MENU_MINIMAP_X_UP_LIMIT)
		{
			if (isEnemy1[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X_UP_LIMIT, MINIMAP_CHARACTER_Y + enemyPos1[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, 1.5f, enemyBackGraphHandle[0], TRUE);
			}
		}
	}
	// ���{�X�̉摜
	for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++)
	{
		// �͈͓�
		if (MINIMAP_CHARACTER_Y + enemyPos2[i].z / 1.5f - playerPos.z / 1.5f > MINIMAP_Y_DOWN_LIMIT && MINIMAP_CHARACTER_Y + enemyPos2[i].z / 1.5f - playerPos.z / 1.5f < MINIMAP_Y_UP_LIMIT &&
			MENU_MINIMAP_X - enemyPos2[i].x / 1.5f + playerPos.x / 1.5f > MENU_MINIMAP_X_DOWN_LIMIT && MENU_MINIMAP_X - enemyPos2[i].x / 1.5f + playerPos.x / 1.5f < MENU_MINIMAP_X_UP_LIMIT)
		{
			if (isEnemy2[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X - enemyPos2[i].x / 1.5f + playerPos.x / 1.5f, MINIMAP_CHARACTER_Y + enemyPos2[i].z / 1.5f - playerPos.z / 1.5f, 0.5f, 0.0f, enemyGraphHandle[1], TRUE);
			}
		}

		// ��
		if (MINIMAP_CHARACTER_Y + enemyPos2[i].z / 1.5f - playerPos.z / 1.5f < MENU_MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy2[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X - enemyPos2[i].x / 1.5f + playerPos.x / 1.5f, MENU_MINIMAP_Y_DOWN_LIMIT, 0.8f, 0.0f, enemyBackGraphHandle[1], TRUE);
			}
		}
		// ��
		else if (MENU_MINIMAP_X - enemyPos2[i].x / 1.5f + playerPos.x / 1.5f < MENU_MINIMAP_X_DOWN_LIMIT)
		{
			if (isEnemy2[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X_DOWN_LIMIT, MINIMAP_CHARACTER_Y + enemyPos2[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, -1.5f, enemyBackGraphHandle[1], TRUE);
			}
		}
		// �E
		else if (MENU_MINIMAP_X - enemyPos2[i].x / 1.5f + playerPos.x / 1.5f > MENU_MINIMAP_X_UP_LIMIT)
		{
			if (isEnemy2[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X_UP_LIMIT, MINIMAP_CHARACTER_Y + enemyPos2[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, 1.5f, enemyBackGraphHandle[1], TRUE);
			}
		}

	}
	// �{�X�̉摜
	for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++)
	{
		// �͈͓�
		if (MINIMAP_CHARACTER_Y + enemyPos3[i].z / 1.5f - playerPos.z / 1.5f > MINIMAP_Y_DOWN_LIMIT && MINIMAP_CHARACTER_Y + enemyPos3[i].z / 1.5f - playerPos.z / 1.5f < MINIMAP_Y_UP_LIMIT &&
			MENU_MINIMAP_X - enemyPos3[i].x / 1.5f + playerPos.x / 1.5f > MENU_MINIMAP_X_DOWN_LIMIT && MENU_MINIMAP_X - enemyPos3[i].x / 1.5f + playerPos.x / 1.5f < MENU_MINIMAP_X_UP_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X - enemyPos3[i].x / 1.5f + playerPos.x / 1.5f, MINIMAP_CHARACTER_Y + enemyPos3[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, 0.0f, enemyGraphHandle[2], TRUE);
			}
		}

		// ��
		if (MINIMAP_CHARACTER_Y + enemyPos3[i].z / 1.5f - playerPos.z / 1.5f < MENU_MINIMAP_Y_DOWN_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X - enemyPos3[i].x / 1.5f + playerPos.x / 1.5f, MENU_MINIMAP_Y_DOWN_LIMIT, 0.8f, 0.0f, enemyBackGraphHandle[2], TRUE);
			}
		}
		// ��
		else if (MENU_MINIMAP_X - enemyPos3[i].x / 1.5f + playerPos.x / 1.5f < MENU_MINIMAP_X_DOWN_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X_DOWN_LIMIT, MINIMAP_CHARACTER_Y + enemyPos3[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, -1.5f, enemyBackGraphHandle[2], TRUE);
			}
		}
		// �E
		else if (MENU_MINIMAP_X - enemyPos3[i].x / 1.5f + playerPos.x / 1.5f > MENU_MINIMAP_X_UP_LIMIT)
		{
			if (isEnemy3[i])
			{
				DrawRotaGraphF(MENU_MINIMAP_X_UP_LIMIT, MINIMAP_CHARACTER_Y + enemyPos3[i].z / 1.5f - playerPos.z / 1.5f, 0.8f, 1.5f, enemyBackGraphHandle[2], TRUE);
			}
		}

	}

	if (MINIMAP_CHARACTER_Y + towerPos.z / 1.5f - playerPos.z / 1.5f < MENU_MINIMAP_Y_UP_LIMIT)
	{
		// �^���[�̉摜
		DrawRotaGraphF(MENU_MINIMAP_X - towerPos.x + playerPos.x / 1.5f, MINIMAP_CHARACTER_Y + towerPos.z / 1.5f - playerPos.z / 1.5f, 0.4f, 0.0f, towerGraphHandle, TRUE);
	}
}

// ���
void MiniMap::Release()
{
	DeleteGraph(miniMapGraphHandle);
	miniMapGraphHandle = NULL;

	DeleteGraph(playerGraphHandle);
	playerGraphHandle = NULL;

	DeleteGraph(towerGraphHandle);
	towerGraphHandle = NULL;

	DeleteGraph(itemShopGraphHandle);
	itemShopGraphHandle = NULL;

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(enemyGraphHandle[i]);
		enemyGraphHandle[i] = NULL;

		DeleteGraph(enemyBackGraphHandle[i]);
		enemyBackGraphHandle[i] = NULL;
	}
}
