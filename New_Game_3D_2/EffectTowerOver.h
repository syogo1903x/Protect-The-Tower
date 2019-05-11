#pragma once

class EffectBase;

class EffectTowerOver :public EffectBase
{
public:

	EffectTowerOver();
	~EffectTowerOver();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;

private:


};