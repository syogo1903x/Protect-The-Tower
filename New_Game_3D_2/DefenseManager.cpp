#include "Common.h"

int DefenseManager::godbyeShopAnimationCount;
int DefenseManager::joinShopAnimationCount;

// �R���X�g���N�^
DefenseManager::DefenseManager()
{

	wallModelHamdel = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_WALL));
	atackBallModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_ATACKBALL));
	fireModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_FIRE));
	soldierModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_SOLDIER));


	buyObject = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_BUY));

	// ���m�̏e�e
	soldierBulletModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::BULLET_SHOT));

	mapFrameGraphHandle = LoadGraph("img/character/frame2.png");

	itemFrameGraphHandle = LoadGraph("img/frame.png");

	buyGraphHandle = LoadGraph("img/Item/buy.png");
	backGraphHandle = LoadGraph("img/Item/deru.png");

	buttonGraphHandle[0] = LoadGraph("img/button/wall.png");
	buttonGraphHandle[1] = LoadGraph("img/button/atack.png");
	buttonGraphHandle[2] = LoadGraph("img/button/fire.png");
	buttonGraphHandle[3] = LoadGraph("img/button/soldier.png");

	backGroundGraphHadle = LoadGraph("img/backGround.png");

	woodGraphHamdle = LoadGraph("img/wood.png");

	// �f�B�t�F���X�A�C�e���̉摜
	nodeGraphHandle[0] = LoadGraph("img/Item/wall.png");
	nodeGraphHandle[1] = LoadGraph("img/Item/atack.png");
	nodeGraphHandle[2] = LoadGraph("img/Item/fire.png");
	nodeGraphHandle[3] = LoadGraph("img/Item/soldier.png");

	LoadDivGraph("img/flan.png", 2, 2, 1, 32, 32, moouseGraphHandle, TRUE);
	LoadDivGraph("img/���䖋/640/pipo-curtain1.png", 10, 1, 10, 640, 480, openShopGraphHandle, TRUE);
	LoadDivGraph("img/���䖋/640/pipo-curtain2.png", 18, 1, 18, 640, 480, closeShopGraphHandle, TRUE);

	// �}�b�v�̉摜�擾
	if (SceneMenu::GetStage() == "stage/���ʘOver0.93/���ʘO.pmx") { mapGraphHandle = LoadGraph("img/map/map1.png"); }
	if (SceneMenu::GetStage() == "stage/���O�r�[�O���E���h1.05/���O�r�[�O���E���h�i�Ő��j.pmx") { mapGraphHandle = LoadGraph("img/map/map2.png"); }
	if (SceneMenu::GetStage() == "stage/���̓s���e���X�e�[�W/���̓s���e���X�e�[�W.pmx") { mapGraphHandle = LoadGraph("img/map/map3.png"); }

	// ���ʉ��擾
	se[PURCASE] = new SoundEffect("Music/SE/clearing1.mp3");
	se[CHOICE] = new SoundEffect("Music/SE/cursor10.mp3");
	se[DECISION] = new SoundEffect("Music/SE/flying_pan.mp3");
	se[INSTALLATION] = new SoundEffect("Music/SE/sword-clash1.mp3");
	se[CANSEL] = new SoundEffect("Music/SE/cancel6.mp3");
	se[ENTRYSHOP] = new SoundEffect("Music/SE/key-drop1.mp3");
	se[CALL_ENTRY] = new SoundEffect("Music/SE/nyuten.mp3");
	se[CALL_BYE] = new SoundEffect("Music/SE/goodBye.mp3");

	openShopAnimationCount = 0;
	closeShopAnimationCount = 0;
	godbyeShopAnimationCount = 0;
	joinShopAnimationCount = 0;
	isShopEntry = false;

	// �����p�摜
	descriptionGraphHandle[0] = LoadGraph("img/Description_3.png");
	descriptionGraphHandle[1] = LoadGraph("img/Description_4.png");
	// 
	LoadDivGraph("img/number.png", 10, 10, 1, 64, 64, numberGraphHandle, TRUE);
	// 
	moneyGraphHandle = LoadGraph("img/money.png");


	descriptionCount = 0;
	isDescription = false;

	arrowModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_ARROW));

	MV1SetScale(arrowModelHandle, VGet(10, 10, 10));
	//MV1SetDifColorScale(arrowModelHandle, GetColorF(255, 255, 255, 255));
	mouseSpeed = 0;
}

// �f�X�g���N�^
DefenseManager::~DefenseManager()
{

}

