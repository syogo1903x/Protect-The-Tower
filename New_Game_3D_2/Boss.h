#pragma once
#include "CharacterBase.h"

class Boss :public CharacterBase
{
public:
	Boss();
	~Boss();


	void		Init(int model) override;
	void		Init(char *_playerNumber) override;
	void		CharacterMove(Camera &_camera) override;
	void		CharacterJump() override;
	void		CharacterAtack() override;
	void		Animation() override;
	void		SetBoss();
	void		CharacterDeathBlow() override;
	void		CharacterDamage() override;

	void		SetModelColor();
	void		EnemyMove(VECTOR _pos);
	void		EnemyMoveSub(VECTOR _pos);
	void		EnemyUpdate(CharacterBase * _player, Tower *_tower);

	// Œü‚«‚ğí‚É‰Šú‰»
	void		ClerDir() { characterMove.dir = VGet(0.0f, 0.0f, 0.0f); }


	VECTOR &GetEnemyPos() { return pos; }

private:

	VECTOR pos;

};