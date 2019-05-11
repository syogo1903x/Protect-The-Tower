#include "Common.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// �c�w���C�u��������������
	if (DxLib_Init() < 0)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��
	SetUseDirect3DVersion(DX_DIRECT3D_9);


	// ��ʂ��E�B���h�E���[�h�ɂ���
	ChangeWindowMode(TRUE);
	//ChangeWindowMode(FALSE);

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(SCREEN_X, SCREEN_Y, 16);

	// ������
	SetDrawScreen(DX_SCREEN_BACK);

	// �}�E�X��\��
	SetMouseDispFlag(FALSE);
	// �}�E�X�J�[�\���̃E�B���h�E�O�ւ̈ړ����֎~
	SetValidMousePointerWindowOutClientAreaMoveFlag(FALSE);

	// ����
	SceneChange *scene = new SceneChange();
	// ������
	scene->Init();

	// �G�t�F�N�g�̏�����
	EFFECT.Init();

	// �e�L�X�g�ύX�ǂݍ���
	ChangeTextFont();

	// ��������t�H���g
	TextFontDraw(3);

	// �G���[���o�邩�G�X�P�[�v���������܂Ń��[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !SceneChange::GetEscape())
	{
		// Windows�̂��@�����֐�
		ProcessMessage();

		// ��ʂ�^�����ɍX�V
		ClearDrawScreen();

		// �X�V
		scene->Update();

		// �`��
		scene->Draw();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

	}

	// �e�L�X�g�폜
	TextRelease();

	// Effekseer���I������B
	Effkseer_End();

	// DX���C�u�����̐ݒ��߂�
	RefreshDxLibDirect3DSetting();

	// �J��
	scene->Release();

	// DdxLib�̏I��
	DxLib_End();
	return 0;
}