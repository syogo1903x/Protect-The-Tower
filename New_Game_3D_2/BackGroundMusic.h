#pragma once


class BackGroundMusic
{
public:
	BackGroundMusic(const char *_name);
	~BackGroundMusic();

	virtual void PlayBackGroundMusic();
	void OnePlayBackGroundMusic();
	virtual void StopBackGroundMusic();
	virtual void Release();

protected:
	int backGroundMusicHandle;
	int backGroundMusicCount;
	bool isPronunciation;



};
