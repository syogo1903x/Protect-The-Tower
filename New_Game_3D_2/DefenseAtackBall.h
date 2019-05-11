#pragma once

class DefenseBase;


class DefenseAtackBall:public DefenseBase
{
public:
	DefenseAtackBall(int _modelHandle);
	~DefenseAtackBall();

	void SetDefenseObject(int _modelHamdle) override;
	void Init() override;
	void Update() override;
	void Draw() override;
	void HpDraw() override;
	void Release() override;

private:

};