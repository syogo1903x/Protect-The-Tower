#pragma once

class EffectBase;

class EffectDeathBlow_Chinami :public EffectBase
{
public:
	EffectDeathBlow_Chinami();
	~EffectDeathBlow_Chinami();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};