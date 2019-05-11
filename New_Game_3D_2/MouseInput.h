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

	// ‰Ÿ‚³‚ê‚½uŠÔ
	bool MousePush(int _mouseInput);
	// ‰Ÿ‚³‚ê‘±‚¯‚Ä‚¢‚é‚©
	bool MousePresed(int _mouseInput);
	// —£‚³‚ê‚½uŠÔ
	bool MouseRelease(int _mouseInput);

private:
	MouseInput();
	
	int nowInput;
	int prevInput;

};


#define MOUSE_INPUT			MouseInput::MouseInputInstance()
