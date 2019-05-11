#include "Common.h"


DefenseWall::DefenseWall(int _modelHandle)
			:DefenseBase(_modelHandle)
{
	defenseModelHandle = MV1DuplicateModel(_modelHandle);
}

// 削除
DefenseWall::~DefenseWall()
{
}

void DefenseWall::SetDefenseObject(int _modelHamdle)
{

}

void DefenseWall::Init()
{
	isSetDefense = false;
	life = 200;

	// ダメージ用
	isDamage = false;
	damageCount = 0;
}

void DefenseWall::Update()
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

	if (damageCount >= 4800)
	{
		isDamage = false;
		damageCount = 0;
	}

	MV1SetPosition(defenseModelHandle, pos);
	MV1SetRotationXYZ(defenseModelHandle, rotation);
}

void DefenseWall::Draw()
{
	MV1DrawModel(defenseModelHandle);
}

void DefenseWall::HpDraw()
{
	DrawCube3D(VAdd(pos, VGet(-20.f, 23.f, -0.15f)), VAdd(pos, VGet(-20.f + life / 5, 21.f, 0.15f)), GetColor(0, 255, 0), GetColor(0, 0, 0), TRUE);
	DrawCube3D(VAdd(pos, VGet(-20.f + 0.01f, 23.f + 0.02f, -0.01f)), VAdd(pos, VGet(20.f - 0.01f, 21.f - 0.02f, 0.01f)), GetColor(100, 100, 100), GetColor(0, 0, 0), TRUE);
}

void DefenseWall::Release()
{
	MV1DeleteModel(defenseModelHandle);
	defenseModelHandle = NULL;
}
