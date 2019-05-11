#include "EnemyManager.h"

int EnemyManager::enemyCount;

// コンストラクタ
EnemyManager::EnemyManager()
{
	// モデルの入れ込み
	modelHandle[0] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ENEMY_MEDIUM));
	modelHandle[1] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ENEMY_SMALL));
	modelHandle[2] = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::ENEMY_BOSS));
}

// デストラクタ
EnemyManager::~EnemyManager()
{

}

// エネミー初期化
void EnemyManager::CreateEnemy()
{
	// ランダム初期化
	srand((unsigned int)time(NULL));

	// 敵カウント初期化
	enemyCount = 0;
	enemyEmergenceCount = 0;
	count = 0;

	// 中ボス　初期化
	for (int i = 0; i < 8; i++)
	{
		medium[i] = new MediumBoss();
		notMedium.push_back(medium[i]);
	}

	// 雑魚キャラ
	for (int i = 0; i < 20; i++)
	{
		enemy[i] = new Enemy();
		notEnemy.push_back(enemy[i]);
	}

	// ボスの初期化
	for (int i = 0; i < 4; i++)
	{
		boss[i] = new Boss();
		notBoss.push_back(boss[i]);
	}


	// 中ボス 未使用リスト登録
	if (!notMedium.empty())
	{
		for (notMediumItr = notMedium.begin(); notMediumItr != notMedium.end(); notMediumItr++)
		{
			(*notMediumItr)->SetPos(VGet(-300 + (float)(rand() % 500), 5, -400));
			(*notMediumItr)->Init(modelHandle[0]);
			(*notMediumItr)->SetColor(1.0f, 1.0f, 1.0f);
		}
	}

	// ザコ敵 未使用リスト登録
	if (!notEnemy.empty())
	{
		for (notEnemyItr = notEnemy.begin(); notEnemyItr != notEnemy.end(); notEnemyItr++)
		{
			(*notEnemyItr)->SetPos(VGet(-300 + (float)(rand() % 600), 5, -300));
			(*notEnemyItr)->Init(modelHandle[1]);
			MV1SetDifColorScale((*notEnemyItr)->GetModel(), GetColorF(0.1f, 0.1f, 0.1f, 1.0f));
		}
	}

	// ボス 未使用リスト登録
	if (!notBoss.empty())
	{
		for (notBossItr = notBoss.begin(); notBossItr != notBoss.end(); notBossItr++)
		{
			(*notBossItr)->SetPos(VGet(-300 + (float)(rand() % 600), 7, -300));
			(*notBossItr)->Init(modelHandle[2]);
			MV1SetScale((*notBossItr)->GetModel(), VGet(2.5f, 2.5f, 2.5f));
		}
	}
}

// エネミーの当たり判定更新
void EnemyManager::EnemyManagerUpdate(CharacterBase * _player, Stage * _stage)
{

	// ゲームが始まればカウントダウン
	if (SceneGame::GetStart())
	{
		enemyEmergenceCount++;
	}

	// 当たり判定
	if (!bossList.empty())
	{
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			// ボスとステージの当たり判定
			HitCheck::HitCheckPlayerToGound((*bossItr), _stage, 2.5f);
			// プレイヤーとボスの四角の当たり判定
			if (!(*bossItr)->GetDead())
			{
				HitCheck::HitCheckCirclePlayerToOtherPlayer(_player, (*bossItr));
			}
			// プレイヤーとボスの円の当たり判定
			if (!(*bossItr)->GetDead())
			{
				HitCheck::HitCheckBoxPlayerToBoss(_player, (*bossItr));
			}
		}
	}

	// 当たり判定
	if (!enemyList.empty())
	{
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			// ザコ敵と地面の当たり判定
			HitCheck::HitCheckPlayerToGound((*enemyItr), _stage, 1.0f);

			// プレイヤーとエネミーの四角の当たり判定
			if (!(*enemyItr)->GetDead()) 
			{
				HitCheck::HitCheckBoxPlayerToOtherPlayer(_player, (*enemyItr)); 
			}

			// プレイヤーとエネミーの円の当たり判定
			if (!(*enemyItr)->GetDead())
			{
				HitCheck::HitCheckCirclePlayerToOtherPlayer(_player, (*enemyItr));
			}
			//HitCheck::HitCheckCirclePlayerToOtherPlayer((*enemyItr), (*enemyItr));
		}
	}

	// 当たり判定
	if (!mediumList.empty())
	{
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{

			// 中ボスとステージの当たり判定
			HitCheck::HitCheckPlayerToGound((*mediumItr), _stage, 1.0f);
			// プレイヤーとエネミーの四角の当たり判定
			if (!(*mediumItr)->GetDead())
			{
				HitCheck::HitCheckBoxPlayerToOtherPlayer(_player, (*mediumItr));
			}
			// プレイヤーとエネミーの円の当たり判定
			if (!(*mediumItr)->GetDead())
			{
				HitCheck::HitCheckCirclePlayerToOtherPlayer(_player, (*mediumItr));
			}
		}
	}

}

