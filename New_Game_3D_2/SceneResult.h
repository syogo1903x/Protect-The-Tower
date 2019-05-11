#pragma once
#include "SceneBase.h"

class SoundEffect;

class SceneResult :public SceneBase
{
public:
	SceneResult();
	~SceneResult();

	void Init() override;
	SceneBase *Update() override;
	void Draw() override;
	void Release() override;

	static void CreateModel();

private:

	int playerFallGraphHandle;
	int playerGraphHandle[5];
	int playerLandGraphHandle;
	int playerLandingGraphHandle[5];

	int resultGraphHandle;
	int resultWinOrLoseGraphHandle;

	VECTOR pos;
	float bound;
	int boundCount;
	bool isFall;

	SoundEffect *se;

	int resultPushGraphHandle[2];
	float count;
	// 
	static int playerModelHandle;
	int animAttachIndex;
};
