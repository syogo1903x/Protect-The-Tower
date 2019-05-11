#pragma once
#include "Common.h"

enum KEY_STATE
{
    KEY_OFF = 0,
    KEY_ON,
    KEY_PRESSED,
    KEY_RELEASE
};


class KeyInput
{
public:
	~KeyInput();


	static KeyInput &KeyInputInstance()
	{
		static KeyInput instance;
		return instance;
	}

	void Init_Key();
	void Update_Key();
	KEY_STATE GetKey(unsigned char _keyCode);


private:
	KeyInput();

	KEY_STATE key[256];
	char	 keyState[2][256];

	int nowKey;
	int prevKey;
	
};

#define KEY_INPUT			KeyInput::KeyInputInstance()