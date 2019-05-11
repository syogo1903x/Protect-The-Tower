#include "Common.h"

SceneTitle::SceneTitle()
{
	// ���[�h���Ɍ��ʉ��̍폜
	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		delete(se);
		se = NULL;
	}
}

SceneTitle::~SceneTitle()
{
	Release();
}

void SceneTitle::Init()
{
	padInputSize = GetJoypadNum();

	// BGM�ǂݍ���
	bgm = new BackGroundMusic("Music/BGM/titleBGM.mp3");

	// ���ʉ��ǂݍ���
	se = new SoundEffect("Music/SE/decision9.mp3");

	graphHandle = LoadGraph("img/title1.png");
	LoadDivGraph("img/flan.png", 2, 2, 1, 32, 32, moouseGraphHandle, TRUE);

	titleGraphHandle[0] = LoadGraph("img/title_char.png");
	titleGraphHandle[1] = LoadGraph("img/ground.png");

	titleModelHandle = MV1LoadModel("skyDome/Skydome_CC6/Dome_CC601.pmx");
	MV1SetPosition(titleModelHandle, VGet(0, -700, 0));

	titlePushGraphHandle[0] = LoadGraph("img/push2.png");
	titlePushGraphHandle[1] = LoadGraph("img/push.png");

	animation = 0;
	animationCount = 0;
	isAlhaBlend = true;
	rotate = 0;

	rogoGraphHandle = LoadGraph("img/rogo2.png");

	isDemo = false;
	// �t�F�[�h�C�� �t�F�[�h�A�E�g ������
	FADE.Init();

	// BGM�Đ�
	bgm->PlayBackGroundMusic();

	// �J������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 50, 100), VGet(0, 0, 0));
}

SceneBase * SceneTitle::Update()
{
	GetMousePoint(&mouseX, &mouseY);
	animation++;

	// �X�J�C�h�[���̉�]
	rotate += 0.0005f;
	
	// �_��
	if (animation % 20 == 0)
	{
		isAlhaBlend = !isAlhaBlend;
	}

	if (isAlhaBlend)
	{
		animationCount = 255;
	}
	else
	{
		animationCount = 0;
	}

	// �L�[�������ꂽ��
	if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
	{
		// ���ʉ��Đ�
		se->PlaySoundEffect();

		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");

		isDemo = true;
	}

	if (animation >= 300 || KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON)
	{
		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");

		isDemo = false;
	}


	// �t�F�[�h�A�E�g���I���ΕύX
	if (FADE.FadeOutEnd() && isDemo)
	{
		isTitlePass = true;
		// ���
		Release();
		// �؂�ւ�
		return new SceneMenu;
	}

	// �t�F�[�h�A�E�g���I���ΕύX
	if (FADE.FadeOutEnd() && !isDemo)
	{
		isTitlePass = true;
		// ���
		Release();
		// �؂�ւ�
		return new SceneDemo;
	}

	// �G�X�P�[�v���������ΏI��
	if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON)
	{
		SceneChange::SetEscape(true);
	}

	return this;
}

void SceneTitle::Draw()
{
	MV1SetRotationXYZ(titleModelHandle, VGet(0, rotate, 0));
	MV1DrawModel(titleModelHandle);
	
	DrawGraph(0, 0, titleGraphHandle[1], TRUE);

	DrawRotaGraph(SCREEN_X / 3, (int)(SCREEN_Y / 2.5f), 1.f, 0.0f, rogoGraphHandle, TRUE, TRUE);
	DrawRotaGraph(SCREEN_X / 3, (int)(SCREEN_Y / 2.5f), 0.8f, 0.0f, graphHandle, TRUE);
	DrawGraph(0, 0, titleGraphHandle[0], TRUE);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, animationCount);

	// �p�b�h�����Ă�����
	if (SceneChange::GetPadOrKey())
	{
		DrawRotaGraphF(SCREEN_X / 3.f, SCREEN_Y / 1.15f, 1.f, 0.0f, titlePushGraphHandle[0], TRUE);
	}
	// �L�[���
	else
	{
		DrawRotaGraphF(SCREEN_X / 3.f, SCREEN_Y / 1.15f, 1.f, 0.0f, titlePushGraphHandle[1], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawRotaGraph(mouseX, mouseY, 1, 0, moouseGraphHandle[animation % 2], TRUE);

	// �t�F�[�h�A�E�g
	FADE.FadeOut_Play();

	if (isTitlePass)
	{
		// �t�F�[�h�C��
		FADE.FadeIn_Play();
	}
	else
	{
		FADE.TitleFadeIn_Play();
	}
}

void SceneTitle::Release()
{
	DeleteGraph(graphHandle);
	graphHandle = NULL;

	MV1DeleteModel(titleModelHandle);
	titleModelHandle = NULL;

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(moouseGraphHandle[i]);
		moouseGraphHandle[i] = NULL;

		DeleteGraph(titleGraphHandle[i]);
		titleGraphHandle[i] = NULL;

		DeleteGraph(titlePushGraphHandle[i]);
		titlePushGraphHandle[i] = NULL;

	}


	DeleteGraph(rogoGraphHandle);
	rogoGraphHandle = NULL;

	if (bgm)
	{
		bgm->StopBackGroundMusic();
		bgm->Release();
		delete(bgm);
		bgm = NULL;
	}
}
