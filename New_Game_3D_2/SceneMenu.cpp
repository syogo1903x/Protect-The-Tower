#include "Common.h"

char *SceneMenu::playerModelHandle = "";
char *SceneMenu::stageModelHandle = "";

SceneMenu::SceneMenu()
{
	for (int i = 0; i < 3; i++)
	{
		if (se[i])
		{
			se[i]->Release();
			se[i] = NULL;
		}
	}
}

SceneMenu::~SceneMenu()
{
	Release();
}

void SceneMenu::Init()
{
	// BGM�ǂݍ���
	bgm = new BackGroundMusic("Music/BGM/MenuBGM.mp3");
	// ���ʉ��ǂݍ���
	se[0] = new SoundEffect("Music/SE/cursor10.mp3");
	se[1] = new SoundEffect("Music/SE/cancel2.mp3");
	se[2] = new SoundEffect("Music/SE/decision9.mp3");

	mouseX = SCREEN_X / 2;
	mouseY = SCREEN_Y / 2;
	// �}�E�X�̏������W���S
	SetMousePoint(mouseX, mouseY);

	// 
	graphHandle = LoadGraph("img/menu.png");
	// 
	nowLoadingGaprhHandle = LoadGraph("img/nowloading.png");
	optionGraphHandle = LoadGraph("img/option.png");

	// 
	characterModelHandle[0] = "character/original/�E�܂����_Gun/ukon.pmx";
	characterModelHandle[1] = "character/original/Ruby_Gun/Ruby.pmx";
	characterModelHandle[2] = "character/original/���Ȃ��Ȃ�_Gun/���Ȃ��Ȃ�V4.pmx";
	characterModelHandle[3] = "character/original/MMD�p�x�錢_Gun/������.pmx";
	characterModelHandle[4] = "character/original/MMD�p�x��J���X_Gun/MMD�p�x��J���X.pmx";

	// 
	stageObjModelHandle[0] = "stage/���ʘOver0.93/���ʘO.pmx";
	stageObjModelHandle[1] = "stage/���O�r�[�O���E���h1.05/���O�r�[�O���E���h�i�Ő��j.pmx";
	stageObjModelHandle[2] = "stage/���̓s���e���X�e�[�W/���̓s���e���X�e�[�W.pmx";

	// 
	characterGraphHandle[0] = LoadGraph("img/character/ukon_1.png");
	characterGraphHandle[1] = LoadGraph("img/character/Ruby_1.png");
	characterGraphHandle[2] = LoadGraph("img/character/�������Ȃ�_1.png");
	characterGraphHandle[3] = LoadGraph("img/character/������_1.png");
	characterGraphHandle[4] = LoadGraph("img/character/�J���X_1.png");
	// 
	characterStartGraphHandle[0] = LoadGraph("img/character/ukon_2.png");
	characterStartGraphHandle[1] = LoadGraph("img/character/Ruby_2.png");
	characterStartGraphHandle[2] = LoadGraph("img/character/�������Ȃ�_2.png");
	characterStartGraphHandle[3] = LoadGraph("img/character/������_2.png");
	characterStartGraphHandle[4] = LoadGraph("img/character/�J���X_2.png");

	stageGraphHandle[0] = LoadGraph("img/stage/���ʘO.png");
	stageGraphHandle[1] = LoadGraph("img/stage/�Ő�.png");
	stageGraphHandle[2] = LoadGraph("img/stage/���̓s.png");

	difficultGraphHandle[0] = LoadGraph("img/easy.png");
	difficultGraphHandle[1] = LoadGraph("img/norm.png");
	difficultGraphHandle[2] = LoadGraph("img/hard.png");

	frameGraphHandle[0] = LoadGraph("img/character/frame.png");
	frameGraphHandle[1] = LoadGraph("img/character/frame2.png");
	//
	LoadDivGraph("img/flan.png", 2, 2, 1, 32, 32, moouseGraphHandle, TRUE);
	// 
	startGraphHandle = LoadGraph("img/OK.png");
	// 
	selectGraphHamdle[0] = LoadGraph("img/mouse_left.png");
	selectGraphHamdle[1] = LoadGraph("img/A.png");
	//
	backGraphHandle[0] = LoadGraph("img/mouse_right.png");
	backGraphHandle[1] = LoadGraph("img/B.png");
	//
	selecctMenuGraphHandle[0] = LoadGraph("img/charcterSelect.png");
	selecctMenuGraphHandle[1] = LoadGraph("img/stageSelect.png");
	selecctPushMenuGraphHandle[0] = LoadGraph("img/select.png");
	selecctPushMenuGraphHandle[1] = LoadGraph("img/back.png");

	//
	isPlayerSelect = false;
	isMenuSelect = false;

	playerModelHandle = 0;
	playerNomer = 0;

	stageNomer = 0;

	menuCount = 0;

	for (int i = 0; i < 5; i++)
	{
		isPlayerDecision[i] = false;
		isSoundEffect[i] = false;
	}
	for (int i = 0;i < 3; i++)
	{
		isMenuDecision[i] = false;
	}

	changeCount = 0;
	isChange = false;


	isPush = false;
	pushCount = 0;

	playerSizeUpCount = 0;
	playerSizeUp = 0;
	playerSizeUpBlank = 0;

	menuSizeUp = 0;
	menuSizeUpBlank = 0;
	menuSizeUpCount = 0;

	// �t�F�[�h�C�� �t�F�[�h�A�E�g ������
	FADE.Init();

	// BGM�Đ�
	bgm->PlayBackGroundMusic();

	LOAD_FILE.LoadFileData("GameCount.txt");
}

