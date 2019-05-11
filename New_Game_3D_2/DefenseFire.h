#pragma once

class DefenseBase;

class DefenseFire : public DefenseBase
{
public:
	DefenseFire(int _modelHandle);
	~DefenseFire();

	void SetDefenseObject(int _modelHamdle) override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void HpDraw() override;
	void Release() override;

	
private:


};