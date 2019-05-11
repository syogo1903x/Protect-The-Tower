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

	// シングルトン
	static Stage &StageInctance()
	{
		static Stage stageInstance;
		return stageInstance;
	}

	// 初期化
	void Init(char *_stage);
	// 更新
	void Update();
	// 描画
	void Draw();
	// 解放
	void Release();

	// ゲッター
	bool GetFailur() { return isFailure; }
	const int &GetModel() const { return modelHandle; }

	// セッター
	static void SetDangerTrans(int i, float _set) { dangerModelTransmission[i] += _set; }
	void SetFailur(bool _set) { isFailure = _set; }

private:
	Stage();

	// ステージモデル
	int modelHandle;
	// スカイドームモデル
	int skydomeModelHandle;
	float count;
	VECTOR pos;

	int dangerModelHandle[4];
	static float dangerModelTransmission[4];
	bool isFailure;
};

#define STAGE				Stage::StageInctance()