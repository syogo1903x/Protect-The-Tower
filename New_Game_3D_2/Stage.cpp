#include "Common.h"

float Stage::dangerModelTransmission[4];

Stage::Stage()
{

}

Stage::~Stage()
{
	//Release();
}

void Stage::Init(char *_stage)
{
	isFailure = false;
	// ステージの生成
	modelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::GAMESTAGE));

	// スカイドームの読み込み
	skydomeModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::SKYDOOM));

	if (modelHandle < 0)
	{
		isFailure = true;
		// printfDx("ステージモデル読み込みエラー\n");
	}

	pos = VGet(0, 0, 0);

	// ステージでサイズの変更
	if (_stage == "stage/白玉楼ver0.93/白玉楼.pmx") { MV1SetScale(modelHandle, VGet(2, 2, 2)); }
	if (_stage == "stage/ラグビーグラウンド1.05/ラグビーグラウンド（芝生）.pmx") { MV1SetScale(modelHandle, VGet(1, 1, 1)); }
	if (_stage == "stage/月の都風弾幕ステージ/月の都風弾幕ステージ.pmx") { MV1SetScale(modelHandle, VGet(4, 2, 1)); }

	// 範囲外に出ないようにする壁のモデル
	for (int i = 0; i < 4; i++)
	{
		dangerModelHandle[i] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::GAMESTAGE_OUT));
		MV1SetScale(dangerModelHandle[i], VGet(4.25f, 5, 6));
		dangerModelTransmission[i] = 0.0f;
	}

	// 壁モデルの位置設定
	MV1SetPosition(dangerModelHandle[0], VGet(320, 0, 0));
	MV1SetRotationXYZ(dangerModelHandle[0], VGet(0, 1.57f, 0));
	MV1SetPosition(dangerModelHandle[1], VGet(0, 0, 260));
	MV1SetPosition(dangerModelHandle[2], VGet(-320, 0, 0));
	MV1SetRotationXYZ(dangerModelHandle[2], VGet(0, 1.57f, 0));
	MV1SetPosition(dangerModelHandle[3], VGet(0, 0, -430));

	MV1SetScale(skydomeModelHandle, VGet(2, 2, 2));
	count = 0;
}

// 更新
void Stage::Update()
{
	// 回転
	count += 0.0005f;
	MV1SetRotationXYZ(skydomeModelHandle, VGet(0, count, 0));

	// ステージの位置設定
	MV1SetPosition(modelHandle, pos);
	MV1SetPosition(skydomeModelHandle, pos);
}

// 描画
void Stage::Draw()
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(skydomeModelHandle);

	for (int i = 0; i < 4; i++)
	{
		if (dangerModelTransmission[i] > 1.0f) { dangerModelTransmission[i] = 1.0f; }
		if (dangerModelTransmission[i] < 0.0f) { dangerModelTransmission[i] = 0.0f; }

		MV1SetOpacityRate(dangerModelHandle[i], dangerModelTransmission[i]);
		MV1DrawModel(dangerModelHandle[i]);
	}
}

// 解放
void Stage::Release()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	MV1DeleteModel(skydomeModelHandle);
	skydomeModelHandle = NULL;


	for (int i = 0; i < 4; i++)
	{
		MV1DeleteModel(dangerModelHandle[i]);
		dangerModelHandle[i] = NULL;
	}
}