// ������
void DefenseManager::Init()
{

	// �Ǘp���X�g������
	DefenseWall *defenseWall = new DefenseWall(wallModelHamdel);
	notDefenseWallList.push_back(defenseWall);
	// �U���{�[���p���X�g������
	DefenseAtackBall *defenseAtackBall = new DefenseAtackBall(atackBallModelHandle);
	notDefenseAtackBallList.push_back(defenseAtackBall);
	// ���U���p���X�g������
	DefenseFire *defenseFire = new DefenseFire(fireModelHandle);
	notDefenseFireList.push_back(defenseFire);
	// ���m�U���p�ϐ�
	DefenseSoldier *defenseSoldier = new DefenseSoldier(soldierModelHandle);
	notDefenseSoldierList.push_back(defenseSoldier);
	

	// �� ���g�p���X�g�o�^
	if (!notDefenseWallList.empty())
	{
		for (notDefenseWallIter = notDefenseWallList.begin(); notDefenseWallIter != notDefenseWallList.end(); notDefenseWallIter++)
		{
			(*notDefenseWallIter)->Init();
			(*notDefenseWallIter)->SetRotain(ZEROCLEAR);
		}
	}

	// �U���{�[�� ���g�p���X�g�o�^
	if (!notDefenseAtackBallList.empty())
	{
		for (notDefenseAtackBallIter = notDefenseAtackBallList.begin(); notDefenseAtackBallIter != notDefenseAtackBallList.end(); notDefenseAtackBallIter++)
		{
			(*notDefenseAtackBallIter)->Init();
		}
	}

	// ���U�� ���g�p���X�g�o�^
	if (!notDefenseFireList.empty())
	{
		for (notDefenseFireIter = notDefenseFireList.begin(); notDefenseFireIter != notDefenseFireList.end(); notDefenseFireIter++)
		{
			(*notDefenseFireIter)->Init();
		}
	}

	// ���m�U�� ���g�p���X�g�o�^
	if (!notDefenseSoldierList.empty())
	{
		for (notDefenseSoldierIter = notDefenseSoldierList.begin(); notDefenseSoldierIter != notDefenseSoldierList.end(); notDefenseSoldierIter++)
		{
			(*notDefenseSoldierIter)->Init();
			(*notDefenseSoldierIter)->SetDefenseObject(soldierBulletModelHandle);
		}
	}

	// �V���b�v
	defenseBuyObject = new DefenseBuyObject(buyObject);
	defenseBuyObject->Init();

	// �e�N�X�`���ƃ��f���̈ʒu�ύX
	defenseBuyObject->SetPos(SHOP_INIT_POS);

	isDefenseShoppingMode = false;
	
	isWall = false;
	isAtackBall = false;
	isFire = false;
	isSoldier = false;

	for (int i = 0; i < SHOP_LINE; i++)
	{
		for (int j = 0; j < SHOP_COLUMN; j++)
		{
			isNodeFree[i][j] = false;
			isWallNode[i][j] = false;
			isAtackBallNode[i][j] = false;
			isFireNode[i][j] = false;
			isSoldierNode[i][j] = false;
		}
	}

	wallSizeCount = 0;
	atackBallSizeCount = 0;
	fireSizeCount = 0;
	soldierSizeCount = 0;
	isChangeControlor = true;
	itemNumber = 0;
}

// �X�V
void DefenseManager::Update(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// �V���b�v���ʉ���~
	se[CALL_BYE]->StopSoundEffect();
	// �V���b�v���X�ޓX�̃t�F�[�h ������
	openShopAnimationCount = 0;
	closeShopAnimationCount = 0;

	// ����
	possessionMoney = _player->GetMoney();

	// �V���b�s���O�I�u�W�F�N�g�ƃv���C���[�̓����蔻��
	if (HitCheck::HitCheckBoxPlayerToBuyItemObject(_player, defenseBuyObject))
	{
		isShopEntry = true;
	}

	if (godbyeShopAnimationCount >= 17) { godbyeShopAnimationCount = 17; }
	if (joinShopAnimationCount >= 9) { joinShopAnimationCount = 9; }

	// �ǍX�V
	WallUpdate(_player, _small, _medium, _boss);
	// �U���{�[���X�V
	AttackBallUpdate(_player, _small, _medium, _boss);
	// ���U��
	FireUpdate(_player, _small, _medium, _boss);
	// ���m�U��
	SoldierUpdate(_player, _small, _medium, _boss);

	// �A�C�e���V���b�v�ƃv���C���[�̈ʒu�v�Z
	VECTOR buyObjeDir = VSub(_player->GetPos(), SHOP_INIT_POS);
	VECTOR buyObjeAngle = ZEROCLEAR;

	// ���K��
	if (VSquareSize(buyObjeDir) != 0)
	{
		buyObjeDir = VNorm(buyObjeDir);
	}

	// �����ύX
	float aimAngle = vec2Radian(&VGet(0, 0, -1), &buyObjeDir);

	// �����X�V
	buyObjeAngle.y = lerpRadian(buyObjeAngle.y, aimAngle, 1.f);

	// ���
	MV1SetPosition(arrowModelHandle, _player->GetPos());
	MV1SetRotationXYZ(arrowModelHandle, buyObjeAngle);

	// �V���b�s���O�X�V
	defenseBuyObject->Update();

}

// �`��
void DefenseManager::Draw()
{
	// ���X�� �ޓX�� �t�F�[�h
	ShopFade();

	// �Ǖ\��
	WallDraw();
	// �U���{�[���\��
	AttackBallDraw();
	// ���\��
	FireDraw();
	// ���m�\��
	SoldierDraw();
	// �V���b�s���O���[���\��
	defenseBuyObject->Draw();
}


// �V���b�v�X�V
void DefenseManager::ShopUpdate(CharacterBase *_player)
{
	DescriptionUpdate(_player);
}

// �V���b�v�\��
void DefenseManager::ShopDraw()
{
	DescriptionDraw();
}

// �V���b�v���X�ޓX�t�F�[�h
void DefenseManager::ShopFade()
{
	// ���X���t�F�[�h�C��
	joinShopAnimationCount++;

	// �ޓX���t�F�[�h�A�E�g
	if (isShopEntry)
	{
		godbyeShopAnimationCount++;
		if (godbyeShopAnimationCount >= 10)
		{
			isDefenseShoppingMode = true;
			isShopEntry = false;
		}
	}
}

// �Ǖ`��
void DefenseManager::WallDraw()
{
	// �f�B�t�F���X�p�� �\��
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			if ((*defenseWallListIter)->GetDefense()) { (*defenseWallListIter)->Draw(); }
		}
	}
}

// �U���{�[���`��
void DefenseManager::AttackBallDraw()
{
	// �f�B�t�F���X�p�A�^�b�N�{�[�� �\��
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			if ((*defenseAtackBallListIter)->GetDefense()) { (*defenseAtackBallListIter)->Draw(); }
		}
	}
}

// ���`��
void DefenseManager::FireDraw()
{

	// �f�B�t�F���X�p�� �\��
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			if ((*defenseFireListIter)->GetDefense()) { (*defenseFireListIter)->Draw(); }
		}
	}
}

