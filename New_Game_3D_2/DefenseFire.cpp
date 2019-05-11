#include "Common.h"

DefenseFire::DefenseFire(int _modelHandle)
			:DefenseBase( _modelHandle)
{
	defenseModelHandle = MV1DuplicateModel(_modelHandle);
}

// 削除
DefenseFire::~DefenseFire()
{
}

void DefenseFire::SetDefenseObject(int _modelHamdle)
{

}

void DefenseFire::Init()
{
	isSetDefense = false;
	life = 10;
	rotation = ZEROCLEAR;

	// ダメージ用
	isDamage = false;
	damageCount = 0;
}

void DefenseFire::Update()
{
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

	rotation.y += 0.001f;

	MV1SetPosition(defenseModelHandle, pos);
	MV1SetRotationXYZ(defenseModelHandle, rotation);
}

void DefenseFire::Draw()
{
	MV1DrawModel(defenseModelHandle);

}

void DefenseFire::HpDraw()
{
	DrawCube3D(VAdd(pos, VGet(-10.f, 23.f, 0.15f)), VAdd(pos, VGet(-10.f + life, 21.f, -0.15f)), GetColor(0, 255, 0), GetColor(0, 0, 0), TRUE);
	DrawCube3D(VAdd(pos, VGet(-10.f + 0.01f, 23.f + 0.02f, 0.01f)), VAdd(pos, VGet(0.f - 0.01f, 21.f - 0.02f, -0.01f)), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);
}

void DefenseFire::Release()
{
	MV1DeleteModel(defenseModelHandle);
	defenseModelHandle = NULL;
}
