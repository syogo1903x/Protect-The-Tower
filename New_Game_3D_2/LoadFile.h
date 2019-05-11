#pragma once

class LoadFile
{
public:
	~LoadFile();

	static LoadFile &LoadFileInstance()
	{
		static LoadFile instance;
		return instance;
	}

	void LoadFileData(const char * _fileName);


private:
	LoadFile();

	int number;
};


#define LOAD_FILE			LoadFile::LoadFileInstance()