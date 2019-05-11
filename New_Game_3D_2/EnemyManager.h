#pragma once
#include "Camera.h"
#include "Enemy.h"
#include "MediumBoss.h"
#include "Boss.h"
#include <list>

using namespace std;

class Enemy;
class MediumBoss;
class Boss;
class Stage;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemy();

	void EnemyManagerUpdate(CharacterBase *_player, Stage *_stage);
	void EnemyManagerDraw(CharacterBase *_player, Camera *_camera);
	void Update(CharacterBase *_player, Camera *_camera, Tower *_tower);
	void Draw();

	void Release();

	// セッター
	static void SetEnemyCount(int _count) { enemyCount += _count; }


	// ゲッター
	// ライフ取得
	const int &GetEnemyCount() const { return enemyCount; }

	CharacterBase &GetBoss(int _set) { return *boss[_set]; }
	CharacterBase &GetEnemy(int _set) { return *enemy[_set]; }
	CharacterBase &GetMedium(int _set) { return *medium[_set]; }

private:
	int modelHandle[3];
	int count;
	static int enemyCount;

	// エネミーリスト
	Enemy *enemy[20];
	list<Enemy*> enemyList;
	list<Enemy*>::iterator enemyItr;
	list<Enemy*> notEnemy;
	list<Enemy*>::iterator notEnemyItr;


	// 中ボスリスト
	MediumBoss *medium[8];
	list<MediumBoss*> mediumList;
	list<MediumBoss*>::iterator mediumItr;
	list<MediumBoss*> notMedium;
	list<MediumBoss*>::iterator notMediumItr;


	// ボスのリスト
	Boss *boss[4];
	list<Boss*> bossList;
	list<Boss*>::iterator bossItr;
	list<Boss*> notBoss;
	list<Boss*>::iterator notBossItr;

	int enemyEmergenceCount;
};