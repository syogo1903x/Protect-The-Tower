#include "Common.h"

SoundEffect::SoundEffect(const char * _name)
{
	soundEffectMusicHandle = LoadSoundMem(_name);
	// ‰¹—Ê‚Ìİ’è
	ChangeVolumeSoundMem(255 * 80 / 100, soundEffectMusicHandle);
	isPronunciation = false;
}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::PlaySoundEffect()
{
	// Ä¶
	PlaySoundMem(soundEffectMusicHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundEffect::OnePlaySoundEffect()
{
	// ˆê‰ñ‚¾‚¯Ä¶
	soundEffectMusicCount = 0;
	soundEffectMusicCount++;

	if (soundEffectMusicCount == 1 && !isPronunciation)
	{
		isPronunciation = true;
		PlaySoundMem(soundEffectMusicHandle, DX_PLAYTYPE_BACK, TRUE);
	}

}

void SoundEffect::StopSoundEffect()
{
	// ’â~
	StopSoundMem(soundEffectMusicHandle);
	isPronunciation = false;
}

void SoundEffect::Release()
{
	// ‰ğ•ú
	DeleteSoundMem(soundEffectMusicHandle);
	soundEffectMusicHandle = NULL;
}
