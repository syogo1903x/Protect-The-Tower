#include "Common.h"

int NowLoad::modelHandle[MODEL_MAX];

NowLoad::NowLoad()
{
	count = 0;
}

NowLoad::~NowLoad()
{

}

// �T�u�X���b�h�̍쐬
void NowLoad::CreateSubThread()
{
	HANDLE threadHandle;
	unsigned long	id;
	DWORD	exitCode;
	LOAD_FILE_PARAMETER	*param;

	param = NULL;
	param = new LOAD_FILE_PARAMETER[MODEL_MAX];

	// �X���b�h�̐���
	threadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, param, 0, &id);

	SetDrawScreen(DX_SCREEN_BACK);


	do
	{
		// ���[�h��ʂ̕`��
		ClearDrawScreen();
		{
			count++;
			DrawBox(0, 0, 1600, 900, GetColor(100, 0, 100), true);

			if (count >= 2) { DrawString(1410, 800, ".", GetColor(0, 0, 0)); }
			if (count >= 4) { DrawString(1420, 800, ".", GetColor(0, 0, 0)); }
			if (count >= 6) { DrawString(1430, 800, ".", GetColor(0, 0, 0)); }

			if (count >= 10) { count = 0; }

			DrawString(1300, 800, "Loading", GetColor(count * 25, count * 25, count * 25));
			DrawFormatString(100, 800, GetColor(0, 0, 0), "%d", count);
		}
		ScreenFlip();

		// �X���b�h�̏�Ԃ𒲂ׂ�
		GetExitCodeThread(threadHandle, &exitCode);

	// �ǂݍ����I�������i��
	}while (ProcessMessage() == 0 && exitCode != 0);


	for (int i = 0; i < MODEL_MAX; i++)
	{
		modelHandle[i] = MV1LoadModelFromMem(param[i].FileImage, param[i].FileSize, FileReadFunc, FileReleaseFunc, NULL);
	}
}

// �T�u�X���b�h�̃��f������
void NowLoad::SubThreadUpdate()
{

	modelHandle[MODEL_HANDLE::GAMESTAGE] = MV1LoadModel(SceneMenu::GetStage());
	modelHandle[MODEL_HANDLE::GAMESTAGE_OUT] = MV1LoadModel("Item/danger/danger.mqo");
	modelHandle[MODEL_HANDLE::SKYDOOM] = MV1LoadModel("skyDome/Skydome_CC6/Dome_CC602.pmx");
	modelHandle[MODEL_HANDLE::TOWER] = MV1LoadModel("Item/�@�̃I�u�W�F/�@�I�u�W�F.pmx");
	modelHandle[MODEL_HANDLE::PLAYER] = MV1LoadModel(SceneMenu::GetPlayer());
	modelHandle[MODEL_HANDLE::BULLET_SHOT] = MV1LoadModel("character/bullet.mqo");
	modelHandle[MODEL_HANDLE::ENEMY_SMALL] = MV1LoadModel("character/original/animal/�C�m�V�Vwildboar.pmx");
	modelHandle[MODEL_HANDLE::ENEMY_MEDIUM] = MV1LoadModel("character/original/DFM/PMD/DFman.pmd");
	modelHandle[MODEL_HANDLE::ENEMY_BOSS] = MV1LoadModel("character/original/�t�@�b�g�}��/Fatman.pmx");
	modelHandle[MODEL_HANDLE::ITEM_COIN] = MV1LoadModel("Item/Coin/coin.mqo");
	modelHandle[MODEL_HANDLE::ITEM_RECOVERY] = MV1LoadModel("Item/�n�[�g�Ƃ���/�n�[�g�i��������j.pmx");
	modelHandle[MODEL_HANDLE::DEFENSE_WALL] = MV1LoadModel("Item/Wall/wall.mqo");
	modelHandle[MODEL_HANDLE::DEFENSE_ATACKBALL] = MV1LoadModel("Item/AtackBall.mqo");
	modelHandle[MODEL_HANDLE::DEFENSE_FIRE] = MV1LoadModel("Item/fire.mqo");
	modelHandle[MODEL_HANDLE::DEFENSE_SOLDIER] = MV1LoadModel("Item/BGM-71/BGM-71 TOW.pmd");
	modelHandle[MODEL_HANDLE::DEFENSE_BUY] = MV1LoadModel("Item/����/����/����.pmx");
	modelHandle[MODEL_HANDLE::DEFENSE_ARROW] = MV1LoadModel("Item/Arrow.mqo");
}

// ���
void NowLoad::Release()
{
	for (int i = 0; i < MODEL_MAX; i++)
	{ 
		MV1DeleteModel(modelHandle[i]);
		modelHandle[i] = NULL;
	}
}