// 体力描画
void EnemyManager::EnemyManagerDraw(CharacterBase * _player, Camera *_camera)
{

	// ザコ敵の範囲内にいればザコ敵の体力を表示
	if (!enemyList.empty())
	{
		// 使用リスト
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			if (HitCheck::HitCheckCirclePlayerToEnemy(_player, (*enemyItr)))
			{
				if ((*enemyItr)->GetLife() > 0)
				{
					DrawLifeBoxSmallEnemy((*enemyItr), _camera);
				}
			}
		}
	}


	// 中ボスの範囲内にいれば中ボスの体力を表示
	if (!mediumList.empty())
	{
		// 使用リスト
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{
			if (HitCheck::HitCheckCirclePlayerToEnemy(_player, (*mediumItr)))
			{
				if ((*mediumItr)->GetLife() > 0)
				{
					DrawLifeBoxMediumBoss((*mediumItr), _camera);
				}
			}
		}
	}


	// ボスの範囲内にいればボスの体力を表示
	if (!bossList.empty())
	{
		// 使用リスト
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			// ボスの範囲内にいればボスの体力を表示
			if (HitCheck::HitCheckCirclePlayerToEnemy(_player, (*bossItr)))
			{
				if ((*bossItr)->GetLife() > 0)
				{
					DrawLifeBoxBoss((*bossItr), _camera);
				}
			}
		}
	}
}

// 更新
void EnemyManager::Update(CharacterBase *_player, Camera * _camera, Tower *_tower)
{

	// 未使用リスト
	// エネミーの出現条件をタワーのウェーブごとに変える
	if (enemyEmergenceCount % Tower::GetSmallEnemy() == 1)
	{
		if (!notEnemy.empty())
		{
			for (notEnemyItr = notEnemy.begin(); notEnemyItr != notEnemy.end(); notEnemyItr++)
			{
				(*notEnemyItr)->SetPos((*notEnemyItr)->GetEnemyPos());
				(*notEnemyItr)->SetEnemy();
				// 未使用リストから使用リストへ
				enemyList.push_back(*notEnemyItr);
				notEnemy.remove(*notEnemyItr);
				break;
			}
		}
	}


	// エネミーの出現条件をタワーのウェーブごとに変える
	if (enemyEmergenceCount % Tower::GetMediumEnemy() == 1)
	{
		// ウェーブが0ではないときに出現
		if (Tower::GetWave() != 0)
		{
			// 未使用リスト
			if (!notMedium.empty())
			{
				for (notMediumItr = notMedium.begin(); notMediumItr != notMedium.end(); notMediumItr++)
				{
					(*notMediumItr)->SetPos((*notMediumItr)->GetEnemyPos());
					(*notMediumItr)->SetMedium();
					// 未使用リストから使用リストへ
					mediumList.push_back(*notMediumItr);
					notMedium.remove(*notMediumItr);
					break;
				}
			}
		}
	}

	// エネミーの出現条件をタワーのウェーブごとに変える
	if (enemyEmergenceCount % Tower::GetBigEnemy() == 1)
	{
		// ウェーブが1より上であれば出現
		if (Tower::GetWave() > 1)
		{
			// ボス
			if (!notBoss.empty())
			{
				for (notBossItr = notBoss.begin(); notBossItr != notBoss.end(); notBossItr++)
				{
					(*notBossItr)->SetPos((*notBossItr)->GetEnemyPos());
					(*notBossItr)->SetBoss();
					// 未使用リストから使用リストへ
					bossList.push_back(*notBossItr);
					notBoss.remove(*notBossItr);
					break;
				}
			}
		}
	}


	// 雑魚 更新
	if (!enemyList.empty())
	{
		// 使用リスト
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			if ((*enemyItr)->GetLife() < 0)
			{
				// タワーにヒットしていない時に
				if (!(*enemyItr)->GetHit())
				{
					// プレイヤーの必殺技ゲージをためる
					_player->SetDeathBlowCount(5.f);
				}

				// 使用リストから未使用リストへ
				notEnemy.push_back(*enemyItr);
				enemyList.remove(*enemyItr);
				break;
			}

			if (SceneGame::GetStart())
			{
				(*enemyItr)->EnemyUpdate(_player, _tower);
			}

			(*enemyItr)->Update(*_camera);
		}
	}

	// 中ボス 更新
	if (!mediumList.empty())
	{
		// 使用リスト
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{
			// 出現エフェクト
			//if (enemyEmergenceCount % Tower::GetMediumEnemy() == 1)
			//{
			//	EFFECT.UpdateAppearMediumBoss((*mediumItr));
			//}

			if ((*mediumItr)->GetLife() < 0)
			{
				// タワーにヒットしていない時に
				if (!(*mediumItr)->GetHit())
				{
					// プレイヤーの必殺技ゲージをためる
					_player->SetDeathBlowCount(10.f);
				}

				// 使用リストから未使用リストへ
				notMedium.push_back(*mediumItr);
				mediumList.remove(*mediumItr);
				break;
			}

			if (SceneGame::GetStart())
			{
				(*mediumItr)->EnemyUpdate(_player, _tower);
			}

			(*mediumItr)->Update(*_camera);
		}
	}

	// ボス更新
	if (!bossList.empty())
	{
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			// 出現エフェクト
			//if (enemyEmergenceCount % Tower::GetBigEnemy() == 1)
			//{
			//	EFFECT.UpdateAppearBoss((*bossItr));
			//}

			if ((*bossItr)->GetLife() < 0)
			{
				// タワーにヒットしていない時に
				if (!(*bossItr)->GetHit())
				{
					// プレイヤーの必殺技ゲージをためる
					_player->SetDeathBlowCount(20.f);
				}

				// 使用リストから未使用リストへ
				notBoss.push_back(*bossItr);
				bossList.remove(*bossItr);

				break;
			}

			if (SceneGame::GetStart())
			{
				(*bossItr)->EnemyUpdate(_player, _tower);
			}
			(*bossItr)->Update(*_camera);
		}
	}
}

