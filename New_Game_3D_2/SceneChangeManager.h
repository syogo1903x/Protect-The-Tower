#pragma once
#include"SceneBase.h"

class SceneChange final
{
public:
	SceneChange();
	~SceneChange();

	void Init();
	void Update();
	void Release();
	void Draw();

	void SetFirstScene(SceneBase *scenebase) { nowScene = scenebase; }

	// セッター
	static void SetPadOrKey(bool _set) { isPad = _set; }
	static void SetEscape(bool _set) { isEscape = _set; }

	// ゲッター
	const static bool GetPadOrKey() { return isPad; }
	const static bool GetEscape() { return isEscape; }


private:
	SceneBase *nowScene;
	SceneBase *prevScene;

	static bool isPad;
	static bool isEscape;

};