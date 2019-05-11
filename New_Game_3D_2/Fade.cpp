#include "Fade.h"


Fade::Fade()
{
	DeleteGraph(fadeGraphHandle);
	fadeGraphHandle = NULL;

	DeleteGraph(fadeOutGraphHandle);
	fadeOutGraphHandle = NULL;

	fadeGraphHandle = LoadGraph("img/fade.png");
	fadeOutGraphHandle = LoadGraph("img/fadeout.png");
}

Fade::~Fade()
{
	DeleteGraph(fadeGraphHandle);
	fadeGraphHandle = NULL;

	DeleteGraph(fadeOutGraphHandle);
	fadeOutGraphHandle = NULL;
}

void Fade::Init()
{
	fadeInCount = 255;
	fadeOutCount = 0;
	time = 0;
}

// フェードイン だんだん出てくる スピード普通 
void Fade::FadeIn_Play()
{
	fadeInCount -= 50;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeInCount);
	DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.0f, 0.0f, fadeOutGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

// フェードイン だんだん消える
void Fade::FadeOut_Play()
{
	fadeOutCount += time;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeOutCount);
	DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.0f, 0.0f, fadeOutGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

// フェードイン だんだん出てくる スピード遅い
void Fade::SlowFadeIn_Play()
{
	fadeInCount -= 25;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeInCount);
	DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.0f, 0.0f, fadeGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

// フェードイン だんだん出てくる スピード早い
void Fade::FastFadeIn_Play()
{
	fadeInCount -= 100;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeInCount);
	DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.0f, 0.0f, fadeGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}


void Fade::TermsFadeOut_Play(char *_timer)
{
	if (_timer == "Fast") { time = 100; }
	else if (_timer == "Slow") { time = 25; }
	else { time = 50; }
}

bool Fade::FadeOutEnd()
{
	if (fadeOutCount > 250)
	{
		return true;
	}

	return false;
}

void Fade::TitleFadeIn_Play()
{
	fadeInCount -= 50;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeInCount);
	DrawRotaGraph(SCREEN_X / 2, SCREEN_Y / 2, 1.0f, 0.0f, fadeGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
