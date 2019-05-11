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

	// ゲッター
	VECTOR GetBulletPos() { return bulletPos; }
	VECTOR GetPos() { return pos; }
	int GetModel() { return defenseModelHandle; }
	int GetLife() { return life; }
	bool GetDefense() { return isSetDefense; }
	float GetRadius() { return radius; }
	bool GetDamage() { return isDamage; }
	int GetDefenseNumber() { return defenseNumber; }

	// セッター
	// ポジションセット
	void SetPos(const VECTOR _set) { pos = _set; }
	// ローテーションセット
	void SetRotain(const VECTOR _set) { rotation = _set; }
	// デフェンスできるかどうかセット
	void SetDefense(const bool _set) { isSetDefense = _set; }
	// 体力ダメージセット
	void SetDamageDecrease(const int _set) { damage = _set; }
	// 体力セット
	void SetLife(const int _set) { life = _set; }
	// 弾の出現
	void SetBullet() { isBulletFire = false; }
	// ターゲットのセッター
	void SetTargetEnemy(VECTOR _set) { targetPos = _set; }
	// ダメージセット
	void SetDamage(bool _set) { isDamage = _set; }
	// 向きセット
	void SetDir(VECTOR _set) { direction = _set; }
	// 範囲セット
	void SetRange(bool _set) { isRange = _set; }
	// 回転スピードセット
	void SetAngleSpeed(float _set) { dirSpeed = _set; }

	// ディフェンスアイテムの自分が持っている番号の取得
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


	// 兵士用なんだよね
	VECTOR targetPos;
	VECTOR bulletPos;
	float radius;
	bool isBulletFire;
	VECTOR direction;
	float dirSpeed;

	bool isRange;

};