SceneBase * SceneMenu::Update()
{
	GetMousePoint(&mouseX, &mouseY);
	animation++;

	if (menuCount == 0)
	{
		// ���j���[�T�C�Y�����Z�b�g����	
		menuSizeUp = 0;
		menuSizeUpBlank = 0;
		menuSizeUpCount = 0;

		// ���肳��Ă��Ȃ����Ƃɂ���
		isPlayerSelect = false;
		// �E����������
		if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000 && !isPush)
		{
			// ���Z�b�g
			playerSizeUpBlank = 0;
			playerSizeUp = 0;
			playerSizeUpCount = 0;

			// �I�����Đ�
			se[0]->PlaySoundEffect();

			// �������t���O���I��
			isPush = true;
			playerNomer++;
		}

		// ������������
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000 && !isPush)
		{
			// ���Z�b�g
			playerSizeUpBlank = 0;
			playerSizeUp = 0;
			playerSizeUpCount = 0;

			// �I�����Đ�
			se[0]->PlaySoundEffect();

			// �������t���O���I��
			isPush = true;
			playerNomer--;
		}
	}
	else
	{
		// ���肳��Ă��Ȃ����Ƃɂ���
		isMenuSelect = false;
		// �v���C���[�T�C�Y���Z�b�g
		playerSizeUpBlank = 0;
		playerSizeUp = 0;
		playerSizeUpCount = 0;

		// �E����������
		if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000 && !isPush)
		{
			// ���Z�b�g����	
			menuSizeUp = 0;
			menuSizeUpBlank = 0;
			menuSizeUpCount = 0;

			// �I�����Đ�
			se[0]->PlaySoundEffect();

			// �������t���O���I��
			isPush = true;
			stageNomer++;
		}

		// ������������
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000 && !isPush)
		{
			// ���Z�b�g����	
			menuSizeUp = 0;
			menuSizeUpBlank = 0;
			menuSizeUpCount = 0;

			// �I�����Đ�
			se[0]->PlaySoundEffect();

			// �������t���O���I��
			isPush = true;
			stageNomer--;
		}
	}

	// �����ꑱ���Ȃ��悤�ɂ���
	if (isPush) { pushCount ++; }
	if (pushCount > 7) { isPush = false; pushCount = 0; }

	// �ő�l�ƍŏ��l�𒴂��Ȃ�
	if (playerNomer > PLAYER_MAX)
	{
		playerNomer = 0;
	}
	if (playerNomer < 0)
	{
		playerNomer = PLAYER_MAX;
	}


	// �ő�l�ƍŏ��l�𒴂��Ȃ�
	if (stageNomer > MENU_MAX)
	{
		stageNomer = 0;
	}
	if (stageNomer < 0)
	{
		stageNomer = MENU_MAX;
	}

	//�@�L�����N�^�[���ꍞ��
	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		if (playerNomer == i)
		{
			playerModelHandle = characterModelHandle[i];
		}
	}

	//�@�X�e�[�W���ꍞ��
	for (int i = 0; i < MENU_COUNT; i++)
	{
		if (stageNomer == i)
		{
			stageModelHandle = stageObjModelHandle[i];
		}
	}

	// �L�[�������ꂽ��
	if (menuCount == 0)
	{
		for (int i = 0; i < PLAYER_COUNT; i++)
		{
			// �����蔻��
			if ((PLAYER_BLANK + HIT_SIZE * i) - HIT_CHECK < mouseX && (PLAYER_BLANK + HIT_SIZE * i) + HIT_CHECK > mouseX &&
				PLAYER_BLANK_Y - HIT_CHECK < mouseY && PLAYER_BLANK_Y + HIT_CHECK > mouseY)
			{
				// 
				if (!isSoundEffect[i])
				{
					// �I�����Đ�
					se[0]->PlaySoundEffect();
					isSoundEffect[i] = true;
				}

				isPlayerDecision[i] = true;
				playerNomer = i;
				// �}�E�X����������
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
				{
					// ���艹�Đ�
					se[2]->PlaySoundEffect();

					// �J�E���g�ύX
					menuCount = 1;
					isPlayerSelect = true;
				}
			}
			else
			{
				isPlayerDecision[i] = false;
				isSoundEffect[i] = false;
			}

			// �v���C���[�I�����F�ύX
			if (playerNomer == i)
			{
				isPlayerDecision[i] = true;
			}
		}

		if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A))
		{
			// ���艹�Đ�
			se[2]->PlaySoundEffect();

			// �J�E���g�ύX
			menuCount = 1;
			isPlayerSelect = true;
		}

		// �v���C���[�I���ɖ߂�
		if (KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B) || MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT))
		{
			// �L�����Z�����Đ�
			se[1]->PlaySoundEffect();

			// �t�F�[�h�A�E�g�������������̏�������
			FADE.TermsFadeOut_Play("Fast");
		}
	}
	else
	{
		for (int i = 0; i < MENU_COUNT; i++)
		{
			// �����蔻��
			if ((MENU_BLANK + HIT_SIZE * i) - HIT_CHECK < mouseX && (MENU_BLANK + HIT_SIZE * i) + HIT_CHECK > mouseX &&
				MENU_Y + 30 - HIT_CHECK < mouseY && MENU_Y + 30 + HIT_CHECK > mouseY)
			{
				// 
				if (!isSoundEffect[i]) 
				{
					// �I�����Đ�
					se[0]->PlaySoundEffect();
					isSoundEffect[i] = true;
				}
				// 
				stageNomer = i;
				isMenuDecision[i] = true;
				// �}�E�X����������
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
				{
					// ���艹�Đ�
					se[2]->PlaySoundEffect();

					// �ύX�t���O�̃I��
					isChange = true;
					isMenuSelect = true;
				}
			}
			else
			{
				isMenuDecision[i] = false;
				isSoundEffect[i] = false;
			}

			// �X�e�[�W�I�����F�ύX
			if (stageNomer == i)
			{
				isMenuDecision[i] = true;
			}
		}

		if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON|| PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A))
		{
			// ���艹�Đ�
			se[2]->PlaySoundEffect();

			// �ύX�t���O�̃I��
			isChange = true;
			isMenuSelect = true;
		}

		// �v���C���[�I���ɖ߂�
		if (KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B) || MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT))
		{
			// �L�����Z�����Đ�
			se[1]->PlaySoundEffect();

			// �J�E���g�ύX
			menuCount = 0;
		}

	}

	if (isChange)	changeCount++;

	if (changeCount > 4)
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneGame;
	}

	// �t�F�[�h�A�E�g���I���ΕύX
	if (FADE.FadeOutEnd())
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneTitle;
	}

	// �G�X�P�[�v���������ΏI��
	if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON)
	{
		SceneChange::SetEscape(true);
	}

	return this;
}

