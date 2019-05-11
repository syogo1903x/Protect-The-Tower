#pragma once

enum HIT_CHECK
{
	WALL_RIGHT,
	WALL_LEFT,
	WALL_FRONT,
	WALL_BACK,
	WALL_UP
};

class Stage
{
public:
	~Stage();

	static Stage &StageInctance()
	{
		static Stage stageInstance;
		return stageInstance;
	}

	void Init(char *_stage);
	void Update();
	void Draw();
	void Release();

	const int &GetModel() const { return modelHandle; }

	// セッター
	static void SetDangerTrans(int i, float _set) { dangerModelTransmission[i] += _set; }
	void SetFailur(bool _set) { isFailure = _set; }

	// ゲッター
	bool GetFailur() { return isFailure; }

private:
	Stage();
	int modelHandle;
	int skydomeModelHandle;
	float count;
	VECTOR pos;

	int dangerModelHandle[4];
	static float dangerModelTransmission[4];
	bool isFailure;
};

#define STAGE				Stage::StageInctance()