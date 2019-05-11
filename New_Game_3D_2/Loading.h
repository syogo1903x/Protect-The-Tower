#pragma once


struct LOAD_FILE_PARAMETER
{
	void *FileImage;
	int	FileSize;
};

// ファイルを読み込む関数
int LoadingFile(const TCHAR *FilePath, void **FileImageAddr, int *FileSize);

// ファイル読み込み用コールバック関数
int FileReadFunc(const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData);

// ファイル解放用コールバック関数
int FileReleaseFunc(void *MemoryAddr, void *FileReadFuncData);

void Thread(LOAD_FILE_PARAMETER *param);