void SceneMenu::Draw()
{
	DrawGraph(0, 0, graphHandle, TRUE);

	if (menuCount == 0)
	{
		DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 2.f, 1.0f, 0.0f, selecctMenuGraphHandle[0], TRUE);
		// 
		playerSizeUpCount++;
		if (playerSizeUpCount > 0 && playerSizeUpCount <= 30) { playerSizeUp += 0.0015f; playerSizeUpBlank += 0.36f; }
		if (playerSizeUpCount > 30 && playerSizeUpCount <= 60) { playerSizeUp -= 0.0015f; playerSizeUpBlank -= 0.36f; }
		if (playerSizeUpCount >= 60) { playerSizeUpCount = 0; }
	}
	else 
	{
		DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 2.f, 1.0f, 0.0f, selecctMenuGraphHandle[1], TRUE);
		//
		menuSizeUpCount++;
		if (menuSizeUpCount > 0 && menuSizeUpCount <= 30) { menuSizeUp += 0.0015f; menuSizeUpBlank += 0.36f; }
		if (menuSizeUpCount > 30 && menuSizeUpCount <= 60) { menuSizeUp -= 0.0015f; menuSizeUpBlank -= 0.36f; }
		if (menuSizeUpCount >= 60) { menuSizeUpCount = 0; }
	}

	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 0.4f, 0.0, frameGraphHandle[1], TRUE);

		// �L�����N�^�[�I��
		if (isPlayerDecision[i])
		{
			//DrawBox(90 + 300 * i - (int)playerSizeUpBlank, 150 - (int)playerSizeUpBlank, 310 + 300 * i + (int)playerSizeUpBlank, 350 + (int)playerSizeUpBlank, GetColor(250, 250, 250), TRUE);
			DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 1.0, 0.0, characterStartGraphHandle[i], TRUE);
			// ����摜
			if (isPlayerSelect) { DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 0.3f, 0.0f, startGraphHandle, TRUE); }
			if (menuCount == 0) { DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 0.48f + playerSizeUp, 0.0, frameGraphHandle[0], TRUE); }
		}
		else
		{
			DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 1.0, 0.0, characterGraphHandle[i], TRUE);
		}
	}

	for (int i = 0; i < MENU_COUNT; i++)
	{
		DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y + 30, 0.4f, 0.0, frameGraphHandle[1], TRUE);
		DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y - 110, 1.0, 0.0, difficultGraphHandle[i], TRUE);
		DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y + 30, 1.0, 0.0, stageGraphHandle[i], TRUE);

		// �X�e�[�W�I��
		if (isMenuDecision[i])
		{
			//DrawBox(390 + 300 * i - (int)menuSizeUpBlank, 580 - (int)menuSizeUpBlank, 610 + 300 * i + (int)menuSizeUpBlank, 780 + (int)menuSizeUpBlank, GetColor(250, 250, 250), TRUE);
			if (isMenuSelect) { DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y, 0.3f + menuSizeUp, 0.0f, startGraphHandle, TRUE); }
			if (menuCount == 1) { DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y + 30, 0.48f + menuSizeUp, 0.0, frameGraphHandle[0], TRUE); }
		}
	}

	//
	DrawRotaGraph(1250, MENU_Y + 30, 0.4f, 0.0, frameGraphHandle[1], TRUE);

	DrawRotaGraph(1170, 635, 0.3f, 0.0f, selectGraphHamdle[0], TRUE);
	DrawRotaGraph(1235, 635, 0.2f, 0.0f, selectGraphHamdle[1], TRUE);
	DrawRotaGraph(1170, 725, 0.3f, 0.0f, backGraphHandle[0], TRUE);
	DrawRotaGraph(1235, 725, 0.2f, 0.0f, backGraphHandle[1], TRUE);

	DrawRotaGraph(1310, 635, 0.7f, 0.0f, selecctPushMenuGraphHandle[0], TRUE);
	DrawRotaGraph(1310, 725, 0.7f, 0.0f, selecctPushMenuGraphHandle[1], TRUE);


	// �}�E�X�ʒu
	DrawRotaGraph(mouseX, mouseY, 1, 0, moouseGraphHandle[animation % 2], TRUE);

	//
	if (isChange)
	{
		DrawGraph(0, 0, nowLoadingGaprhHandle, TRUE);
		DrawGraph(0, -30, optionGraphHandle, TRUE);
	}

	// �t�F�[�h�C��
	FADE.FadeIn_Play();
	// �t�F�[�h�A�E�g
	FADE.FadeOut_Play();
	//printfDx("%s\n", stageModelHandle);
}

