#include "Common.h"

BackGroundMusic::BackGroundMusic(const char *_name)
{
	backGroundMusicHandle = LoadSoundMem(_name);
	// ���ʂ̐ݒ�
	ChangeVolumeSoundMem(255 * 80 / 100, backGroundMusicHandle);
}

BackGroundMusic::~BackGroundMusic()
{

}

void BackGroundMusic::PlayBackGroundMusic()
{
	// �Đ�
	PlaySoundMem(backGroundMusicHandle, DX_PLAYTYPE_LOOP, TRUE);
}

void BackGroundMusic::OnePlayBackGroundMusic()
{
	// ��񂾂��Đ�
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
	// ��~
	StopSoundMem(backGroundMusicHandle);
	isPronunciation = false;
}

void BackGroundMusic::Release()
{
	// ���
	DeleteSoundMem(backGroundMusicHandle);
	backGroundMusicHandle = NULL;
}
