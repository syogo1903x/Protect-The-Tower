#include "Common.h"

char *SceneGame::result;		// ���U���g�̏��s
bool SceneGame::isStart;		// �X�^�[�g�J�n�t���O
int SceneGame::gameTime;		// �Q�[������
bool SceneGame::isGameClear;	// �Q�[���N���A
bool SceneGame::isGameOver;		// �Q�[���I�[�o�[

SceneGame::SceneGame()
{
	// �}���`�X���b�h
	nowLoading = new NowLoad();
	// ���[�f�B���O���쐬
	//nowLoading->CreateSubThread();
	// ���[�f�B���O�������쐬
	nowLoading->SubThreadUpdate();

	// ���U���g�p���f���̊i�[
	SceneResult::CreateModel();
}

SceneGame::~SceneGame()
{
	//Release();
}

void SceneGame::Init()
{
	// �X�e�[�W������
	STAGE.Init(SceneMenu::GetStage());

	// �v���C���[������
	player = new Player();
	player->Init(SceneMenu::GetPlayer());

	// �J����������
	camera = new Camera();
	camera->Init();

	// �G�l�~�[������
	enemy = new EnemyManager();
	enemy->CreateEnemy();

	// �A�C�e���}�l�[�W���[������
	itemManager = new ItemManager();
	itemManager->Init();

	// ���[�U�[�C���^�[�t�F�[�Y������
	ui = new UI();
	ui->Init(SceneMenu::GetPlayer());

	// �^���[������
	tower = new Tower();
	tower->Init();

	// �f�B�t�F���X�}�l�[�W��������
	defenseManager = new DefenseManager;
	defenseManager->Init();

	// �~�j�}�b�v������
	miniMap = new MiniMap();
	miniMap->Init();

	// BGM�ǂݍ���
	bgm = new BackGroundMusic("Music/BGM/gameBGM.mp3");
	shopBGM = new BackGroundMusic("Music/BGM/shopBGM.mp3");

	// ���ʉ��ǂݍ���
	se[0] = new SoundEffect("Music/SE/decision2.mp3");
	se[1] = new SoundEffect("Music/SE/decision2.mp3");
	se[2] = new SoundEffect("Music/SE/decision2.mp3");
	se[3] = new SoundEffect("Music/SE/roll-finish1.mp3");
	menuSe[0] = new SoundEffect("Music/SE/cursor10.mp3");
	menuSe[1] = new SoundEffect("Music/SE/cancel2.mp3");
	menuSe[2] = new SoundEffect("Music/SE/decision9.mp3");
	menuSe[3] = new SoundEffect("Music/SE/knife-throw1.mp3");

	result = "";

	startCount = 3;

	// �����摜
	descriptionGraphHandle[0] = LoadGraph("img/Description_1.png");
	descriptionGraphHandle[1] = LoadGraph("img/Description_2.png");

	// �E�F�[�u�ƃ^�C�}�[
	waveGraphHandle = LoadGraph("img/weav.png");
	timeGraphHandle = LoadGraph("img/time.png");

	// �����̐����ƃX�^�[�g�摜
	moneyCountGraphHandle = LoadGraph("img/money_.png");
	gameStartGraphHandle  = LoadGraph("img/gameStart.png");
	// ����
	LoadDivGraph("img/number.png", 10, 10, 1, 64, 64, numberGraphHandle, TRUE);
	// �J�E���g�_�E��
	timeCountGraphHandle[0] = LoadGraph("img/1.png");
	timeCountGraphHandle[1] = LoadGraph("img/2.png");
	timeCountGraphHandle[2] = LoadGraph("img/3.png");
	// �摜
	menuGraphHandle = LoadGraph("img/gameMenu.png");
	menuFrameGraphHandle = LoadGraph("img/frame_.png");
	// �����摜
	descriptionOperationGraphHandle[0] = LoadGraph("img/Description_1_.png");
	descriptionOperationGraphHandle[1] = LoadGraph("img/Description_2_.png");
	descriptionRuleGraphHandle[0] = LoadGraph("img/Description_3_.png");
	descriptionRuleGraphHandle[1] = LoadGraph("img/Description_4_.png");
	
	descriptionTimeCount = 0;
	isDescription = false;
	isOptionDescription = false;

	// �t�F�[�h�C�� �t�F�[�h�A�E�g ������
	FADE.Init();

	// BGN�Đ�
	bgm->PlayBackGroundMusic();

	gameStartCount = 0;
	isStart = false;

	gameCount = 0;
	gameTime = 0;

	gameTimeCount = 0;
	isGameClear = false;
	isGameOver = false;
	isGameMenu = false;
	menuCount = 0;

	menuY = 260;

	isDescriptionOperation = false;
	isDescriptionRule = false;

	descriptionRuleCount = 0;
	descriptionOperationCount = 0;

	menuSizeUp = 0;
	menuSizeCount = 0;

	isPush = false;
	pushingCount = 0;
	isMenuPush = false;
	menuPushingCount = 0;
}

