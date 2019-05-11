#include "Common.h"

int SceneResult::playerModelHandle;

SceneResult::SceneResult()
{

	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		delete(se);
	}

}

SceneResult::~SceneResult()
{
	Release();
}

void SceneResult::Init()
{

	// ���ʉ��ǂݍ���
	se = new SoundEffect("Music/SE/decision9.mp3");


	// �L�����N�^�[�̗����Ă����摜
	playerGraphHandle[0] = LoadGraph("img/character/ukon_fall.png");
	playerGraphHandle[1] = LoadGraph("img/character/Ruby_fall.png");
	playerGraphHandle[2] = LoadGraph("img/character/���Ȃ�_fall.png");
	playerGraphHandle[3] = LoadGraph("img/character/������_fall.png");
	playerGraphHandle[4] = LoadGraph("img/character/�J���X_fall.png");

	// �L�����N�^�[�̓|�ꂽ�摜
	playerLandingGraphHandle[0] = LoadGraph("img/character/ukon_die.png");
	playerLandingGraphHandle[1] = LoadGraph("img/character/Ruby_die.png");
	playerLandingGraphHandle[2] = LoadGraph("img/character/���Ȃ�_die.png");
	playerLandingGraphHandle[3] = LoadGraph("img/character/������_die.png");
	playerLandingGraphHandle[4] = LoadGraph("img/character/�J���X_die.png");

	// �{�^���摜
	resultPushGraphHandle[0] = LoadGraph("img/push2.png");
	resultPushGraphHandle[1] = LoadGraph("img/push.png");


	// �A�j���[�V�������A�^�b�`
	animAttachIndex = MV1AttachAnim(playerModelHandle, 6, -1, FALSE);

	// ������
	if (SceneGame::GetResult() == "WIN")
	{
		// �v���C���[�摜�̍폜
		playerFallGraphHandle = NULL;
		// �w�i��������ʂ�
		resultGraphHandle = LoadGraph("img/clear.jpg");
		// �����摜
		resultWinOrLoseGraphHandle = LoadGraph("img/win.png");
		// BGM�ǂݍ���
		bgm = new BackGroundMusic("Music/BGM/winBGM.mp3");
	}
	// �s�k��
	else
	{
		// �w�i��s�k��ʂ�
		resultGraphHandle = LoadGraph("img/lose.png");
		// �s�k���
		resultWinOrLoseGraphHandle = LoadGraph("img/lose_.png");

		// �s�k���̃v���C���[���擾���v���C���[�摜�̓��ꍞ��
		if (SceneMenu::GetPlayer() == "character/original/�E�܂����_Gun/ukon.pmx") { playerFallGraphHandle = playerGraphHandle[0]; playerLandGraphHandle = playerLandingGraphHandle[0]; }
		if (SceneMenu::GetPlayer() == "character/original/Ruby_Gun/Ruby.pmx") { playerFallGraphHandle = playerGraphHandle[1]; playerLandGraphHandle = playerLandingGraphHandle[1]; }
		if (SceneMenu::GetPlayer() == "character/original/���Ȃ��Ȃ�_Gun/���Ȃ��Ȃ�V4.pmx") { playerFallGraphHandle = playerGraphHandle[2]; playerLandGraphHandle = playerLandingGraphHandle[2]; }
		if (SceneMenu::GetPlayer() == "character/original/MMD�p�x�錢_Gun/������.pmx") { playerFallGraphHandle = playerGraphHandle[3]; playerLandGraphHandle = playerLandingGraphHandle[3]; }
		if (SceneMenu::GetPlayer() == "character/original/MMD�p�x��J���X_Gun/MMD�p�x��J���X.pmx") { playerFallGraphHandle = playerGraphHandle[4]; playerLandGraphHandle = playerLandingGraphHandle[4]; }

		// BGM�ǂݍ���
		bgm = new BackGroundMusic("Music/BGM/loseBGM.mp3");
	}

	bound = 0;
	boundCount = 0;
	isFall = true;
	pos = VGet(SCREEN_X / 2, -400, 0);
	count = 0;


	// �J������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(50, 15, 50), VGet(-50, 0, -50));

	// �t�F�[�h�C�� �t�F�[�h�A�E�g ������
	FADE.Init();

	// BGM�Đ�
	bgm->PlayBackGroundMusic();
}

