#include "Common.h"


// �t�@�C����ǂݍ��ފ֐�
int LoadingFile(const TCHAR *FilePath, void **FileImageAddr, int *FileSize)
{
	// �t�@�C�����J��
	ifstream fin(FilePath, ios::in | ios::binary);

	// ���s������ -1 ��Ԃ�
	if (!fin) return -1;

	// �t�@�C���̖�����T��
	fin.seekg(0, fstream::end);
	// �t�@�C�������̃C���f�b�N�X�擾
	std::streampos eofPos = fin.tellg();
	// �擪�ɖ߂邽�߂�clear����
	fin.clear();
	// �t�@�C���擪�ɖ߂�
	fin.seekg(0, fstream::beg);
	// �t�@�C���擪�̃C���f�b�N�X�擾
	std::streampos begPos = fin.tellg();
	// ���� - �擪�Ńt�@�C���T�C�Y���擾
	*FileSize = (int)(eofPos - begPos);

	// �������̊m��
	*FileImageAddr = new char[*FileSize]();

	// �t�@�C���̓ǂݍ���
	fin.read((char*)*FileImageAddr, *FileSize);

	// �t�@�C�������
	fin.close();

	// �����Ȃ� 0 ��Ԃ�
	return 0;
}

// �t�@�C���ǂݍ��ݗp�R�[���o�b�N�֐�
int FileReadFunc(const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData)
{
	return LoadingFile(FilePath, FileImageAddr, FileSize);
}

// �t�@�C������p�R�[���o�b�N�֐�
int FileReleaseFunc(void *MemoryAddr, void *FileReadFuncData)
{
	// �m�ۂ����������̉��
	free(MemoryAddr);

	return 0;
}

// ���f���̃X���b�h
void Thread(LOAD_FILE_PARAMETER *param)
{
	// �R�c���f���t�@�C���̓ǂݍ���
	LoadingFile(SceneMenu::GetStage(), &param[MODEL_HANDLE::GAMESTAGE].FileImage, &param[MODEL_HANDLE::GAMESTAGE].FileSize);
	LoadingFile("Item/danger/danger.mqo", &param[MODEL_HANDLE::GAMESTAGE_OUT].FileImage, &param[MODEL_HANDLE::GAMESTAGE_OUT].FileSize);
	LoadingFile("skyDome/Skydome_CC6/Dome_CC602.pmx", &param[MODEL_HANDLE::SKYDOOM].FileImage, &param[MODEL_HANDLE::SKYDOOM].FileSize);
	LoadingFile("Item/�@�̃I�u�W�F/�@�I�u�W�F.pmx", &param[MODEL_HANDLE::TOWER].FileImage, &param[MODEL_HANDLE::TOWER].FileSize);
	LoadingFile(SceneMenu::GetPlayer(), &param[MODEL_HANDLE::PLAYER].FileImage, &param[MODEL_HANDLE::PLAYER].FileSize);
	LoadingFile("character/bullet.mqo", &param[MODEL_HANDLE::BULLET_SHOT].FileImage, &param[MODEL_HANDLE::BULLET_SHOT].FileSize);
	LoadingFile("character/original/animal/�C�m�V�Vwildboar.pmx", &param[MODEL_HANDLE::ENEMY_SMALL].FileImage, &param[MODEL_HANDLE::ENEMY_BOSS].FileSize);
	LoadingFile("character/original/DFM/PMD/DFman.pmd", &param[MODEL_HANDLE::ENEMY_MEDIUM].FileImage, &param[MODEL_HANDLE::ENEMY_MEDIUM].FileSize);
	LoadingFile("character/original/�t�@�b�g�}��/Fatman.pmx", &param[MODEL_HANDLE::ENEMY_BOSS].FileImage, &param[MODEL_HANDLE::ENEMY_BOSS].FileSize);
	LoadingFile("Item/Coin/coin.mqo", &param[MODEL_HANDLE::ITEM_COIN].FileImage, &param[MODEL_HANDLE::ITEM_COIN].FileSize);
	LoadingFile("Item/�n�[�g�Ƃ���/�n�[�g�i��������j.pmx", &param[MODEL_HANDLE::ITEM_RECOVERY].FileImage, &param[MODEL_HANDLE::ITEM_RECOVERY].FileSize);
	LoadingFile("Item/Wall/wall.mqo", &param[MODEL_HANDLE::DEFENSE_WALL].FileImage, &param[MODEL_HANDLE::DEFENSE_WALL].FileSize);
	LoadingFile("Item/AtackBall.mqo", &param[MODEL_HANDLE::DEFENSE_ATACKBALL].FileImage, &param[MODEL_HANDLE::DEFENSE_ATACKBALL].FileSize);
	LoadingFile("Item/fire.mqo", &param[MODEL_HANDLE::DEFENSE_FIRE].FileImage, &param[MODEL_HANDLE::DEFENSE_FIRE].FileSize);
	LoadingFile("Item/BGM-71/BGM-71 TOW.pmd", &param[MODEL_HANDLE::DEFENSE_SOLDIER].FileImage, &param[MODEL_HANDLE::DEFENSE_SOLDIER].FileSize);
	LoadingFile("Item/����/����/����.pmx", &param[MODEL_HANDLE::DEFENSE_BUY].FileImage, &param[MODEL_HANDLE::DEFENSE_BUY].FileSize);
	LoadingFile("Item/Arrow.mqo", &param[MODEL_HANDLE::DEFENSE_ARROW ].FileImage, &param[MODEL_HANDLE::DEFENSE_ARROW].FileSize);

	Sleep(10000);

	ExitThread(0);
}