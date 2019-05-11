#include "Common.h"

int Tower::waveNumber;
int Tower::smallEnemyCount;
int Tower::mediumEnemyCount;
int Tower::bigEnemyCount;
int Tower::waveMoveXCount;
int Tower::waveMoveYCount;
int Tower::waveIntervalCount;
int Tower::life;

bool Tower::isWaveInterval;

Tower::Tower()
{

}

Tower::~Tower()
{

}

// 初期化
void Tower::Init()
{
	// ウェーブの初期化
	waveNumber = 0;

	// モデル
	towerModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::TOWER));
	pos = VGet(0, 0, 100);
	MV1SetScale(towerModelHandle, VGet(2, 2, 2));

	// 効果音読み込み
	se = new SoundEffect("Music/SE/grap1.mp3");

	if (SceneMenu::GetStage() == "stage/白玉楼ver0.93/白玉楼.pmx") { difficultCount = 0; }
	if (SceneMenu::GetStage() == "stage/ラグビーグラウンド1.05/ラグビーグラウンド（芝生）.pmx") { difficultCount = 20; }
	if (SceneMenu::GetStage() == "stage/月の都風弾幕ステージ/月の都風弾幕ステージ.pmx") { difficultCount = 40; }

	// タワー最大体力
	life = 100;
	radius = 5.0f;
	damageCount = 0;

	isHit = false;

	for (int i = 0; i < 3; i++)
	{
		isWave[i] = false;
	}

	isWaveInterval = false;
	waveIntervalCount = 0;

	smallEnemyCount = 120;
	mediumEnemyCount = 120;
	bigEnemyCount = 120;

	waveMoveYCount = 0;
	waveMoveXCount = 0;

	weavClearGraphHandle[0] = LoadGraph("img/wave1.png");
	weavClearGraphHandle[1] = LoadGraph("img/wave2.png");
	weavClearGraphHandle[2] = LoadGraph("img/wave3.png");

	gameOverTime = 0;
	towerSize = VGet(2, 2, 2);

}

