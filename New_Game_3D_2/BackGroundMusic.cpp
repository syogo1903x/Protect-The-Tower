#include "Common.h"

BackGroundMusic::BackGroundMusic(const char *_name)
{
	backGroundMusicHandle = LoadSoundMem(_name);
	// ‰¹—Ê‚Ìİ’è
	ChangeVolumeSoundMem(255 * 80 / 100, backGroundMusicHandle);
}

BackGroundMusic::~BackGroundMusic()
{

}

void BackGroundMusic::PlayBackGroundMusic()
{
	// Ä¶
	PlaySoundMem(backGroundMusicHandle, DX_PLAYTYPE_LOOP, TRUE);
}

void BackGroundMusic::OnePlayBackGroundMusic()
{
	// ˆê‰ñ‚¾‚¯Ä¶
	backGroundMusicCount = 0;
	backGroundMusicCount++;

	if (backGroundMusicCount == 1 && !isPronunciation)
	{
		isPronunciation = true;
		PlaySoundMem(backGroundMusicHandle, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void BackGroundMusic::StopBackGroundMusic()
{
	// ’â~
	StopSoundMem(backGroundMusicHandle);
	isPronunciation = false;
}

void BackGroundMusic::Release()
{
	// ‰ğ•ú
	DeleteSoundMem(backGroundMusicHandle);
	backGroundMusicHandle = NULL;
}
