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

// ������
void Tower::Init()
{
	// �E�F�[�u�̏�����
	waveNumber = 0;

	// ���f��
	towerModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::TOWER));
	pos = VGet(0, 0, 100);
	MV1SetScale(towerModelHandle, VGet(2, 2, 2));

	// ���ʉ��ǂݍ���
	se = new SoundEffect("Music/SE/grap1.mp3");

	if (SceneMenu::GetStage() == "stage/���ʘOver0.93/���ʘO.pmx") { difficultCount = 0; }
	if (SceneMenu::GetStage() == "stage/���O�r�[�O���E���h1.05/���O�r�[�O���E���h�i�Ő��j.pmx") { difficultCount = 20; }
	if (SceneMenu::GetStage() == "stage/���̓s���e���X�e�[�W/���̓s���e���X�e�[�W.pmx") { difficultCount = 40; }

	// �^���[�ő�̗�
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

// �X�V
void Tower::Update()
{
	// �E�F�[�u�̕ύX
	if (SceneGame::GetTimer() == 30) { waveNumber = 1; isWave[0] = true; }
	if (SceneGame::GetTimer() == 60) { waveNumber = 2; isWave[1] = true; }
	if (SceneGame::GetTimer() == 90) { waveNumber = 3; isWave[2] = true; }

	// �E�F�[�u�̊Ԋu
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

	// �E�F�[�u�C���^�[�o���ł͂Ȃ����
	if (!isWaveInterval)
	{
		// ���݂̃E�F�[�u�ł̓G�̏o����
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

	// �����������ɂ�������������
	float alha;

	if (isHit && life > 0)
	{
		// �G�t�F�N�g�Đ�
		EFFECT.UpdateTowerHit(this);

		damageCount++;
		if (damageCount == 1)
		{
			// �̗͌���
			life -= lifeDamage;
			// ���ʉ��Đ�
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

	// �̗͍ő�
	if (life >= 100) { life = 100; }

	if (SceneGame::GetGameOver())
	{
		// �J�������K��l�ɍs���΃J�E���g�J�n
		if (Camera::GetCameraSetComplet()) { gameOverTime++; }

		// �J�E���g���Ƃ̏���
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

		// �^���[�̃��f���T�C�Y�ő�l
		if (towerSize.x < 0) { towerSize.x = 0; }
		if (towerSize.y < 0) { towerSize.y = 0; }
		if (towerSize.z < 0) { towerSize.z = 0; }

		// ���f���T�C�Y�X�V
		MV1SetScale(towerModelHandle, VGet(towerSize.x, towerSize.y, towerSize.z));
	}

	// �^���[�̗͂�0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	if (life <= 0) { life = 0; }
	//if (KEY_INPUT.GetKey(KEY_INPUT_2) == KEY_ON) { life = 0; }

	MV1SetPosition(towerModelHandle, pos);
	MV1SetRotationXYZ(towerModelHandle, VGet(0, 0, 0));
}

// �`��
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
	// �폜
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

// �E�F�[�u�N���A���̃N���A�\��
void Tower::GameWaveString()
{
	SetFontSize(DEFAULT_FONT_SIZE * 10);
	if (waveNumber == 1) { DrawRotaGraph(SCREEN_X * 2 - waveMoveXCount, (int)(SCREEN_Y / 3.f) - waveMoveYCount, 1.0f, 0.0f, weavClearGraphHandle[0], TRUE); }
	if (waveNumber == 2) { DrawRotaGraph(SCREEN_X * 2 - waveMoveXCount, (int)(SCREEN_Y / 3.f) - waveMoveYCount, 1.0f, 0.0f, weavClearGraphHandle[1], TRUE); }
	if (waveNumber == 3) { DrawRotaGraph(SCREEN_X * 2 - waveMoveXCount, (int)(SCREEN_Y / 3.f) - waveMoveYCount, 1.0f, 0.0f, weavClearGraphHandle[2], TRUE); }
	SetFontSize(DEFAULT_FONT_SIZE);
}
