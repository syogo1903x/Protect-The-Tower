#pragma once

class SoundEffect;

class Tower
{
public:
	// コンストラクタ
	Tower();
	// デストラクタ
	~Tower();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 解放
	void Release();
	// ウェーブ文字
	void GameWaveString();

	// ゲッター
	VECTOR GetPos() { return pos; }
	float GetRadius() { return radius; }
	static int GetLife() { return life; }
	bool GetHit() { return isHit; }
	static int GetWave() { return waveNumber; }
	static int GetSmallEnemy() { return smallEnemyCount; }
	static int GetMediumEnemy() { return mediumEnemyCount; }
	static int GetBigEnemy() { return bigEnemyCount; }
	static bool GetWaveInterval() { return isWaveInterval; }
	static int GetWaveIntervalCount() { return waveIntervalCount; }
	int GetTowerCount() { return gameOverTime; }

	// セッター
	static void SetLife(int _set) { life -= _set; }
	void SetHit(bool _set) { isHit = _set; }
	void SetLifeDamege(int _set) { lifeDamage = _set; }
	static void SetWaveInterval(bool _set) { isWaveInterval = _set; }


private:
	// タワーモデル
	int towerModelHandle;
	// 位置
	VECTOR pos;

	// 体力
	static int life;
	// 体力減少
	int lifeDamage;

	// 半径
	float radius;
	bool isHit;
	int damageCount;

	static int waveNumber;
	static int smallEnemyCount;
	static int mediumEnemyCount;
	static int bigEnemyCount;

	static bool isWaveInterval;
	static int waveIntervalCount;
	bool isWave[3];

	static int waveMoveXCount;
	static int waveMoveYCount;

	//各ステージの難しさ
	int difficultCount;

	// 効果音
	SoundEffect *se;

	// ウェーブクリア画像
	int weavClearGraphHandle[3];

	// ゲームオーバーカウント
	int gameOverTime;
	VECTOR towerSize;
};