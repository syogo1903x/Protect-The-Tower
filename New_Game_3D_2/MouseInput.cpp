#include "MouseInput.h"

MouseInput::MouseInput()
{

}

MouseInput::~MouseInput()
{

}

void MouseInput::Update()
{
	prevInput = nowInput;

	nowInput = GetMouseInput();
}


bool MouseInput::MousePush(int _mouseInput)
{
	if ((nowInput & _mouseInput)  && !(prevInput & _mouseInput))
	{
		return true;
	}

	return false;
}

bool MouseInput::MousePresed(int _mouseInput)
{
	if ((nowInput & _mouseInput) && (prevInput & _mouseInput))
	{
		return true;
	}

	return false;

}

bool MouseInput::MouseRelease(int _mouseInput)
{
	if (!(nowInput & _mouseInput) && (prevInput & _mouseInput))
	{
		return true;
	}

	return false;
}