// 更新
void Tower::Update()
{
	// ウェーブの変更
	if (SceneGame::GetTimer() == 30) { waveNumber = 1; isWave[0] = true; }
	if (SceneGame::GetTimer() == 60) { waveNumber = 2; isWave[1] = true; }
	if (SceneGame::GetTimer() == 90) { waveNumber = 3; isWave[2] = true; }

	// ウェーブの間隔
	for (int i = 0; i < 3; i++)
	{
		if (isWave[i])
		{
			waveIntervalCount++;
			waveMoveXCount += 100;

			if (waveIntervalCount == 1)
			{
				isWaveInterval = true;
			}

			if (waveIntervalCount >= 539)
			{
				isWaveInterval = false;
			}

			if (waveIntervalCount >= 600)
			{
				isWave[i] = false;
				waveIntervalCount = 0;
				waveMoveXCount = 0;
				waveMoveYCount = 0;
			}
		}
	}

	// ウェーブインターバルではなければ
	if (!isWaveInterval)
	{
		// 現在のウェーブでの敵の出現率
		switch (waveNumber)
		{
		case 0:
			smallEnemyCount = 120 - difficultCount;
			break;

		case 1:
			smallEnemyCount = 120 - difficultCount;
			mediumEnemyCount = 90 - difficultCount;
			break;

		case 2:
			smallEnemyCount = 60 - difficultCount;
			mediumEnemyCount = 90 - difficultCount;
			bigEnemyCount = 120 - difficultCount;
			break;
		case 3:
			smallEnemyCount = 1000000000;
			mediumEnemyCount = 1000000000;
			bigEnemyCount = 1000000000;
			break;

		default:
			break;
		}
	}
	else
	{
		smallEnemyCount = 1000000000;
		mediumEnemyCount = 1000000000;
		bigEnemyCount = 1000000000;
	}

	// 当たった時にちかちかさせる
	float alha;

	if (isHit && life > 0)
	{
		// エフェクト再生
		EFFECT.UpdateTowerHit(this);

		damageCount++;
		if (damageCount == 1)
		{
			// 体力減少
			life -= lifeDamage;
			// 効果音再生
			se->PlaySoundEffect();
		}

		if (damageCount >= 60)
		{
			damageCount = 0;
			isHit = false;
		}

		if (damageCount % 2 == 0)
		{
			alha = 1.0f;
		}
		else
		{
			alha = 0.8f;
		}

		MV1SetOpacityRate(towerModelHandle, alha);
	}

	// 体力最大
	if (life >= 100) { life = 100; }

	if (SceneGame::GetGameOver())
	{
		// カメラが規定値に行けばカウント開始
		if (Camera::GetCameraSetComplet()) { gameOverTime++; }

		// カウントごとの処理
		if (gameOverTime > 0 && gameOverTime <= 10) { towerSize.x += 0.1f; towerSize.z += 0.1f; }
		if (gameOverTime > 10 && gameOverTime <= 20) { towerSize.x -= 0.1f; towerSize.z -= 0.1f; }
		if (gameOverTime > 20 && gameOverTime <= 30) { towerSize.x += 0.1f; towerSize.z += 0.1f; }
		if (gameOverTime > 30 && gameOverTime <= 40) { towerSize.x -= 0.1f; towerSize.z -= 0.1f; }
		if (gameOverTime > 60 && gameOverTime <= 70) { towerSize.y += 0.1f; }
		if (gameOverTime > 70 && gameOverTime <= 80) { towerSize.y -= 0.1f; }
		if (gameOverTime > 80 && gameOverTime <= 280) { EFFECT.UpdateTowerDown(this); }

		if (gameOverTime > 280)
		{
			towerSize.x -= 0.1f;
			towerSize.y -= 0.1f;
			towerSize.z -= 0.1f;

			EFFECT.UpdateTowerOver(this);
		}

		// タワーのモデルサイズ最大値
		if (towerSize.x < 0) { towerSize.x = 0; }
		if (towerSize.y < 0) { towerSize.y = 0; }
		if (towerSize.z < 0) { towerSize.z = 0; }

		// モデルサイズ更新
		MV1SetScale(towerModelHandle, VGet(towerSize.x, towerSize.y, towerSize.z));
	}

	// タワー体力が0以下にならないようにする
	if (life <= 0) { life = 0; }
	//if (KEY_INPUT.GetKey(KEY_INPUT_2) == KEY_ON) { life = 0; }

	MV1SetPosition(towerModelHandle, pos);
	MV1SetRotationXYZ(towerModelHandle, VGet(0, 0, 0));
}

// 描画
void Tower::Draw()
{
	MV1DrawModel(towerModelHandle);

	if (waveMoveXCount >= 2400)
	{
		if (waveIntervalCount >= 570) { waveMoveYCount += 20; }
		waveMoveXCount = 2400;
	}
}

void Tower::Release()
{
	// 削除
	MV1DeleteModel(towerModelHandle);
	towerModelHandle = NULL;

	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		se = NULL;
	}

	//
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(weavClearGraphHandle[i]);
		weavClearGraphHandle[i] = NULL;
	}
}

void Tower::Atack()
{

}

// ウェーブクリア時のクリア表示
void Tower::GameWaveString()
{
	SetFontSize(DEFAULT_FONT_SIZE * 10);
	if (waveNumber == 1) { DrawRotaGraph(SCREEN_X * 2 - waveMoveXCount, (int)(SCREEN_Y / 3.f) - waveMoveYCount, 1.0f, 0.0f, weavClearGraphHandle[0], TRUE); }
	if (waveNumber == 2) { DrawRotaGraph(SCREEN_X * 2 - waveMoveXCount, (int)(SCREEN_Y / 3.f) - waveMoveYCount, 1.0f, 0.0f, weavClearGraphHandle[1], TRUE); }
	if (waveNumber == 3) { DrawRotaGraph(SCREEN_X * 2 - waveMoveXCount, (int)(SCREEN_Y / 3.f) - waveMoveYCount, 1.0f, 0.0f, weavClearGraphHandle[2], TRUE); }
	SetFontSize(DEFAULT_FONT_SIZE);
}
