#include "Common.h"

LoadFile::LoadFile()
{
}

LoadFile::~LoadFile()
{

}

void LoadFile::LoadFileData(const char * _fileName)
{
	// �t�@�C�����J��
	std::ifstream ifs(_fileName);

	// ���ۑ�����
	std::string str;

	// �t�@�C���̍Ō�܂Ń��[�v
	while (getline(ifs, str))
	{
		number = stoi(str);
	}

	// �J�E���g�𑝂₷
	number++;


	//�o�̓X�g���[���̍쐬
	std::ofstream ofs(_fileName);
	std::string buf;

	//�t�@�C���ɏ�������
	ofs << number << std::endl;

}