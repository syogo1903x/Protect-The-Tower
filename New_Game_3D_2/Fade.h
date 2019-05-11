#pragma once
#include "Common.h"

class Fade
{
public:
	~Fade();

	static Fade &FadeInstance()
	{
		static Fade instance;
		return instance;
	}


	void Init();
	
	void FadeIn_Play();
	void FadeOut_Play();

	void SlowFadeIn_Play();

	void FastFadeIn_Play();

	void TermsFadeOut_Play(char* _timer);
	bool FadeOutEnd();
	void TitleFadeIn_Play();


private:
	Fade();

	int fadeGraphHandle;
	int fadeOutGraphHandle;

	int fadeInCount;
	int fadeOutCount;

	int time;

};

#define FADE			Fade::FadeInstance()