// ���m�`��
void DefenseManager::SoldierDraw()
{

	// �f�B�t�F���X�p���m �\��
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			if ((*defenseSoldierListIter)->GetDefense()) { (*defenseSoldierListIter)->Draw(); }
		}
	}
}

// HP�\��
void DefenseManager::HpDraw()
{
	// �f�B���N�V���i�����C�g�̍쐬
	lightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, -1.0f));
	upLightHandle = CreateDirLightHandle(VGet(0.0f, 1.0f, 0.0f));

	// �f�B�t�F���X�p�ǂ�HP�\��
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			if ((*defenseWallListIter)->GetDefense()) { (*defenseWallListIter)->HpDraw(); }
		}
	}

	// �f�B�t�F���X�p�A�^�b�N�{�[����HP�\��
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			if ((*defenseAtackBallListIter)->GetDefense()) { (*defenseAtackBallListIter)->HpDraw(); }
		}
	}

	// �f�B�t�F���X�p����HP�\��
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			if ((*defenseFireListIter)->GetDefense()) { (*defenseFireListIter)->HpDraw(); }
			if ((*defenseFireListIter)->GetDefense()) { EFFECT.UpdateFire((*defenseFireListIter), defenseFireList.size()); }
		}
	}

	// �f�B�t�F���X�p���m��HP�\��
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			if ((*defenseSoldierListIter)->GetDefense()) { (*defenseSoldierListIter)->HpDraw(); }
		}
	}

	if (Tower::GetWaveInterval()) { MV1DrawModel(arrowModelHandle); }
	//MV1DrawModel(arrowModelHandle);

	// ���C�g�̍폜
	DeleteLightHandle(lightHandle);
	DeleteLightHandle(upLightHandle);
}

