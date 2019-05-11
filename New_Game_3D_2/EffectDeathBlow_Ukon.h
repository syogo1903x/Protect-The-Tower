#pragma once

class EffectBase;

class EffectDeathBlow_Ukon :public EffectBase
{
public:
	EffectDeathBlow_Ukon();
	~EffectDeathBlow_Ukon();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};