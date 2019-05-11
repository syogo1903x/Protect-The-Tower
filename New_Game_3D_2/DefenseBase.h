#pragma once
#include "Common.h"

class DefenseBase
{
public:
	DefenseBase(int _modelHandle) {};
	virtual ~DefenseBase() {};


	virtual void SetDefenseObject(int _modelHamdle) = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void HpDraw() = 0;
	virtual void Release() = 0;

	// �Q�b�^�[
	VECTOR GetBulletPos() { return bulletPos; }
	VECTOR GetPos() { return pos; }
	int GetModel() { return defenseModelHandle; }
	int GetLife() { return life; }
	bool GetDefense() { return isSetDefense; }
	float GetRadius() { return radius; }
	bool GetDamage() { return isDamage; }
	int GetDefenseNumber() { return defenseNumber; }

	// �Z�b�^�[
	// �|�W�V�����Z�b�g
	void SetPos(const VECTOR _set) { pos = _set; }
	// ���[�e�[�V�����Z�b�g
	void SetRotain(const VECTOR _set) { rotation = _set; }
	// �f�t�F���X�ł��邩�ǂ����Z�b�g
	void SetDefense(const bool _set) { isSetDefense = _set; }
	// �̗̓_���[�W�Z�b�g
	void SetDamageDecrease(const int _set) { damage = _set; }
	// �̗̓Z�b�g
	void SetLife(const int _set) { life = _set; }
	// �e�̏o��
	void SetBullet() { isBulletFire = false; }
	// �^�[�Q�b�g�̃Z�b�^�[
	void SetTargetEnemy(VECTOR _set) { targetPos = _set; }
	// �_���[�W�Z�b�g
	void SetDamage(bool _set) { isDamage = _set; }
	// �����Z�b�g
	void SetDir(VECTOR _set) { direction = _set; }
	// �͈̓Z�b�g
	void SetRange(bool _set) { isRange = _set; }
	// ��]�X�s�[�h�Z�b�g
	void SetAngleSpeed(float _set) { dirSpeed = _set; }

	// �f�B�t�F���X�A�C�e���̎����������Ă���ԍ��̎擾
	void SetDefenseNumber(int _set) { defenseNumber = _set; }

protected:
	int defenseModelHandle;
	VECTOR pos;
	VECTOR rotation;
	bool isSetDefense;
	int life;
	int damage;
	int damageCount;
	bool isDamage;
	int defenseNumber;


	// ���m�p�Ȃ񂾂��
	VECTOR targetPos;
	VECTOR bulletPos;
	float radius;
	bool isBulletFire;
	VECTOR direction;
	float dirSpeed;

	bool isRange;

};