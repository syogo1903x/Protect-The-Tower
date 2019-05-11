#pragma once
#include "Dxlib.h"

class PadInput
{
public:
	~PadInput();

	void Update(char *_padNomber);

	// �����ꂽ�u��
	bool PadPush(char *_padNomber, int _padInputNumber);
	// �����ꑱ���Ă���
	bool PadPressed(char *_padNomber, int _padInputNumber);
	// �����ꂽ�u��
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