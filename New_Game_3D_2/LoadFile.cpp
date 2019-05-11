#include "Common.h"

LoadFile::LoadFile()
{
}

LoadFile::~LoadFile()
{

}

void LoadFile::LoadFileData(const char * _fileName)
{
	// ファイルを開く
	std::ifstream ifs(_fileName);

	// 列を保存する
	std::string str;

	// ファイルの最後までループ
	while (getline(ifs, str))
	{
		number = stoi(str);
	}

	// カウントを増やす
	number++;


	//出力ストリームの作成
	std::ofstream ofs(_fileName);
	std::string buf;

	//ファイルに書き込み
	ofs << number << std::endl;

}