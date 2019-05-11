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

// テキストロード
void ChangeTextFont()
{
	font[GONTA] = "font/GD-TiVangerionJA-010.otf";
	if (AddFontResourceEx(font[GONTA], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("エラー\n"); }

	font[SANSERIF] = "font/GN-Kin-iro_SansSerif.ttf";
	if (AddFontResourceEx(font[SANSERIF], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("エラー\n"); }

	//font_002 = "font/FZGonta-kana/FZゴンタかな.otf";
	font[KEION] = "font/keifont.ttf";
	if (AddFontResourceEx(font[KEION], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("エラー\n"); }

	font[KIRIN] = "font/kirin-Regular.ttf";
	if (AddFontResourceEx(font[KIRIN], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("エラー\n"); }

	font[TORAMAN] = "font/toroman.ttf";
	if (AddFontResourceEx(font[TORAMAN], FR_PRIVATE, NULL) > 0) {}
	else { printfDx("エラー\n"); }

}

///////////////////////////////////
// テキスト表示
// 0 : テキスト デフォルト
// 1 : テキスト かっこいい
// 2 : テキスト きんいろサンセリフ
// 3 : テキスト ゴンタかな
// 4 : テキスト キリンフォント
// 5 : テキスト アンニャントロマン
//////////////////////////////////
void TextFontDraw(int textFont)
{
	// メイリオ
	if (textFont == 0)
	{
		ChangeFont("メイリオ", DX_CHARSET_DEFAULT);
	}

	// ゴンタカナ
	if (textFont == 1)
	{
		ChangeFont("GD-TiVangerionJA-OTF", DX_CHARSET_DEFAULT);
	}

	// サンセリフ
	if (textFont == 2)
	{
		ChangeFont("GN-きんいろサンセリフ", DX_CHARSET_DEFAULT);
	}

	// けいおんフォント
	if (textFont == 3)
	{
		//ChangeFont("FZゴンタかな", DX_CHARSET_DEFAULT);
		ChangeFont("けいふぉんと", DX_CHARSET_DEFAULT);
	}

	// キリンフォント
	if (textFont == 4)
	{
		ChangeFont("キリンフォント", DX_CHARSET_DEFAULT);
	}

	// アンニャントロマン
	if (textFont == 5)
	{
		ChangeFont("アンニャントロマン", DX_CHARSET_DEFAULT);
	}
}

// テキスト削除
void TextRelease()
{
	for (int i = 0; i < FONT_SIZE_MAX; i++)
	{
		if (RemoveFontResourceEx(font[i], FR_PRIVATE, NULL)) {}
		else {printfDx("消すのが エラー\n");	}
	}
}
