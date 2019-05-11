#pragma once
#include "Common.h"

class MouseInput
{
public:
	~MouseInput();


	void Update();

	static MouseInput &MouseInputInstance()
	{
		static MouseInput instance;
		return instance;
	}

	// �����ꂽ�u��
	bool MousePush(int _mouseInput);
	// �����ꑱ���Ă��邩
	bool MousePresed(int _mouseInput);
	// �����ꂽ�u��
	bool MouseRelease(int _mouseInput);

private:
	MouseInput();
	
	int nowInput;
	int prevInput;

};


#define MOUSE_INPUT			MouseInput::MouseInputInstance()