// 描画
void EnemyManager::Draw()
{
	// 中ボス 描画
	if (!mediumList.empty())
	{
		for (mediumItr = mediumList.begin(); mediumItr != mediumList.end(); mediumItr++)
		{
			(*mediumItr)->Draw();
		}
	}

	// 雑魚 描画
	if (!enemyList.empty())
	{
		for (enemyItr = enemyList.begin(); enemyItr != enemyList.end(); enemyItr++)
		{
			(*enemyItr)->Draw();
		}
	}

	// ボス 更新
	if (!bossList.empty())
	{
		for (bossItr = bossList.begin(); bossItr != bossList.end(); bossItr++)
		{
			(*bossItr)->Draw();
		}
	}

	// ボスのエフェクト
	for (int i = 0; i < 4; i++)
	{
		EFFECT.UpdateBoss(boss, i);
		if (!boss[i]->GetDead()) { EFFECT.UpdateDownBoss(boss, i); }
	}
	// 雑魚敵のエフェクト
	for (int i = 0; i < 20; i++)
	{
		if (!enemy[i]->GetDead()) { EFFECT.UpdateDownSmallEnemy(enemy, i); }
	}
	// 中ボスのエフェクト
	for (int i = 0; i < 8; i++)
	{
		if (!medium[i]->GetDead()) { EFFECT.UpdateDownMediumBoss(medium, i); }
	}

}

// 解放
void EnemyManager::Release()
{
	// 中ボス
	for (int i = 0; i < 8; i++)
	{
		medium[i]->Release();
		medium[i] = NULL;
		delete(medium[i]);
	}

	// 雑魚
	for (int i = 0; i < 20; i++)
	{
		enemy[i]->Release();
		enemy[i] = NULL;
		delete(enemy[i]);
	}

	// ボス
	for (int i = 0; i < 4; i++)
	{
		boss[i]->Release();
		boss[i] = NULL;
		delete(boss[i]);
	}

	// 各モデルの開放
	for (int i = 0; i < 3; i++)
	{
		MV1DeleteModel(modelHandle[i]);
		modelHandle[i] = NULL;
	}
}
