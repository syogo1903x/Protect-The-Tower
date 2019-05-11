#include "Common.h"

bool SceneChange::isPad = false;
bool SceneChange::isEscape = false;

SceneChange::SceneChange()
{
	isPad = false;
	isEscape = false;
}

SceneChange::~SceneChange()
{
	Release();
}

// ������
void SceneChange::Init()
{
	// ��ԍŏ��̓^�C�g��
	SetFirstScene(new SceneTitle);
	// �L�[�̏�����
	KEY_INPUT.Init_Key();
	// �V�[���̏�����
	nowScene->Init();
	// �ŏ��̓L�[�{�[�h���
	isPad = false;
}

// �X�V
void SceneChange::Update()
{
	// �L�[�̍X�V
	KEY_INPUT.Update_Key();
	// �p�b�h�̍X�V
	PAD_INPUT.Update("1P");
	// �}�E�X�̍X�V
	MOUSE_INPUT.Update();


	// �L�[�������ꂽ�Ƃ�
	if (CheckHitKeyAll() == 1 || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) ||
		MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) ||
		MOUSE_INPUT.MousePush(MOUSE_INPUT_MIDDLE)) { isPad = false; }

	// �p�b�h�������ꂽ�Ƃ�
	if (PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000 || 
		PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000 ||
		PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000 ||
		PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000 || 
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_X) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_Y) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_LEFT_SHOULDER) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_RIGHT_SHOULDER)) { isPad = true; }

	prevScene = nowScene->Update();

	// �ߋ��̃V�[�������݂̃V�[���ƈ�v���Ă�������΁@�V�[����؂�ւ���
	if (prevScene != nowScene)
	{
		nowScene = prevScene;
		nowScene->Init();
	}
}

// ���
void SceneChange::Release()
{
	// �폜
	if (nowScene)
	{
		nowScene->Release();
		delete nowScene;
		nowScene = NULL;
	}
}

// �\��
void SceneChange::Draw()
{
	nowScene->Draw();
}
