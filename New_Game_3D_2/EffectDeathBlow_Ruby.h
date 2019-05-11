#pragma once

class EffectBase;

class EffectDeathBlow_Ruby :public EffectBase
{
public:
	EffectDeathBlow_Ruby();
	~EffectDeathBlow_Ruby();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};