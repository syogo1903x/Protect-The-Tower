#pragma once

class DefenseBase;

class DefenseBuyObject:public DefenseBase
{
public:
	DefenseBuyObject(int _modelHandle);
	~DefenseBuyObject();


	void SetDefenseObject(int _modelHamdle) override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void HpDraw() override;
	void Release() override;



private:



};