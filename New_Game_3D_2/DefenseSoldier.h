#pragma once

class DefenseBase;

class DefenseSoldier : public DefenseBase
{
public:
	DefenseSoldier(int _modelHandle);
	~DefenseSoldier();

	void SetDefenseObject(int _modelHamdle) override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void HpDraw() override;
	void Release() override;

private:
	int bulletCount;
	int bulletModelHandle;
};