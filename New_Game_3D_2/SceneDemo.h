#pragma once
#include "SceneBase.h"

class BackGroundMusic;

class SceneDemo :public SceneBase
{
public:
	SceneDemo();
	~SceneDemo();

	void Init() override;
	SceneBase *Update() override;
	void Draw() override;
	void Release() override;

private:
	int videoMovieHandle;
	int circleGraphHandle;
	int count;
	int time;
	VECTOR demoPos;
	int alha;
	bool isPush;
};