// �V�[���Q�[���X�V
SceneBase * SceneGame::Update()
{
	// �Q�[�����n�܂���
	if (isStart)
	{
		// ���j���[�������ꂽ��
		if (!isGameMenu)
		{
			// �G�X�P�[�v���p�b�h�̃X�^�[�g�{�^���������ꂽ��\��
			if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_START))
			{
				isGameMenu = true;
				menuSe[2]->PlaySoundEffect();
			}
			// ������
			menuCount = 0;
			descriptionRuleCount = 0;
			descriptionOperationCount = 0;
			isDescriptionOperation = false;
			isDescriptionRule = false;
			menuY = 260;
		}
		else
		{
			menuSizeCount++;

			if (menuSizeCount > 0 && menuSizeCount <= 30) { menuSizeUp += 0.001f; }
			if (menuSizeCount > 30 && menuSizeCount <= 60) { menuSizeUp -= 0.001f; }
			if (menuSizeCount > 60) { menuSizeCount = 0; }

			// 
			if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_START))
			{
				isGameMenu = false;
				menuSe[2]->PlaySoundEffect();
			}

			if (!isDescriptionRule && !isDescriptionOperation)
			{
				if (KEY_INPUT.GetKey(KEY_INPUT_W) == KEY_ON)
				{
					menuCount--;
					menuSe[0]->PlaySoundEffect();
				}

				if (KEY_INPUT.GetKey(KEY_INPUT_S) == KEY_ON )
				{
					menuCount++;
					menuSe[0]->PlaySoundEffect();
				}


				// �p�b�h�̈�u����
				if (!isPush && PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000)
				{
					isPush = true;
					menuCount--;
					menuSe[0]->PlaySoundEffect();
				}

				if (!isPush && PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000)
				{
					isPush = true;
					menuCount++;
					menuSe[0]->PlaySoundEffect();
				}

				if (isPush)
				{
					pushingCount++;
				}
				if (pushingCount >= 5)
				{
					isPush = false;
					pushingCount = 0;
				}
			}

			switch (menuCount)
			{
			case 0:
				menuY = 260;
				// �}�E�X�̍����p�b�h��A�������ꂽ��Q�[���ɖ߂�
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON )
				{
					isGameMenu = false;
					menuSe[2]->PlaySoundEffect();
				}
				break;
			case 1:
				menuY = 380;
				// �}�E�X�̍����p�b�h��A�������ꂽ�瑀������\��
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
				{
					if (!isDescriptionOperation) { menuSe[2]->PlaySoundEffect(); }
					isDescriptionOperation = true;
				}
				break;
			case 2:
				menuY = 495;
				// �}�E�X�̍����p�b�h��A�������ꂽ�烋�[�������\��
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
				{
					if (!isDescriptionRule) { menuSe[2]->PlaySoundEffect(); }
					isDescriptionRule = true;
				}
				break;
			case 3:
				menuY = 615;
				// �}�E�X�̍����p�b�h��A�������ꂽ�烁�j���[�ɖ߂�
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
				{
					FADE.TermsFadeOut_Play("Fast");
					menuSe[2]->PlaySoundEffect();
				}
				break;
			}

			// �ő�l�ݒ�
			if (menuCount < 0) { menuCount = 3; }
			if (menuCount > 3) { menuCount = 0; }
		}
	}

	// �����p
	if (isDescription)
	{
		if (!isGameMenu)
		{
			// �A�C�e���V���b�v�ɓ����Ă��Ȃ����
			if (!defenseManager->GetLetsShop())
			{
				bullet = player->GetShot().GetShot();
				itr = player->GetShot().GetItr();

				// �Q�[���J�n�܂Ŏ��Ԃ�����
				gameStartCount++;
				if (gameStartCount >= GAME_START_COUNT) { isStart = true; }
				else { SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2); }

				// �^���[�̃C���^�[�o���ł͂Ȃ��Ƃ�
				if (!Tower::GetWaveInterval())
				{
					if (isStart) { gameCount++; }

					if (gameCount % ONE_SECOND == 1) { gameTime++; }
				}

				// �v���C���[�ƒn�ʂ̓����蔻��
				HitCheck::HitCheckPlayerToGound(player, &STAGE, player->GetCharaSize());

				// �G���G
				for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
				{
					// �A�C�e���ƃv���C���[�̓����蔻��
					HitCheck::HitCheckBoxPlayerToItem(player, &itemManager->GetSmallEnemyItemRecovery(i));
					HitCheck::HitCheckBoxPlayerToCoin(player, &itemManager->GetSmallEnemyItemCoin(i));

					// �G���G�Əe�e�̓����蔻��
					if (!bullet.empty())
					{
						// ���܂��o�Ă����
						for (itr = bullet.begin(); itr != bullet.end(); itr++)
						{
							HitCheck::HitCheckGun((*itr)->pos, &enemy->GetEnemy(i), 2.f);
						}
					}
				}

				// ���{�X
				for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++)
				{
					// �A�C�e���ƃv���C���[�̓����蔻��
					HitCheck::HitCheckBoxPlayerToItem(player, &itemManager->GetMediumBossItemRecovery(i));
					HitCheck::HitCheckBoxPlayerToCoin(player, &itemManager->GetMediumBossItemCoin(i));

					// ���{�X�Əe�e�̓����蔻��
					if (!bullet.empty())
					{
						// ���܂��o�Ă����
						for (itr = bullet.begin(); itr != bullet.end(); itr++)
						{
							HitCheck::HitCheckGun((*itr)->pos, &enemy->GetMedium(i), 2.5f);
						}
					}
				}

				// �{�X
				for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++)
				{
					// �A�C�e���ƃv���C���[�̓����蔻��
					HitCheck::HitCheckBoxPlayerToItem(player, &itemManager->GetBossItemRecovery(i));
					HitCheck::HitCheckBoxPlayerToCoin(player, &itemManager->GetBossItemCoin(i));

					// �{�X�Əe�e�̓����蔻��
					if (!bullet.empty() && enemy->GetBoss(i).GetLife() != 0)
					{
						// ���܂��o�Ă����
						for (itr = bullet.begin(); itr != bullet.end(); itr++)
						{
							HitCheck::HitCheckGun((*itr)->pos, &enemy->GetBoss(i), 3.f);
						}
					}
				}

				// �}�b�v�̍X�V
				STAGE.Update();

				// �v���C���[�̍X�V
				player->Update(*camera);

				// �^���[�̍X�V
				tower->Update();

				// �G�l�~�[�̍X�V
				enemy->Update(player, camera, tower);

				// �e�G�l�~�[�̍X�V
				enemy->EnemyManagerUpdate(player, &STAGE);

				for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
				{
					for (int j = 0; j < ItemManager::MEDIUM_BOSS_ITEM_MAX; j++)
					{
						for (int k = 0; k < ItemManager::BOSS_ITEM_MAX; k++)
						{
							// �f�B�t�F���X�Ǘ�
							defenseManager->Update(player, &enemy->GetEnemy(i), &enemy->GetMedium(j), &enemy->GetBoss(k));
							// �~�j�}�b�v�Ǘ�
							miniMap->UpdatePlayerMap(player, tower);
							miniMap->UpdateSmall(&enemy->GetEnemy(i), i);
							miniMap->UpdateMedium(&enemy->GetMedium(j), j);
							miniMap->UpdateBoss(&enemy->GetBoss(k), k);
							// �K�E�Z�g�p���̓����蔻��
							if (player->GetDeathBlow())
							{
								HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(player, &enemy->GetEnemy(i));
								HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(player, &enemy->GetMedium(j));
								HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(player, &enemy->GetBoss(k));
							}
						}
					}
				}

				// �G�l�~�[�������Ă���A�C�e���X�V
				for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++) { itemManager->UpdateSmallEnemy(&enemy->GetEnemy(i), i); }
				for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++) { itemManager->UpdateMediumBoss(&enemy->GetMedium(i), i); }
				for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++) { itemManager->UpdateBoss(&enemy->GetBoss(i), i); }

				// �A�C�e��������Ă���
				itemManager->UpdatePlayer(player);

				// �J�����̍X�V
				camera->Update(player, tower);

				// �e�G�t�F�N�g�̍X�V
				EFFECT.Update();

			}
			// �A�C�e���V���b�v�ɓ����Ă����
			else
			{
				// �v���C���[�����ʒu
				player->SetPos(PLAYER_INIT_POS);
				// �J���������ʒu
				camera->CameraDirInit();
				defenseManager->ShopUpdate(player);
			}
		}
	}
	else
	{
		// ���Ԃ��Ƃɐi��
		descriptionTimeCount++;
		if (descriptionTimeCount >= 300)
		{
			isOptionDescription = true;
		}
		if (descriptionTimeCount >= 600)
		{
			isDescription = true;
		}

		// �����ꂽ��i��
		if (!isOptionDescription)
		{
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
			{
				isOptionDescription = true;
				menuSe[2]->PlaySoundEffect();
			}

		}
		else
		{
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
			{
				isDescription = true;
				menuSe[2]->PlaySoundEffect();
			}

			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B))
			{
				isOptionDescription = false;
				menuSe[1]->PlaySoundEffect();
			}
		}
	}

	// �v���C���[�̗̑͂��Ȃ��Ȃ�Ε����t���O�̃I��
	if (player->GetLife() <= GAME_OVER || tower->GetLife() <= GAME_OVER)
	{
		isGameOver = true;
	}

	// ���ԓ����؂�Ώ���
	if (gameTime >= GAME_CLEAR_COUNT)
	{
		isGameClear = true;
	}

	// �K������𖞂�������t�F�[�h�A�E�g�̊J�n
	if (tower->GetTowerCount() >= TOWER_LIFE_ZERO_COUNT/* || KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON*/)
	{
		// �����܂���
		result = "LOSE";

		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");
	}

	// �K������𖞂�������t�F�[�h�A�E�g�̊J�n
	if (Tower::GetWave() == WEAV_THREE && Tower::GetWaveIntervalCount() >= WEAV_THREE_INTERVAL /*|| KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON*/)
	{
		// �����܂���
		result = "WIN";

		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");
	}

	// �t�F�[�h�A�E�g���I���ΕύX
	if (!isGameMenu && FADE.FadeOutEnd())
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneResult;
	}

	// 
	if (isGameMenu && FADE.FadeOutEnd())
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneMenu;
	}

	// �X�e�[�W�ǂݍ��݂��G���[��f�����������x�ǂݍ���
	if (STAGE.GetFailur())
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneGame;
	}

	// ����ێ�
	return this;
}