SceneBase * SceneResult::Update()
{
	//
	count++;
	// �s�k���̃o�E���h
	pos.y += 50;

	if (pos.y > SCREEN_Y - 140)
	{
		boundCount++;
		pos.y = SCREEN_Y - 140;
	}

	if (boundCount > 10)
	{
		isFall = false;
		boundCount = 10;
	}

	bound = ((sinf(DX_PI_F / 2 * boundCount) * 20));

	MV1SetRotationXYZ(playerModelHandle, VGet(0, -2.14f, 0));
	MV1SetPosition(playerModelHandle, VGet(20, 0, 30));

	// �A�j���[�V�������ꍞ��
	MV1SetAttachAnimTime(playerModelHandle, animAttachIndex, count);


	// �L�[����������
	if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
	{
		// ���ʉ��Đ�
		se->PlaySoundEffect();

		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");
	}

	// �J�E���g���K��l�𒴂�����@�t�F�[�h�A�E�g
	if (count == 600) { se->PlaySoundEffect(); }
	if (count >= 600) { FADE.TermsFadeOut_Play("Fast"); }

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

void SceneResult::Draw()
{
	// ������
	if (SceneGame::GetResult() == "WIN")
	{
		STAGE.Draw();								// �X�e�[�W�`��
		MV1DrawModel(playerModelHandle);			// �v���C���[�\��

		// �p�b�h�̎�
		if (SceneChange::GetPadOrKey())
		{
			DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.2f, 1.f, 0.0f, resultPushGraphHandle[0], TRUE);
		}
		// �L�[�̎�
		else
		{
			DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.2f, 1.f, 0.0f, resultPushGraphHandle[1], TRUE);
		}

		// ����
		DrawRotaGraphF(SCREEN_X / 3.f, SCREEN_Y / 2.f, 0.6f, 0.0f, resultWinOrLoseGraphHandle, TRUE);
	}
	// �s�k��
	else
	{
		DrawGraph(0, 0, resultGraphHandle, TRUE);

		// �������
		if (isFall)
		{
			DrawRotaGraphF(pos.x, pos.y + bound, 1.0f, 0.0f, playerFallGraphHandle, TRUE);
		}
		else
		{
			// �p�b�h�̎�
			if (SceneChange::GetPadOrKey())
			{
				DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.9f, 1.f, 0.0f, resultPushGraphHandle[0], TRUE);
			}
			// �L�[�̎�
			else
			{
				DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.9f, 1.f, 0.0f, resultPushGraphHandle[1], TRUE);
			}

			DrawRotaGraphF(pos.x, pos.y + bound / 2, 1.0f, 0.0f, playerLandGraphHandle, TRUE);

			// �s�k
			DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 2.f, 1.0f, 0.0f, resultWinOrLoseGraphHandle, TRUE);
		}
	}

	// �t�F�[�h�C��
	FADE.FadeIn_Play();
	// �t�F�[�h�A�E�g
	FADE.FadeOut_Play();
}

// ���
void SceneResult::Release()
{
	// �폜
	DeleteGraph(graphHandle);
	graphHandle = NULL;

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(resultPushGraphHandle[i]);
		resultPushGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(playerGraphHandle[i]);
		playerGraphHandle[i] = NULL;
		DeleteGraph(playerLandingGraphHandle[i]);
		playerLandingGraphHandle[i] = NULL;
	}

	DeleteGraph(playerFallGraphHandle);
	playerFallGraphHandle = NULL;
	DeleteGraph(playerLandGraphHandle);
	playerLandGraphHandle = NULL;
	DeleteGraph(resultGraphHandle);
	resultGraphHandle = NULL;
	DeleteGraph(resultWinOrLoseGraphHandle);
	resultWinOrLoseGraphHandle = NULL;

	if (bgm)
	{
		bgm->StopBackGroundMusic();
		bgm->Release();
		delete(bgm);
		bgm = NULL;
	}

	// �X�e�[�W�폜
	STAGE.Release();


	// ���f���폜
	MV1DeleteModel(playerModelHandle);
	playerModelHandle = NULL;
}

void SceneResult::CreateModel()
{
	playerModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::PLAYER));

	if (playerModelHandle < 0) { printfDx("���f���G���[\n"); }
}
