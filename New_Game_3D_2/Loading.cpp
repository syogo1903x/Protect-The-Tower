#include "Common.h"


// ファイルを読み込む関数
int LoadingFile(const TCHAR *FilePath, void **FileImageAddr, int *FileSize)
{
	// ファイルを開く
	ifstream fin(FilePath, ios::in | ios::binary);

	// 失敗したら -1 を返す
	if (!fin) return -1;

	// ファイルの末尾を探す
	fin.seekg(0, fstream::end);
	// ファイル末尾のインデックス取得
	std::streampos eofPos = fin.tellg();
	// 先頭に戻るためにclearする
	fin.clear();
	// ファイル先頭に戻る
	fin.seekg(0, fstream::beg);
	// ファイル先頭のインデックス取得
	std::streampos begPos = fin.tellg();
	// 末尾 - 先頭でファイルサイズを取得
	*FileSize = (int)(eofPos - begPos);

	// メモリの確保
	*FileImageAddr = new char[*FileSize]();

	// ファイルの読み込み
	fin.read((char*)*FileImageAddr, *FileSize);

	// ファイルを閉じる
	fin.close();

	// 成功なら 0 を返す
	return 0;
}

// ファイル読み込み用コールバック関数
int FileReadFunc(const TCHAR *FilePath, void **FileImageAddr, int *FileSize, void *FileReadFuncData)
{
	return LoadingFile(FilePath, FileImageAddr, FileSize);
}

// ファイル解放用コールバック関数
int FileReleaseFunc(void *MemoryAddr, void *FileReadFuncData)
{
	// 確保したメモリの解放
	free(MemoryAddr);

	return 0;
}

// モデルのスレッド
void Thread(LOAD_FILE_PARAMETER *param)
{
	// ３Ｄモデルファイルの読み込み
	LoadingFile(SceneMenu::GetStage(), &param[MODEL_HANDLE::GAMESTAGE].FileImage, &param[MODEL_HANDLE::GAMESTAGE].FileSize);
	LoadingFile("Item/danger/danger.mqo", &param[MODEL_HANDLE::GAMESTAGE_OUT].FileImage, &param[MODEL_HANDLE::GAMESTAGE_OUT].FileSize);
	LoadingFile("skyDome/Skydome_CC6/Dome_CC602.pmx", &param[MODEL_HANDLE::SKYDOOM].FileImage, &param[MODEL_HANDLE::SKYDOOM].FileSize);
	LoadingFile("Item/蓮のオブジェ/蓮オブジェ.pmx", &param[MODEL_HANDLE::TOWER].FileImage, &param[MODEL_HANDLE::TOWER].FileSize);
	LoadingFile(SceneMenu::GetPlayer(), &param[MODEL_HANDLE::PLAYER].FileImage, &param[MODEL_HANDLE::PLAYER].FileSize);
	LoadingFile("character/bullet.mqo", &param[MODEL_HANDLE::BULLET_SHOT].FileImage, &param[MODEL_HANDLE::BULLET_SHOT].FileSize);
	LoadingFile("character/original/animal/イノシシwildboar.pmx", &param[MODEL_HANDLE::ENEMY_SMALL].FileImage, &param[MODEL_HANDLE::ENEMY_BOSS].FileSize);
	LoadingFile("character/original/DFM/PMD/DFman.pmd", &param[MODEL_HANDLE::ENEMY_MEDIUM].FileImage, &param[MODEL_HANDLE::ENEMY_MEDIUM].FileSize);
	LoadingFile("character/original/ファットマン/Fatman.pmx", &param[MODEL_HANDLE::ENEMY_BOSS].FileImage, &param[MODEL_HANDLE::ENEMY_BOSS].FileSize);
	LoadingFile("Item/Coin/coin.mqo", &param[MODEL_HANDLE::ITEM_COIN].FileImage, &param[MODEL_HANDLE::ITEM_COIN].FileSize);
	LoadingFile("Item/ハートとお花/ハート（金属光沢）.pmx", &param[MODEL_HANDLE::ITEM_RECOVERY].FileImage, &param[MODEL_HANDLE::ITEM_RECOVERY].FileSize);
	LoadingFile("Item/Wall/wall.mqo", &param[MODEL_HANDLE::DEFENSE_WALL].FileImage, &param[MODEL_HANDLE::DEFENSE_WALL].FileSize);
	LoadingFile("Item/AtackBall.mqo", &param[MODEL_HANDLE::DEFENSE_ATACKBALL].FileImage, &param[MODEL_HANDLE::DEFENSE_ATACKBALL].FileSize);
	LoadingFile("Item/fire.mqo", &param[MODEL_HANDLE::DEFENSE_FIRE].FileImage, &param[MODEL_HANDLE::DEFENSE_FIRE].FileSize);
	LoadingFile("Item/BGM-71/BGM-71 TOW.pmd", &param[MODEL_HANDLE::DEFENSE_SOLDIER].FileImage, &param[MODEL_HANDLE::DEFENSE_SOLDIER].FileSize);
	LoadingFile("Item/茶屋/茶屋/茶屋.pmx", &param[MODEL_HANDLE::DEFENSE_BUY].FileImage, &param[MODEL_HANDLE::DEFENSE_BUY].FileSize);
	LoadingFile("Item/Arrow.mqo", &param[MODEL_HANDLE::DEFENSE_ARROW ].FileImage, &param[MODEL_HANDLE::DEFENSE_ARROW].FileSize);

	Sleep(10000);

	ExitThread(0);
}