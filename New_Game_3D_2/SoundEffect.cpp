#include "Common.h"

SoundEffect::SoundEffect(const char * _name)
{
	soundEffectMusicHandle = LoadSoundMem(_name);
	// ���ʂ̐ݒ�
	ChangeVolumeSoundMem(255 * 80 / 100, soundEffectMusicHandle);
	isPronunciation = false;
}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::PlaySoundEffect()
{
	// �Đ�
	PlaySoundMem(soundEffectMusicHandle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundEffect::OnePlaySoundEffect()
{
	// ��񂾂��Đ�
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
	// ��~
	StopSoundMem(soundEffectMusicHandle);
	isPronunciation = false;
}

void SoundEffect::Release()
{
	// ���
	DeleteSoundMem(soundEffectMusicHandle);
	soundEffectMusicHandle = NULL;
}
