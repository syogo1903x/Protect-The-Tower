#pragma once
#include "Dxlib.h"

class PadInput
{
public:
	~PadInput();

	void Update(char *_padNomber);

	// ‰Ÿ‚³‚ê‚½uŠÔ
	bool PadPush(char *_padNomber, int _padInputNumber);
	// ‰Ÿ‚³‚ê‘±‚¯‚Ä‚¢‚é
	bool PadPressed(char *_padNomber, int _padInputNumber);
	// —£‚³‚ê‚½uŠÔ
	bool PadRelease(char *_padNomber, int _padInputNumber);

	static PadInput &PadInputInstance()
	{
		static PadInput instance;
		return instance;
	}

	XINPUT_STATE GetPadInput(char *_padNomber);

private:
	PadInput();
	XINPUT_STATE pad;
	XINPUT_STATE prevPad;

};

#define	PAD_INPUT			PadInput::PadInputInstance()