void SceneGame::Draw()
{
	// �����p
	if (isDescription)
	{
		if (!defenseManager->GetLetsShop())
		{
			// �V���b�vBGM ��~
			shopBGM->StopBackGroundMusic();
			// BGN�Đ�
			bgm->OnePlayBackGroundMusic();

			STAGE.Draw();								// �X�e�[�W�`��
			player->Draw();								// �v���C���[�`��
			enemy->Draw();								// �G�`��
			enemy->EnemyManagerDraw(player, camera);	// �G�`��
			itemManager->Draw();						// �A�C�e���`��
			camera->Draw();								// �J�����`��
			tower->Draw();								// �^���[�`��
			defenseManager->Draw();						// �f�B�t�F���X�Ǘ�
			EFFECT.Draw();								// �G�t�F�N�g�̕\��

			// �^�C���̕\��
			if (gameStartCount >= COUNT_THREE) { startCount = 3; se[0]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_TWO) { startCount = 2;   se[1]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_ONE) { startCount = 1;   se[2]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_GAME_START) { startCount = 4; se[3]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_BLANK) startCount = 5;

			// �Q�[���J�E���g�_�E��
			if (startCount == 4) { DrawRotaGraphF(SCREEN_X / 2, 350, 1.0f,0.f, gameStartGraphHandle,TRUE); }
			if (startCount < 4 && startCount > 0) { DrawRotaGraphF(SCREEN_X / 2, 350, 1.0f, 0.f, timeCountGraphHandle[startCount - 1], TRUE); }
	
			// ���[�U�[�C���^�t�F�[�X
			miniMap->Draw();
			ui->Draw(player, tower);

			// �t�F�[�h�C��
			if (!isGameMenu) { ui->FadeDraw(); }

			// �^���[�̃E�F�[�u�N���A�摜
			tower->GameWaveString();

			// 0�b���n�߂�J�E���g
			if (gameTime == WEAV_TWO_COUNT) { gameTimeCount = -WEAV_TWO_COUNT; }
			if (gameTime == WEAV_THREE_COUNT) { gameTimeCount = -WEAV_THREE_COUNT; }

			playerMoneyCount=player->GetMoney();
			gameTimeNumber = gameTimeCount + gameTime;

			// ���Ԃ̉摜
			DrawRotaGraph(80, 35, 0.4f, 0.0f, timeGraphHandle, TRUE);

			// �����̉摜
			if (gameTimeNumber >= 10) { 
				DrawRotaGraph(195, 35, 1.0f, 0.0f, numberGraphHandle[gameTimeNumber / 10], TRUE);
				DrawRotaGraph(235, 35, 1.0f, 0.0f, numberGraphHandle[gameTimeNumber % 10], TRUE);
			}
			else
			{
				DrawRotaGraph(195, 35, 1.0f, 0.0f, numberGraphHandle[gameTimeNumber], TRUE);
			}

			// �E�F�[�u�̉摜
			DrawRotaGraph(80, 80, 0.2f, 0.0f, waveGraphHandle, TRUE);
			// �����̉摜
			DrawRotaGraph(190, 80, 1.0f,0.0f, numberGraphHandle[Tower::GetWave() + 1],TRUE);
			// �����̉摜
			DrawRotaGraph(420, 750, 0.3f, 0.0f, moneyCountGraphHandle, TRUE);
			// �����̐����̉摜
			if (playerMoneyCount == 0) { DrawRotaGraph(500, 750, 1.f, 0.0f, numberGraphHandle[0], TRUE); }
			// �P�O�O�ȏ�
			if (playerMoneyCount >= 100 && playerMoneyCount < 1000) {
			 DrawRotaGraph(500, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount / 100], TRUE); 
			 DrawRotaGraph(540, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			 DrawRotaGraph(580, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			}
			// �P�O�O�O�ȏ�
			if (playerMoneyCount >= 1000 && playerMoneyCount < 10000) {
			DrawRotaGraph(500, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount / 1000], TRUE); 
			DrawRotaGraph(540, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount % 1000 / 100], TRUE);
			DrawRotaGraph(580, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			DrawRotaGraph(620, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			}
			// �P�O�O�O�O�ȏ�
			if (playerMoneyCount >= 10000) {
			 DrawRotaGraph(500, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount / 10000], TRUE);
			 DrawRotaGraph(540, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount % 10000 / 1000], TRUE);
			 DrawRotaGraph(580, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount % 1000 / 100], TRUE);
			 DrawRotaGraph(620, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			 DrawRotaGraph(660, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			}

		}
		else
		{
			// �퓬BGM��~
			bgm->StopBackGroundMusic();
			// �V���b�v��ʕ\��
			defenseManager->ShopDraw();
			// �V���b�vBGM�Đ�
			shopBGM->OnePlayBackGroundMusic();
		}
	}
	else
	{
		// �����摜�\��
		if (!isOptionDescription) { DrawGraph(0, 0, descriptionGraphHandle[0], TRUE); }
		else { DrawGraph(0, 0, descriptionGraphHandle[1], TRUE); }
	}

	if (isGameMenu)
	{
		// �������
		if (isDescriptionOperation)
		{
			// �߂�{�^��
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B))
			{
				isDescriptionOperation = false;
				menuSe[1]->PlaySoundEffect();
			}
			// �J�E���g����
			if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON)
			{
				descriptionOperationCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// �J�E���g����
			if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON)
			{
				descriptionOperationCount++;
				menuSe[3]->PlaySoundEffect();
			}
			// �J�E���g����
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
			{
				isMenuPush = true;
				descriptionOperationCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// �J�E���g����
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
			{
				isMenuPush = true;
				descriptionOperationCount++;
				menuSe[3]->PlaySoundEffect();
			}

			if (isMenuPush)
			{
				menuPushingCount++;
			}
			if (menuPushingCount >= 5)
			{
				isMenuPush = false;
				menuPushingCount = 0;
			}

			// �ő�l�ݒ�
			if (descriptionOperationCount < 0) { descriptionOperationCount = 1; }
			if (descriptionOperationCount > 1) { descriptionOperationCount = 0; }

			// �e�l�̎��\��
			if (descriptionOperationCount == 0)
			{
				DrawGraph(0, 0, descriptionOperationGraphHandle[0], TRUE);
			}
			else
			{
				DrawGraph(0, 0, descriptionOperationGraphHandle[1], TRUE);
			}
		}

		// ���[������
		if (isDescriptionRule)
		{
			// �߂�{�^��
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B))
			{
				isDescriptionRule = false;
				menuSe[1]->PlaySoundEffect();
			}
			// �J�E���g����
			if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON)
			{
				descriptionRuleCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// �J�E���g����
			if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON )
			{
				descriptionRuleCount++;
				menuSe[3]->PlaySoundEffect();
			}
			// �J�E���g����
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
			{
				isMenuPush = true;
				descriptionRuleCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// �J�E���g����
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
			{
				isMenuPush = true;
				descriptionRuleCount++;
				menuSe[3]->PlaySoundEffect();
			}

			if (isMenuPush)
			{
				menuPushingCount++;
			}
			if (menuPushingCount >= 5)
			{
				isMenuPush = false;
				menuPushingCount = 0;
			}


			// �ő�l�ݒ�
			if (descriptionRuleCount < 0) { descriptionRuleCount = 1; }
			if (descriptionRuleCount > 1) { descriptionRuleCount = 0; }

			// �e�l�̎��\��
			if (descriptionRuleCount == 0)
			{
				DrawGraph(0, 0, descriptionRuleGraphHandle[0], TRUE);
			}
			else
			{
				DrawGraph(0, 0, descriptionRuleGraphHandle[1], TRUE);
			}
		}

		// ��������ƃ��[����������Ȃ��Ƃ������\��
		if (!isDescriptionRule && !isDescriptionOperation)
		{
			DrawGraph(0, 0, menuGraphHandle, TRUE);
			DrawRotaGraph(530, menuY, 1.0f + menuSizeUp, 0.0f, menuFrameGraphHandle, TRUE);
			miniMap->MenuDraw();
		}
	}

	// �t�F�[�h�C��
	FADE.SlowFadeIn_Play();
	// �t�F�[�h�A�E�g
	FADE.FadeOut_Play();

}

