#pragma once

class EffectBase;

class EffectDeathBlow_Inu :public EffectBase
{
public:
	EffectDeathBlow_Inu();
	~EffectDeathBlow_Inu();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};