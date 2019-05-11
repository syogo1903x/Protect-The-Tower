#pragma once
#include "SceneBase.h"

class SoundEffect;

class SceneTitle :public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void Init() override;
	SceneBase *Update() override;
	void Draw() override;
	void Release() override;


private:
	int moouseGraphHandle[2];
	int mouseX;
	int mouseY;
	int animation;

	int titleGraphHandle[2];
	int titleModelHandle;
	int titlePushGraphHandle[2];

	int padInputSize;

	SoundEffect *se;

	int rogoGraphHandle;
	bool isAlhaBlend;
	int animationCount;
	float rotate;

	bool isDemo;
	bool isTitlePass = false;
};