// �ǍX�V
void DefenseManager::WallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// �f�B�t�F���X�p�ǍX�V
	// �� �g�p���X�g�ɂ����
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			// �o�����Ă����
			if ((*defenseWallListIter)->GetDefense())
			{
				// �X�V
				(*defenseWallListIter)->Update();

				// �ǂ̓����蔻��
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _player, WALL_PLAYER_RANGE, 0);
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _small, WALL_SMALL_ENEMY_RANGE, WALL_SMALL_ENEMY_DAMAGE);
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _medium, WALL_MEDIUM_BOSS_RANGE, WALL_MEDIUM_BOSS_DAMAGE);
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _boss, WALL_BOSS_RANGE, WALL_BOSS_DAMAGE);
			}

			// �ǂ̑ϋv�n������Ζ��g�p���X�g�ւ̒ǉ�
			if ((*defenseWallListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseWallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseWallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isWallNode[(int)(NODE_LINE - (*defenseWallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseWallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// �ݒu���Ă��Ȃ����Ƃɂ���
				(*defenseWallListIter)->SetDefense(false);

				// �g�p���X�g���疢�g�p���X�g��
				notDefenseWallList.push_back(*defenseWallListIter);
				defenseWallList.remove(*defenseWallListIter);
				break;
			}
		}
	}
}

// �U���{�[���X�V
void DefenseManager::AttackBallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// �f�B�t�F���X�p�A�^�b�N�{�[���X�V
	// �U���{�[�� �g�p���X�g�ɂ����
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			// �o�����Ă����
			if ((*defenseAtackBallListIter)->GetDefense())
			{
				// �X�V
				(*defenseAtackBallListIter)->Update();

				// �U���{�[���Ƃ̓����蔻��
				HitCheck::HitCheckDefenseAtackBall((*defenseAtackBallListIter), _small, ATACKBALL_SMALL_ENEMY_RANGE, ATACKBALL_SMALL_ENEMY_ATACK_DAMAGE, ATACKBALL_SMALL_ENEMY_HIT_DAMAGE);
				HitCheck::HitCheckDefenseAtackBall((*defenseAtackBallListIter), _medium, ATACKBALL_MEDIUM_BOSS_RANGE, ATACKBALL_MEDIUM_BOSS_ATACK_DAMAGE, ATACKBALL_MEDIUM_BOSS_HIT_DAMAGE);
				HitCheck::HitCheckDefenseAtackBall((*defenseAtackBallListIter), _boss, ATACKBALL_BOSS_RANGE, ATACKBALL_BOSS_ATACK_DAMAGE, ATACKBALL_BOSS_HIT_DAMAGE);
			}
			// �U���{�[���̑ϋv�n������Ζ��g�p���X�g�ւ̒ǉ�
			if ((*defenseAtackBallListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseAtackBallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseAtackBallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isAtackBallNode[(int)(NODE_LINE - (*defenseAtackBallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseAtackBallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// �ݒu���Ă��Ȃ����Ƃɂ���
				(*defenseAtackBallListIter)->SetDefense(false);

				// �g�p���X�g���疢�g�p���X�g��
				notDefenseAtackBallList.push_back(*defenseAtackBallListIter);
				defenseAtackBallList.remove(*defenseAtackBallListIter);
				break;
			}
		}
	}
}

// ���X�V
void DefenseManager::FireUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// �f�B�t�F���X�p���X�V
	// ���U�� �g�p���X�g�ɂ����
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			// �o�����Ă����
			if ((*defenseFireListIter)->GetDefense())
			{
				// �X�V
				(*defenseFireListIter)->Update();

				// ���U���̓����蔻��
				HitCheck::HitCheckDefenseFire((*defenseFireListIter), _small, FIRE_SMALL_ENEMY_RANGE, FIRE_SMALL_ENEMY_ATACK_DAMAGE, FIRE_SMALL_ENEMY_HIT_DAMAGE);
				HitCheck::HitCheckDefenseFire((*defenseFireListIter), _medium, FIRE_MEDIUM_BOSS_RANGE, FIRE_MEDIUM_BOSS_ATACK_DAMAGE, FIRE_MEDIUM_BOSS_HIT_DAMAGE);
				HitCheck::HitCheckDefenseFire((*defenseFireListIter), _boss, FIRE_BOSS_RANGE, FIRE_BOSS_ATACK_DAMAGE, FIRE_BOSS_HIT_DAMAGE);
			}
			// ���U���̑ϋv�n������Ζ��g�p���X�g�ւ̒ǉ�
			if ((*defenseFireListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseFireListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseFireListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isFireNode[(int)(NODE_LINE - (*defenseFireListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseFireListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// �ݒu���Ă��Ȃ����Ƃɂ���
				(*defenseFireListIter)->SetDefense(false);
				// �g�p���X�g���疢�g�p���X�g��
				notDefenseFireList.push_back(*defenseFireListIter);
				defenseFireList.remove(*defenseFireListIter);
				break;
			}
		}
	}
}

// ���m�X�V
void DefenseManager::SoldierUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// �f�B�t�F���X�p���m�X�V
	// ���m�U�� �g�p���X�g�ɂ����
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			// �o�����Ă����
			if ((*defenseSoldierListIter)->GetDefense())
			{
				// �X�V
				(*defenseSoldierListIter)->Update();

				// ���m�U���̓����蔻��
				HitCheck::HitCheckDefenseSoldier((*defenseSoldierListIter), _small, SOLDIER_SMALL_ENEMY_RANGE, SOLDIER_SMALL_ENEMY_HIT_DAMAGE);
				HitCheck::HitCheckDefenseSoldier((*defenseSoldierListIter), _medium, SOLDIER_MEDIUM_BOSS_RANGE, SOLDIER_MEDIUM_BOSS_HIT_DAMAGE);
				HitCheck::HitCheckDefenseSoldier((*defenseSoldierListIter), _boss, SOLDIER_BOSS_RANGE, SOLDIER_BOSS_HIT_DAMAGE);

				// �͈͓����ǂ���
				if (HitCheck::HitCheckCircleEnemyToSoldier(_small, (*defenseSoldierListIter), SOLDIER_WITH_IN_RANGE))
				{
					HitCheck::HitCheckDefenseSoldierBullet((*defenseSoldierListIter), _small, SOLDIER_SMALL_ENEMY_RANGE, SOLDIER_SMALL_ENEMY_ATACK_DAMAGE);
					(*defenseSoldierListIter)->SetTargetEnemy(_small->GetPos());
					(*defenseSoldierListIter)->SetAngleSpeed(0.2f);
				}
				else if (HitCheck::HitCheckCircleEnemyToSoldier(_medium, (*defenseSoldierListIter), SOLDIER_WITH_IN_RANGE))
				{
					HitCheck::HitCheckDefenseSoldierBullet((*defenseSoldierListIter), _medium, SOLDIER_MEDIUM_BOSS_RANGE, SOLDIER_MEDIUM_BOSS_ATACK_DAMAGE);
					(*defenseSoldierListIter)->SetTargetEnemy(_medium->GetPos());
					(*defenseSoldierListIter)->SetAngleSpeed(0.2f);
				}
				else if (HitCheck::HitCheckCircleEnemyToSoldier(_boss, (*defenseSoldierListIter), SOLDIER_WITH_IN_RANGE))
				{
					HitCheck::HitCheckDefenseSoldierBullet((*defenseSoldierListIter), _boss, SOLDIER_BOSS_RANGE, SOLDIER_BOSS_ATACK_DAMAGE);
					(*defenseSoldierListIter)->SetTargetEnemy(_boss->GetPos());
					(*defenseSoldierListIter)->SetAngleSpeed(0.2f);
				}
				else
				{
					(*defenseSoldierListIter)->SetAngleSpeed(0.f);
				}
			}
			// ���m�U���̑ϋv�n������Ζ��g�p���X�g�ւ̒ǉ�
			if ((*defenseSoldierListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseSoldierListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseSoldierListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isSoldierNode[(int)(NODE_LINE - (*defenseSoldierListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseSoldierListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// �ݒu���Ă��Ȃ����Ƃɂ���
				(*defenseSoldierListIter)->SetDefense(false);

				// �g�p���X�g���疢�g�p���X�g��
				notDefenseSoldierList.push_back(*defenseSoldierListIter);
				defenseSoldierList.remove(*defenseSoldierListIter);
				break;
			}
		}
	}
}

// �����X�V
void DefenseManager::DescriptionUpdate(CharacterBase *_player)
{
	// �����p
	if (isDescription)
	{
		se[ENTRYSHOP]->OnePlaySoundEffect();
		se[CALL_ENTRY]->OnePlaySoundEffect();

		godbyeShopAnimationCount = 0;
		joinShopAnimationCount = 0;

		animation++;
		openShopAnimationCount++;

		// �v���C���[�̏������̕ύX�V
		possessionMoney = _player->GetMoney();

		// �f�o�b�N�p �������߂錸�炷
		//if (KEY_INPUT.GetKey(KEY_INPUT_O)) _player->SetMoney(100);
		//if (KEY_INPUT.GetKey(KEY_INPUT_P)) _player->SetMoney(-100);

		bool isMouse = isChangeControlor && MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT);
		bool isControl = !isChangeControlor && PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A);


		// �����蔻����ɂ����Ă��p�b�h�̎��͈ړ���x������
		if ((SCREEN_X / 2.5f - 35) - 17.5f < mouseX && (SCREEN_X / 2.5f + 350) + 17.5f > mouseX &&
			(SCREEN_Y / 1.8f - 17) - 17.5f < mouseY && (SCREEN_Y / 1.8f + 175) + 17.5f > mouseY)
		{
			// �}�E�X�̑��x��������
			mouseSpeed = 10;
		}
		else
		{
			// �}�E�X�̑��x��������
			mouseSpeed = 0;
		}

		// �}�E�X�̈ʒu�擾
		if (isChangeControlor)
		{
			GetMousePoint(&mouseX, &mouseY);
			// 
			if (PAD_INPUT.GetPadInput("1P").ThumbLX <= -STICK_LEAN ||
				PAD_INPUT.GetPadInput("1P").ThumbLX >= STICK_LEAN ||
				PAD_INPUT.GetPadInput("1P").ThumbLY <= -STICK_LEAN ||
				PAD_INPUT.GetPadInput("1P").ThumbLY >= STICK_LEAN)
			{
				isChangeControlor = false;
			}

		}
		else
		{
			if (PAD_INPUT.GetPadInput("1P").ThumbLX <= -STICK_LEAN) { mouseX -= MOUSE_SPEED - mouseSpeed; }
			if (PAD_INPUT.GetPadInput("1P").ThumbLX >= STICK_LEAN) { mouseX += MOUSE_SPEED - mouseSpeed; }
			if (PAD_INPUT.GetPadInput("1P").ThumbLY <= -STICK_LEAN) { mouseY += MOUSE_SPEED - mouseSpeed; }
			if (PAD_INPUT.GetPadInput("1P").ThumbLY >= STICK_LEAN) { mouseY -= MOUSE_SPEED - mouseSpeed; }

			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) ||
				MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) ||
				MOUSE_INPUT.MousePush(MOUSE_INPUT_MIDDLE))
			{
				isChangeControlor = true;
			}
		}

		// ���݂̃V���b�v�ɂ���ԍ�
		if (itemNumber == 0)
		{
			if (isMouse || isControl)
			{
				// �V���b�v�Ǖ\��
				WallShopUpdate(_player);
				// �V���b�v�U���{�[���\��
				AttackBallShopUpdate(_player);
				// �V���b�v���\��
				FireShopUpdate(_player);
				// �V���b�v���m�\��
				SoldierShopUpdate(_player);
			}

			for (int i = 0; i < SHOP_LINE; i++)
			{
				for (int j = 0; j < SHOP_COLUMN; j++)
				{
					// �����蔻��ŃA�C�e�����Ȃ���ΐݒu
					if ((SCREEN_X / 2.5f + i * 35) - 17.5f < mouseX && (SCREEN_X / 2.5f + i * 35) + 17.5f > mouseX &&
						(SCREEN_Y / 1.8f + j * 35) - 17.5f < mouseY && (SCREEN_Y / 1.8f + j * 35) + 17.5f > mouseY &&
						!isNodeFree[i][j])
					{
						//printfDx("%d : %d \n", i, j);

						if (isMouse || isControl)
						{
							// �e�h�q�A�C�e�����Ȃ����̉�
							ShopItemStopSound();

							// �ǐݒu
							WallInstallation(i, j);
							// �U���{�[���ݒu
							AttackBallInstallation(i, j);
							// ���ݒu
							FireInstallation(i, j);
							// ���m�ݒu
							SoldierInstallation(i, j);							
						}
					}
				}
			}
		}
		else
		{
			closeShopAnimationCount++;
			if (closeShopAnimationCount >= 17)
			{
				isDefenseShoppingMode = false;
				itemNumber = 0;
				se[ENTRYSHOP]->StopSoundEffect();
				se[CALL_ENTRY]->StopSoundEffect();
				// �}�E�X�̏������W���S
				SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2);
			}
		}

		// �����蔻��
		if (1420 - 150 < mouseX && 1420 + 150 > mouseX &&
			110 - 100 < mouseY && 110 + 100 > mouseY)
		{
			if (isMouse || isControl)
			{
				itemNumber = 1;
				se[CALL_BYE]->OnePlaySoundEffect();
			}
		}
	}
	else
	{
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A)) { descriptionCount++; se[DECISION]->PlaySoundEffect(); }
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B)) { descriptionCount--; se[CANSEL]->PlaySoundEffect(); }

		if (descriptionCount >= 2) { isDescription = true; }
		if (descriptionCount < 0) { descriptionCount = 0; }
	}
}

