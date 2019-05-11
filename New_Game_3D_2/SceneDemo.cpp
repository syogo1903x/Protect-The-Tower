#include "Common.h"

SceneDemo::SceneDemo()
{

}

SceneDemo::~SceneDemo()
{

}

void SceneDemo::Init()
{
	// ����̓ǂݍ���
	videoMovieHandle = LoadGraph("video/movie.mp4");
	circleGraphHandle = LoadGraph("img/circle.png");

	count = 0;
	time = 1;

	demoPos = VGet(2000, 400, 0);
	isPush = false;

	// �t�F�[�h�C�� �t�F�[�h�A�E�g ������
	FADE.Init();
	alha = 0;
}

SceneBase * SceneDemo::Update()
{
	// ���Ԃ𑪒�
	count++;
	if (count >= 60) 
	{
		time++; 
		count = 0; 
	}

	if (count > 0 && count < 30) { alha += 8; }
	if (count > 30 && count <= 60) { alha -= 8; }

	demoPos.x -= 10;

	if (demoPos.x <= -1000) { demoPos.x = 2000; }

	PlayMovieToGraph(videoMovieHandle);

	// �L�[���������΃��j���[�ړ�
	if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
	{
		isPush = true;
		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");
	}

	// ���Ԃ����ς��ɂȂ�����^�C�g���ړ�
	if (time >= 15)
	{
		isPush = false;
		// �t�F�[�h�A�E�g�������������̏�������
		FADE.TermsFadeOut_Play("Fast");
	}

	// �t�F�[�h�A�E�g���I���ΕύX
	if (FADE.FadeOutEnd() && !isPush)
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneTitle;
	}

	// �t�F�[�h�A�E�g���I��肩�{�^�����������ΕύX
	if (FADE.FadeOutEnd() && isPush)
	{
		// ���
		Release();
		// �؂�ւ�
		return new SceneMenu;
	}

	// �G�X�P�[�v���������ΏI��
	if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON)
	{
		SceneChange::SetEscape(true);
	}

	return this;
}

void SceneDemo::Draw()
{
	// �r�f�I�\��
	DrawGraph(0, 0, videoMovieHandle, FALSE);

	SetFontSize(DEFAULT_FONT_SIZE * 3);
	DrawFormatString(1500, 50, GetColor(255, 0, 0), "%d", time);
	SetDrawBright(255, 0, 0);
	DrawCircleGauge(1515, 75, count * 1.8f, circleGraphHandle, 0);
	SetDrawBright(255, 255, 255);

	SetFontSize(DEFAULT_FONT_SIZE * 6);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alha);
	DrawFormatStringF(600, 400, GetColor(255, 0, 0), "�f�����[�r�[");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetFontSize(DEFAULT_FONT_SIZE * 3);
	if (SceneChange::GetPadOrKey()) { DrawFormatStringF(700, 850, GetColor(255, 0, 0), "A�{�^���������Ă�"); }
	else { DrawFormatStringF(700, 850, GetColor(255, 0, 0), "�G���^�[/�E�N���b�N�������Ă�"); }
	SetFontSize(DEFAULT_FONT_SIZE);

	// �t�F�[�h�C��
	FADE.FadeIn_Play();
	// �t�F�[�h�A�E�g
	FADE.FadeOut_Play();
}

void SceneDemo::Release()
{
	DeleteGraph(videoMovieHandle);
	videoMovieHandle = NULL;

	DeleteGraph(circleGraphHandle);
	circleGraphHandle = NULL;

}
