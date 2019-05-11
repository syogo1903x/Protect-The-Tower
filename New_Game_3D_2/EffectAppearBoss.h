#pragma once

class EffectBase;

class EffectAppearBoss :public EffectBase
{
public:

	EffectAppearBoss();
	~EffectAppearBoss();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};