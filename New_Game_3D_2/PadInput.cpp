#include "PadInput.h"

PadInput::PadInput()
{

}

PadInput::~PadInput()
{

}

void PadInput::Update(char *_padNomber)
{
	prevPad = pad;
}

// パッドが押された瞬間
bool PadInput::PadPush(char * _padNomber, int _padInputNumber)
{
	if (GetPadInput(_padNomber).Buttons[_padInputNumber] && !prevPad.Buttons[_padInputNumber])
	{
		return true;
	}

	return false;
}


// パッドが押され続けているとき
bool PadInput::PadPressed(char * _padNomber, int _padInputNumber)
{
	if (GetPadInput(_padNomber).Buttons[_padInputNumber] && prevPad.Buttons[_padInputNumber])
	{
		return true;
	}

	return false;
}


// パッドが離されたとき
bool PadInput::PadRelease(char * _padNomber, int _padInputNumber)
{
	if (!GetPadInput(_padNomber).Buttons[_padInputNumber] && prevPad.Buttons[_padInputNumber])
	{
		return true;
	}

	return false;
}


// 現在のパッドの取得
XINPUT_STATE PadInput::GetPadInput(char *_padNomber)
{
	if (_padNomber == "1P") { GetJoypadXInputState(DX_INPUT_KEY_PAD1, &pad); }
	if (_padNomber == "2P") { GetJoypadXInputState(DX_INPUT_PAD2, &pad); }
	if (_padNomber == "3P") { GetJoypadXInputState(DX_INPUT_PAD3, &pad); }
	if (_padNomber == "4P") { GetJoypadXInputState(DX_INPUT_PAD4, &pad); }

	return pad;
}