void SceneMenu::Release()
{
	DeleteGraph(graphHandle);
	graphHandle = NULL;

	DeleteGraph(nowLoadingGaprhHandle);
	nowLoadingGaprhHandle = NULL;
	DeleteGraph(optionGraphHandle);
	optionGraphHandle = NULL;
	DeleteGraph(startGraphHandle);
	startGraphHandle = NULL;

	DeleteGraph(moouseGraphHandle[0]);
	moouseGraphHandle[0] = NULL;
	DeleteGraph(moouseGraphHandle[1]);
	moouseGraphHandle[1] = NULL;

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(selectGraphHamdle[i]);
		selectGraphHamdle[i] = NULL;

		DeleteGraph(backGraphHandle[i]);
		backGraphHandle[i] = NULL;

		DeleteGraph(frameGraphHandle[i]);
		frameGraphHandle[i] = NULL;

		DeleteGraph(selecctMenuGraphHandle[i]);
		selecctMenuGraphHandle[i] = NULL;

		DeleteGraph(selecctPushMenuGraphHandle[i]);
		selecctPushMenuGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 3; i++)
	{
		// 
		DeleteGraph(stageGraphHandle[i]);
		stageGraphHandle[i] = NULL;

		// 
		DeleteGraph(difficultGraphHandle[i]);
		difficultGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(characterGraphHandle[i]);
		characterGraphHandle[i] = NULL;
		DeleteGraph(characterStartGraphHandle[i]);
		characterStartGraphHandle[i] = NULL;
	}

	bgm->StopBackGroundMusic();
	bgm->Release();
}
