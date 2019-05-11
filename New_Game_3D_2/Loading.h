#pragma once


struct LOAD_FILE_PARAMETER
{
	void *FileImage;
	int	FileSize;
};

// �t�@�C����ǂݍ��ފ֐�
int LoadingFile(const TCHAR *FilePath, void **FileImageAddr, int *FileSize);

// �t�@�C���ǂݍ��ݗp�R�[���o�b�N�֐�
int FileReadFunc(const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData);

// �t�@�C������p�R�[���o�b�N�֐�
int FileReleaseFunc(void *MemoryAddr, void *FileReadFuncData);

void Thread(LOAD_FILE_PARAMETER *param);