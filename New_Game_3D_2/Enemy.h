#pragma once
#include "CharacterBase.h"
#include <float.h>

class Tower;

class Enemy :public CharacterBase
{
public:
	Enemy();
	~Enemy();


	void			Init(int model) override;
	void			Init(char *_playerNumber) override;
	void			CharacterMove(Camera &_camera) override;
	void			CharacterJump() override;
	void			CharacterAtack() override;
	void			CharacterDeathBlow() override;
	void			Animation() override;
	void			CharacterDamage() override;
	void			SetEnemy();
	void			EnemyMove(VECTOR _pos);
	void			EnemyUpdate(CharacterBase * _player, Tower *_tower);

	// セッター
	// 番号のセット
	void SetEnemyLife(int _isSet) { life = _isSet; }

	// ゲッター
	// 番号の取得
	VECTOR &GetEnemyPos() { return pos; }

private:
	VECTOR pos;
};