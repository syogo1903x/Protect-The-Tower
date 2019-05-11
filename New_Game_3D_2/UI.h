#pragma once
#include "Common.h"

class UI
{
public:
	// �R���X�g���N�^
	UI() {}
	// �f�X�g���N�^
	~UI() {}
	// ������
	void Init(char *_playerNumber);
	// �X�V
	void Update(CharacterBase *_player);
	// �`��
	void Draw(CharacterBase *_player, Tower *_tower);
	// �t�F�[�h�`��
	void FadeDraw();
	// ���
	void Release();

private:
	// �v���C���[�̗͉摜
	int playerHeartGraphHandle;
	// �v���C���[�̉��̗̑�
	int playerHeartDownGraphHandle;
	// �v���C���[�A�C�R��
	int playerIconGraphHandle;
	// �v���C���[�̉��A�C�R��
	int playerIconDownGraphHandle;
	// �G�C���摜
	int aimingGraphHandle;

	// �v���C���[�摜
	int playerGraphHandle[5];
	int playerPutGraphHandle;

	// �K�E�Z�Q�[�W�摜
	int deathBlowGraphHandle[4];
	int deathBlowStartGraphHandle[2];
	int fireGraphHandle[13];
	int fireCount;
	int alhaCount;
	int blendCount;

	// �t�F�[�h�摜
	int openShopGraphHandle[10];
	int closeShopGraphHandle[18];

	// �������摜
	int moneyGraphHamdle;

	// �^���[�̗͉摜
	int gaugeGraphHandle;
};