#pragma once

class SoundEffect;

class Tower
{
public:
	Tower();
	~Tower();

	void Init();
	void Update();
	void Draw();
	void Release();

	void Atack();
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
	int towerModelHandle;
	VECTOR pos;

	static int life;
	int lifeDamage;

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

	int difficultCount;

	// 効果音
	SoundEffect *se;

	int weavClearGraphHandle[3];

	int gameOverTime;
	VECTOR towerSize;
};