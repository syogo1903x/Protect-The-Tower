#include "Common.h"

const int FONT_SIZE_MAX = 5;

LPCSTR font[FONT_SIZE_MAX];

enum FONT
{
	GONTA,
	SANSERIF,
	KEION,
	KIRIN,
	TORAMAN,
};

// �e�L�X�g���[�h
void ChangeTextFont()
{
	font[GONTA] = "font/GD-TiVangerionJA-010.otf";
	if (AddFontResourceEx(font[GONTA], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("�G���[\n"); }

	font[SANSERIF] = "font/GN-Kin-iro_SansSerif.ttf";
	if (AddFontResourceEx(font[SANSERIF], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("�G���[\n"); }

	//font_002 = "font/FZGonta-kana/FZ�S���^����.otf";
	font[KEION] = "font/keifont.ttf";
	if (AddFontResourceEx(font[KEION], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("�G���[\n"); }

	font[KIRIN] = "font/kirin-Regular.ttf";
	if (AddFontResourceEx(font[KIRIN], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("�G���[\n"); }

	font[TORAMAN] = "font/toroman.ttf";
	if (AddFontResourceEx(font[TORAMAN], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("�G���[\n"); }

}

///////////////////////////////////
// �e�L�X�g�\��
// 0 : �e�L�X�g �f�t�H���g
// 1 : �e�L�X�g ����������
// 2 : �e�L�X�g ���񂢂�T���Z���t
// 3 : �e�L�X�g �S���^����
// 4 : �e�L�X�g �L�����t�H���g
// 5 : �e�L�X�g �A���j�����g���}��
//////////////////////////////////
void TextFontDraw(int textFont)
{
	// ���C���I
	if (textFont == 0)
	{
		ChangeFont("���C���I", DX_CHARSET_DEFAULT);
	}

	// �S���^�J�i
	if (textFont == 1)
	{
		ChangeFont("GD-TiVangerionJA-OTF", DX_CHARSET_DEFAULT);
	}

	// �T���Z���t
	if (textFont == 2)
	{
		ChangeFont("GN-���񂢂�T���Z���t", DX_CHARSET_DEFAULT);
	}

	// ��������t�H���g
	if (textFont == 3)
	{
		//ChangeFont("FZ�S���^����", DX_CHARSET_DEFAULT);
		ChangeFont("�����ӂ����", DX_CHARSET_DEFAULT);
	}

	// �L�����t�H���g
	if (textFont == 4)
	{
		ChangeFont("�L�����t�H���g", DX_CHARSET_DEFAULT);
	}

	// �A���j�����g���}��
	if (textFont == 5)
	{
		ChangeFont("�A���j�����g���}��", DX_CHARSET_DEFAULT);
	}
}

// �e�L�X�g�폜
void TextRelease()
{
	for (int i = 0; i < FONT_SIZE_MAX; i++)
	{
		if (RemoveFontResourceEx(font[i], FR_PRIVATE, NULL)) {}
		else {printfDx("�����̂� �G���[\n");	}
	}
}
