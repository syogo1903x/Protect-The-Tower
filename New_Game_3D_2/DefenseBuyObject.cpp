#include "Common.h"

DefenseBuyObject::DefenseBuyObject(int _modelHandle) :DefenseBase(_modelHandle)
{
	defenseModelHandle = MV1DuplicateModel(_modelHandle);
}

DefenseBuyObject::~DefenseBuyObject()
{

}

void DefenseBuyObject::SetDefenseObject(int _modelHamdle)
{

}

void DefenseBuyObject::Init()
{
	isSetDefense = true;
	life = 100;
	rotation = ZEROCLEAR;
}

void DefenseBuyObject::Update()
{
	MV1SetPosition(defenseModelHandle, pos);
	MV1SetRotationXYZ(defenseModelHandle, rotation);
}

void DefenseBuyObject::Draw()
{
	MV1DrawModel(defenseModelHandle);
}

void DefenseBuyObject::HpDraw()
{
}

void DefenseBuyObject::Release()
{
	MV1DeleteModel(defenseModelHandle);
	defenseModelHandle = NULL;
}
