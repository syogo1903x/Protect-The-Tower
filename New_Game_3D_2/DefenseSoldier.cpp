#include "Common.h"

DefenseSoldier::DefenseSoldier(int _modelHandle) 
				:DefenseBase(_modelHandle)
{
	defenseModelHandle = MV1DuplicateModel(_modelHandle);
}

// 削除
DefenseSoldier::~DefenseSoldier()
{
}

void DefenseSoldier::SetDefenseObject(int _modelHamdle)
{
	bulletModelHandle = MV1DuplicateModel(_modelHamdle);
	MV1SetScale(bulletModelHandle, VGet(0.25f, 0.25f, 0.25f));
}

void DefenseSoldier::Init()
{
	isSetDefense = false;
	life = 10;
	rotation = ZEROCLEAR;
	radius = 3.0f;
	bulletCount = 0;
	isBulletFire = false;
	bulletPos = pos;
	direction = ZEROCLEAR;

	// ダメージ用
	isDamage = false;
	damageCount = 0;
}

void DefenseSoldier::Update()
{
	// 定数
	const float OFFSET = 12;

	if (isSetDefense)
	{
		if (life <= 0)
		{
			isSetDefense = false;
		}
	}

	if (isDamage) { damageCount++; }
	if (damageCount == 40) { life -= damage; }

	if (damageCount >= 2400)
	{
		isDamage = false;
		damageCount = 0;
	}

	bulletCount++;

	if (bulletCount % 600 == 0) 
	{
		bulletPos = VGet(pos.x, pos.y + OFFSET, pos.z);
		// 向き取得
		direction = VSub(targetPos, pos);
		// 正規化
		direction = VNorm(direction);

		// 向き変更
		//float aimAngle = vec2Radian(&VGet(0, 0, -1), &direction);

		// 向き更新
		//rotation.y = lerpRadian(rotation.y, aimAngle, dirSpeed);
	}

	bulletPos = VAdd(bulletPos, VScale(direction, 0.3f));


	MV1SetPosition(bulletModelHandle, bulletPos);

	MV1SetPosition(defenseModelHandle, pos);


	//MV1SetRotationXYZ(defenseModelHandle, rotation);
}

void DefenseSoldier::Draw()
{
	MV1DrawModel(bulletModelHandle);

	MV1DrawModel(defenseModelHandle);
}

void DefenseSoldier::HpDraw()
{
	DrawCube3D(VAdd(pos, VGet(-10.f, 23.f, 0.15f)), VAdd(pos, VGet(-10.f + life, 21.f, -0.15f)), GetColor(0, 255, 0), GetColor(0, 0, 0), TRUE);
	DrawCube3D(VAdd(pos, VGet(-10.f + 0.01f, 23.f + 0.02f, 0.01f)), VAdd(pos, VGet(0.f - 0.01f, 21.f - 0.02f, -0.01f)), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);
}

void DefenseSoldier::Release()
{
	MV1DeleteModel(defenseModelHandle);
	defenseModelHandle = NULL;
	MV1DeleteModel(bulletModelHandle);
	bulletModelHandle = NULL;

}