// �V���b�v�ǍX�V
void DefenseManager::WallShopUpdate(CharacterBase *_player)
{
	// �ǂ̃{�^��
	if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
		SHOP_Y_2 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + SHOP_BLANK_2 > mouseY)
	{
		// ���ʉ��Đ�
		se[CHOICE]->PlaySoundEffect();

		isWall = true;
		isAtackBall = false;
		isFire = false;
		isSoldier = false;
	}

	if (isWall)
	{
		if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
			SHOP_Y_2 + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + 150 + SHOP_BLANK_2 > mouseY)
		{
			if (_player->GetMoney() >= WALL_MONEY_CONSUMPTION)
			{
				// ���ʉ��Đ�
				se[PURCASE]->PlaySoundEffect();
				// �ǃ��X�g�������
				if (!notDefenseWallList.empty())
				{
					for (notDefenseWallIter = notDefenseWallList.begin(); notDefenseWallIter != notDefenseWallList.end(); notDefenseWallIter++)
					{
						// �ǂ̎擾�𑝂₷
						wallSizeCount++;
						// ���g�p���X�g����g�p���X�g��
						defenseWallList.push_back(*notDefenseWallIter);
						notDefenseWallList.remove(*notDefenseWallIter);
						// �����������̍폜
						_player->SetMoney(-WALL_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// �V���b�v�U���{�[���X�V
void DefenseManager::AttackBallShopUpdate(CharacterBase *_player)
{
	// �U���{�[���̃{�^��
	if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
		SHOP_Y - SHOP_BLANK_2 < mouseY && SHOP_Y + SHOP_BLANK_2 > mouseY)
	{
		// ���ʉ��Đ�
		se[CHOICE]->PlaySoundEffect();

		isAtackBall = true;
		isWall = false;
		isFire = false;
		isSoldier = false;
	}

	if (isAtackBall)
	{
		if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
			SHOP_Y + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y + 150 + SHOP_BLANK_2 > mouseY)
		{
			// �U���{�[���ł����
			if (_player->GetMoney() >= ATACKBALL_MONEY_CONSUMPTION)
			{
				// ���ʉ��Đ�
				se[PURCASE]->PlaySoundEffect();
				// 
				if (!notDefenseAtackBallList.empty())
				{
					for (notDefenseAtackBallIter = notDefenseAtackBallList.begin(); notDefenseAtackBallIter != notDefenseAtackBallList.end(); notDefenseAtackBallIter++)
					{
						// �U���{�[���̎擾�𑝂₷
						atackBallSizeCount++;
						// ���g�p���X�g����g�p���X�g��
						defenseAtackBallList.push_back(*notDefenseAtackBallIter);
						notDefenseAtackBallList.remove(*notDefenseAtackBallIter);
						// �����������̍폜
						_player->SetMoney(-ATACKBALL_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// �V���b�v���X�V
void DefenseManager::FireShopUpdate(CharacterBase *_player)
{
	// ���U���̃{�^��
	if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
		SHOP_Y_2 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + SHOP_BLANK_2 > mouseY)
	{
		// ���ʉ��Đ�
		se[CHOICE]->PlaySoundEffect();

		isAtackBall = false;
		isWall = false;
		isFire = true;
		isSoldier = false;

	}
	if (isFire)
	{
		if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
			SHOP_Y_2 + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + 150 + SHOP_BLANK_2 > mouseY)
		{
			// ���U���ł����
			if (_player->GetMoney() >= FIRE_MONEY_CONSUMPTION)
			{
				// ���ʉ��Đ�
				se[PURCASE]->PlaySoundEffect();
				// 
				if (!notDefenseFireList.empty())
				{
					for (notDefenseFireIter = notDefenseFireList.begin(); notDefenseFireIter != notDefenseFireList.end(); notDefenseFireIter++)
					{
						// ���U���̎擾�𑝂₷
						fireSizeCount++;
						// ���g�p���X�g����g�p���X�g��
						defenseFireList.push_back(*notDefenseFireIter);
						notDefenseFireList.remove(*notDefenseFireIter);
						// �����������̍폜
						_player->SetMoney(-FIRE_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// �V���b�v���m�X�V
void DefenseManager::SoldierShopUpdate(CharacterBase *_player)
{
	// ���m�U���̃{�^��
	if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
		SHOP_Y - SHOP_BLANK_2 < mouseY && SHOP_Y + SHOP_BLANK_2 > mouseY)
	{
		// ���ʉ��Đ�
		se[CHOICE]->PlaySoundEffect();
		// 
		isAtackBall = false;
		isWall = false;
		isFire = false;
		isSoldier = true;

	}
	if (isSoldier)
	{
		if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
			SHOP_Y + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y + 150 + SHOP_BLANK_2 > mouseY)
		{
			// ���m�U���ł����
			if (_player->GetMoney() >= SOLDIER_MONEY_CONSUMPTION)
			{
				// ���ʉ��Đ�
				se[PURCASE]->PlaySoundEffect();
				// 
				if (!notDefenseSoldierList.empty())
				{
					for (notDefenseSoldierIter = notDefenseSoldierList.begin(); notDefenseSoldierIter != notDefenseSoldierList.end(); notDefenseSoldierIter++)
					{
						// ���m�U���̎擾�𑝂₷
						soldierSizeCount++;
						// ���g�p���X�g����g�p���X�g��
						defenseSoldierList.push_back(*notDefenseSoldierIter);
						notDefenseSoldierList.remove(*notDefenseSoldierIter);
						// �����������̍폜
						_player->SetMoney(-SOLDIER_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// �h�q�A�C�e�����Ȃ����̉�
void DefenseManager::ShopItemStopSound()
{
	if (wallSizeCount == 0 && isWall) { se[CANSEL]->PlaySoundEffect(); }
	if (atackBallSizeCount == 0 && isAtackBall) { se[CANSEL]->PlaySoundEffect(); }
	if (fireSizeCount == 0 && isFire) { se[CANSEL]->PlaySoundEffect(); }
	if (soldierSizeCount == 0 && isSoldier) { se[CANSEL]->PlaySoundEffect(); }
}

// �ǐݒu
void DefenseManager::WallInstallation(int _row, int _col)
{
	// �ǂ̎g�p���X�g�ɂ����
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			// ���ݒu����Ă��Ȃ����
			if (!(*defenseWallListIter)->GetDefense() && isWall)
			{
				// ���ʉ��Đ�
				if (wallSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// �������炷
				wallSizeCount--;
				isWallNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// �ݒu
				(*defenseWallListIter)->SetDefense(true);
				(*defenseWallListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// �U���{�[���ݒu
void DefenseManager::AttackBallInstallation(int _row, int _col)
{
	// �U���{�[���̎g�p���X�g�ɂ����
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			// ���ݒu����Ă��Ȃ����
			if (!(*defenseAtackBallListIter)->GetDefense() && isAtackBall)
			{
				// ���ʉ��Đ�
				if (atackBallSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// �������炵
				atackBallSizeCount--;
				isAtackBallNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// �ݒu
				(*defenseAtackBallListIter)->SetDefense(true);
				(*defenseAtackBallListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// ���ݒu
void DefenseManager::FireInstallation(int _row, int _col)
{
	// ���U���̎g�p���X�g�ɂ����
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			// ���ݒu����Ă��Ȃ����
			if (!(*defenseFireListIter)->GetDefense() && isFire)
			{
				// ���ʉ��Đ�
				if (fireSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// �������炷
				fireSizeCount--;
				isFireNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// �ݒu
				(*defenseFireListIter)->SetDefense(true);
				(*defenseFireListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// ���m�ݒu
void DefenseManager::SoldierInstallation(int _row, int _col)
{
	// ���m�U���̎g�p���X�g�ɂ����
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			// ���ݒu����Ă��Ȃ����
			if (!(*defenseSoldierListIter)->GetDefense() && isSoldier)
			{
				// ���ʉ��Đ�
				if (soldierSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// �������炵
				soldierSizeCount--;
				isSoldierNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// �ݒu
				(*defenseSoldierListIter)->SetDefense(true);
				(*defenseSoldierListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// �����\��
void DefenseManager::DescriptionDraw()
{
	// �����p
	if (isDescription)
	{
		// �w�i
		DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, backGroundGraphHadle, TRUE);


		// �A�C�e���̔z�u
		if (itemNumber == 0)
		{
			DrawModiGraph(5, 5, 1300, 5, 1300, 220, 5, 220, itemFrameGraphHandle, TRUE);
			DrawRotaGraph(1440, 110, 1.0f, 0.0f, backGraphHandle, TRUE);

			DrawRotaGraph(SCREEN_X / 2, (int)(SCREEN_Y / 1.6f), 1.0f, 0.0f, woodGraphHamdle, TRUE);
			DrawRotaGraph(SCREEN_X / 2, (int)(SCREEN_Y / 1.6f), 1.0f, 0.0f, mapGraphHandle, TRUE);

			// ��10�� �c5�s	
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 0.06f, 0.0f, mapFrameGraphHandle, TRUE);

					// �����ɂ���Ε\��
					if (isWallNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[0], TRUE); }
					if (isAtackBallNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[1], TRUE); }
					if (isFireNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[2], TRUE); }
					if (isSoldierNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[3], TRUE); }

					// �����蔻��ŃA�C�e��������Όx��
					if ((SCREEN_X / 2.5f + i * 35) - 17.5f < mouseX && (SCREEN_X / 2.5f + i * 35) + 17.5f > mouseX &&
						(SCREEN_Y / 1.8f + j * 35) - 17.5f < mouseY && (SCREEN_Y / 1.8f + j * 35) + 17.5f > mouseY &&
						isNodeFree[i][j])
					{
						if (isWall && wallSizeCount > 0 ||
							isAtackBall&& atackBallSizeCount > 0 ||
							isFire && fireSizeCount > 0 ||
							isSoldier&& soldierSizeCount > 0)
						{
							SetFontSize(60);
							DrawStringF(SCREEN_X / 3, 700, "�󂢂Ă�g�ɂ����Ă�!", GetColor(0, 0, 0), GetColor(255, 255, 255));
							SetFontSize(DEFAULT_FONT_SIZE);
						}
					}
				}
			}

			// �I������Ă�����̂̕\������
			// ��
			WallDraw2D();
			// �U���{�[��
			AttackBallDraw2D();
			// ��
			FireDraw2D();
			// ���m
			SoldierDraw2D();


			if (!isWall && !isAtackBall && !isFire && !isSoldier)
			{
				// �l�i�̕\��
				SetFontSize(60);
				DrawFormatString(100, 50, GetColor(255, 255, 255), "�����������̂�I��ł�!");
				SetFontSize(DEFAULT_FONT_SIZE);
			}

			// �����̕\��
			ShopMoneyDraw();
		}

		// �}�E�X�̕ύX
		DrawGraph(mouseX, mouseY, moouseGraphHandle[animation % 2], TRUE);

		// �t�F�[�h�C�� �t�F�[�h�A�E�g�@�`��
		if (closeShopAnimationCount >= 17) { closeShopAnimationCount = 17; }
		if (openShopAnimationCount >= 9) { openShopAnimationCount = 9; }

		DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, closeShopGraphHandle[closeShopAnimationCount], TRUE);
		DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, openShopGraphHandle[openShopAnimationCount], TRUE);
	}
	else
	{
		// �����摜 �`��
		if (descriptionCount == 0) { DrawGraph(0, 0, descriptionGraphHandle[0], TRUE); }
		if (descriptionCount == 1) { DrawGraph(0, 0, descriptionGraphHandle[1], TRUE); }
	}
}

// ��2D�\��
void DefenseManager::WallDraw2D()
{
	if (isWall)
	{
		DrawBox(SHOP_X - 110, SHOP_Y_2 - 75, SHOP_X + 110, SHOP_Y_2 + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X, SHOP_Y_2 + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// �l�i�̕\��
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "�ǂ͑�����~�܂点�Ă���邼!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "���l�i��100�~");
		SetFontSize(DEFAULT_FONT_SIZE);

		// �I�𒆂̃A�C�e���\��
		if (wallSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[0], TRUE); }
	}
}

// �U���{�[��2D�\��
void DefenseManager::AttackBallDraw2D()
{
	if (isAtackBall)
	{
		DrawBox(SHOP_X - 110, SHOP_Y - 75, SHOP_X + 110, SHOP_Y + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X, SHOP_Y + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// �l�i�̕\��
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "�U���͑�����U�����Ē��˔�΂���!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "���l�i��200�~");
		SetFontSize(DEFAULT_FONT_SIZE);

		// �I�𒆂̃A�C�e���\��
		if (atackBallSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[1], TRUE); }
	}
}

// ��2D�\��
void DefenseManager::FireDraw2D()
{
	if (isFire)
	{
		DrawBox(SHOP_X_2 - 110, SHOP_Y_2 - 75, SHOP_X_2 + 110, SHOP_Y_2 + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X_2, SHOP_Y_2 + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// �l�i�̕\��
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "���͎���ɗ����G��|���Ă��邼!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "���l�i��400�~");
		SetFontSize(DEFAULT_FONT_SIZE);

		// �I�𒆂̃A�C�e���\��
		if (fireSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[2], TRUE); }
	}
}

// ���m2D�\��
void DefenseManager::SoldierDraw2D()
{
	if (isSoldier)
	{
		DrawBox(SHOP_X_2 - 110, SHOP_Y - 75, SHOP_X_2 + 110, SHOP_Y + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X_2, SHOP_Y + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// �l�i�̕\��
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "���m�͌N�ƈꏏ�ɓG�������Ă���邼!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "���l�i��500�~");
		SetFontSize(DEFAULT_FONT_SIZE);

		// �I�𒆂̃A�C�e���\��
		if (soldierSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[3], TRUE); }
	}
}

void DefenseManager::ShopMoneyDraw()
{

	DrawRotaGraph(950, 160, 0.1f, 0.0f, moneyGraphHandle, TRUE);

	// �����̐����̉摜
	if (possessionMoney == 0) { DrawRotaGraph(1000, 160, 1.f, 0.0f, numberGraphHandle[0], TRUE); }
	// �P�O�O�ȏ�
	if (possessionMoney >= 100 && possessionMoney < 1000) {
		DrawRotaGraph(1000, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney / 100], TRUE);
		DrawRotaGraph(1040, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
		DrawRotaGraph(1080, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
	}
	// �P�O�O�O�ȏ�
	if (possessionMoney >= 1000 && possessionMoney < 10000) {
		DrawRotaGraph(1000, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney / 1000], TRUE);
		DrawRotaGraph(1040, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney % 1000 / 100], TRUE);
		DrawRotaGraph(1080, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
		DrawRotaGraph(1120, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
	}
	// �P�O�O�O�O�ȏ�
	if (possessionMoney >= 10000) {
		DrawRotaGraph(1000, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney / 10000], TRUE);
		DrawRotaGraph(1040, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney % 10000 / 1000], TRUE);
		DrawRotaGraph(1080, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney % 1000 / 100], TRUE);
		DrawRotaGraph(1120, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
		DrawRotaGraph(1160, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
	}
	// �{�^���̔z�u
	DrawRotaGraph(SHOP_X, SHOP_Y_2, 1.0f, 0.f, buttonGraphHandle[0], TRUE);
	DrawRotaGraph(SHOP_X, SHOP_Y, 1.0f, 0.f, buttonGraphHandle[1], TRUE);
	DrawRotaGraph(SHOP_X_2, SHOP_Y_2, 1.0f, 0.f, buttonGraphHandle[2], TRUE);
	DrawRotaGraph(SHOP_X_2, SHOP_Y, 1.0f, 0.f, buttonGraphHandle[3], TRUE);

	// �A�C�e���̎����Ă����
	SetFontSize(60);
	DrawFormatString(SHOP_X - 50, SHOP_Y_2 - 100, GetColor(0, 0, 0), "�~ %d", wallSizeCount);
	DrawFormatString(SHOP_X - 50, SHOP_Y - 100, GetColor(0, 0, 0), "�~ %d", atackBallSizeCount);
	DrawFormatString(SHOP_X_2 - 50, SHOP_Y_2 - 100, GetColor(0, 0, 0), "�~ %d", fireSizeCount);
	DrawFormatString(SHOP_X_2 - 50, SHOP_Y - 100, GetColor(0, 0, 0), "�~ %d", soldierSizeCount);
	SetFontSize(DEFAULT_FONT_SIZE);
}

// ���
void DefenseManager::Release()
{
	// ���f��
	MV1DeleteModel(wallModelHamdel);
	wallModelHamdel = NULL;
	MV1DeleteModel(atackBallModelHandle);
	atackBallModelHandle = NULL;
	MV1DeleteModel(fireModelHandle);
	fireModelHandle = NULL;
	MV1DeleteModel(soldierModelHandle);
	soldierModelHandle = NULL;
	MV1DeleteModel(buyObject);
	buyObject = NULL;
	MV1DeleteModel(soldierBulletModelHandle);
	soldierBulletModelHandle = NULL;


	MV1DeleteModel(arrowModelHandle);
	arrowModelHandle = NULL;


	// �摜
	DeleteGraph(buyGraphHandle);
	buyGraphHandle = NULL;
	DeleteGraph(backGraphHandle);
	backGraphHandle = NULL;

	DeleteGraph(descriptionGraphHandle[0]);
	descriptionGraphHandle[0] = NULL;
	DeleteGraph(descriptionGraphHandle[1]);
	descriptionGraphHandle[1] = NULL;
	DeleteGraph(mapGraphHandle);
	mapGraphHandle = NULL;

	for (int i = 0; i < 18; i++)
	{
		DeleteGraph(closeShopGraphHandle[i]);
		closeShopGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(openShopGraphHandle[i]);
		openShopGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(buttonGraphHandle[i]);
		buttonGraphHandle[i] = NULL;

		DeleteGraph(nodeGraphHandle[i]);
		nodeGraphHandle[i] = NULL;
	}

	DeleteGraph(mapFrameGraphHandle);
	mapFrameGraphHandle = NULL;
	DeleteGraph(itemFrameGraphHandle);
	itemFrameGraphHandle = NULL;
	DeleteGraph(backGroundGraphHadle);
	backGroundGraphHadle = NULL;
	DeleteGraph(woodGraphHamdle);
	woodGraphHamdle = NULL;
	DeleteGraph(moouseGraphHandle[0]);
	moouseGraphHandle[0] = NULL;
	DeleteGraph(moouseGraphHandle[1]);
	moouseGraphHandle[1] = NULL;

	//
	defenseWallList.clear();
	notDefenseWallList.clear();
	//
	defenseAtackBallList.clear();
	notDefenseAtackBallList.clear();
	//
	defenseFireList.clear();
	notDefenseFireList.clear();
	//
	defenseSoldierList.clear();
	notDefenseSoldierList.clear();

	DeleteGraph(moneyGraphHandle);
	moneyGraphHandle = NULL;

	//
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numberGraphHandle[i]);
		numberGraphHandle[i] = NULL;
	}

	// 
	defenseBuyObject->Release();
	delete(defenseBuyObject);
	defenseBuyObject = NULL;

	// �T�E���h
	for (int i = 0; i < 5; i++)
	{
		if (se[i])
		{
			se[i]->StopSoundEffect();
			se[i]->Release();
			se[i] = NULL;
			delete(se[i]);
		}
	}
}