// �폜
void SceneGame::Release()
{
	// �v���C���[
	if (player)
	{
		player->Release();
		delete(player);
		player = NULL;
	}

	// �G�l�~�[
	if (enemy)
	{
		enemy->Release();
		delete(enemy);
		enemy = NULL;
	}

	// �}�b�v�폜
	//STAGE.Release();

	// �J����
	if (camera)
	{
		camera->~Camera();
		delete(camera);
		camera = NULL;
	}

	// ���[�U�C���^�[�t�F�[�X
	if (ui)
	{
		ui->Release();
		delete(ui);
		ui = NULL;
	}

	// �~�j�}�b�v
	if (miniMap)
	{
		miniMap->Release();
		delete(miniMap);
		miniMap = NULL;
	}

	// �^���[
	if (tower)
	{
		tower->Release();
		delete(tower);
		tower = NULL;
	}

	// �f�B�t�F���X�}�l�[�W���[
	if (defenseManager)
	{
		defenseManager->Release();
		delete(defenseManager);
		defenseManager = NULL;
	}

	// �A�C�e���}�l�[�W���[
	if (itemManager)
	{
		itemManager->Release();
		delete(itemManager);
		itemManager = NULL;
	}

	// BGM
	if (bgm)
	{
		bgm->StopBackGroundMusic();
		bgm->Release();
		delete(bgm);
		bgm = NULL;
	}

	// �V���b�vBGM
	if (shopBGM)
	{
		shopBGM->StopBackGroundMusic();
		shopBGM->Release();
		delete(shopBGM);
		shopBGM = NULL;
	}

	// ���ʉ�
	for (int i = 0; i < 4; i++)
	{
		if (se[i])
		{
			se[i]->StopSoundEffect();
			se[i]->Release();
			delete(se[i]);
			se[i] = NULL;
		}

		if (menuSe[i])
		{
			menuSe[i]->StopSoundEffect();
			menuSe[i]->Release();
			delete(menuSe[i]);
			menuSe[i] = NULL;
		}
	}

	if (nowLoading)
	{
		nowLoading->Release();
		delete(nowLoading);
		nowLoading = NULL;
	}

	// �����摜�폜
	DeleteGraph(descriptionGraphHandle[0]);
	descriptionGraphHandle[0] = NULL;

	DeleteGraph(descriptionGraphHandle[1]);
	descriptionGraphHandle[1] = NULL;

	// �E�F�[�u�摜
	DeleteGraph(waveGraphHandle);
	waveGraphHandle = NULL;
	// �^�C���摜
	DeleteGraph(timeGraphHandle);
	timeGraphHandle = NULL;

	// �����̉摜
	DeleteGraph(moneyCountGraphHandle);
	moneyCountGraphHandle = NULL;

	// �Q�[���X�^�[�g�摜
	DeleteGraph(gameStartGraphHandle);
	gameStartGraphHandle = NULL;
	//
	DeleteGraph(menuGraphHandle);
	menuGraphHandle = NULL;
	DeleteGraph(menuFrameGraphHandle);
	menuFrameGraphHandle = NULL;


	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(descriptionRuleGraphHandle[i]);
		descriptionRuleGraphHandle[i] = NULL;
		DeleteGraph(descriptionOperationGraphHandle[i]);
		descriptionOperationGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(timeCountGraphHandle[i]);
		timeCountGraphHandle[i] = NULL;
	}

	//
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numberGraphHandle[i]);
		numberGraphHandle[i] = NULL;
	}

}