#pragma once

class EffectBase;

class EffectDeathBlow_Karasu :public EffectBase
{
public:
	EffectDeathBlow_Karasu();
	~EffectDeathBlow_Karasu();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};