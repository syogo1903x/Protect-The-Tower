#pragma once

class SoundEffect;

class Tower
{
public:
	// �R���X�g���N�^
	Tower();
	// �f�X�g���N�^
	~Tower();

	// ������
	void Init();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���
	void Release();
	// �E�F�[�u����
	void GameWaveString();

	// �Q�b�^�[
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

	// �Z�b�^�[
	static void SetLife(int _set) { life -= _set; }
	void SetHit(bool _set) { isHit = _set; }
	void SetLifeDamege(int _set) { lifeDamage = _set; }
	static void SetWaveInterval(bool _set) { isWaveInterval = _set; }


private:
	// �^���[���f��
	int towerModelHandle;
	// �ʒu
	VECTOR pos;

	// �̗�
	static int life;
	// �̗͌���
	int lifeDamage;

	// ���a
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

	//�e�X�e�[�W�̓��
	int difficultCount;

	// ���ʉ�
	SoundEffect *se;

	// �E�F�[�u�N���A�摜
	int weavClearGraphHandle[3];

	// �Q�[���I�[�o�[�J�E���g
	int gameOverTime;
	VECTOR towerSize;
};