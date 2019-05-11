#pragma once

class DefenseBase;

class DefenseWall :public DefenseBase
{
public:
	DefenseWall(int _modelHandle);
	~DefenseWall();


	void SetDefenseObject(int _modelHamdle) override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void HpDraw() override;
	void Release() override;

private:

};