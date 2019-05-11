#pragma once
#include "CharacterBase.h"

class MediumBoss:public CharacterBase
{
public:
	MediumBoss();
	~MediumBoss();


	void		Init(int model) override;
	void		Init(char *_playerNumber) override;
	void		CharacterMove(Camera &_camera) override;
	void		CharacterJump() override;
	void		CharacterAtack() override;
	void		Animation() override;
	void		CharacterDeathBlow() override;
	void		CharacterDamage() override;
	void		SetModelColor();
	void		SetMedium();
	void		EnemyMove(VECTOR _pos);
	void		EnemyMoveSub(VECTOR _pos);
	void		EnemyUpdate(CharacterBase * _player, Tower *_tower);


	// 向きを常に初期化
	void		ClerDir(){ characterMove.dir = VGet(0.0f, 0.0f, 0.0f); }

	// セッター
	
	void SetColor(float _redColor, float _greenColor, float _blueColor) { redColor = _redColor; greenColor = _greenColor; blueColor = _blueColor; }
	void SetAtack(bool _isAtack) { characterAtack.isAtack = _isAtack; }

	// ゲッター
	VECTOR &GetEnemyPos() { return pos; }

private:
	float redColor;
	float blueColor;
	float greenColor;

	VECTOR pos;

};