#pragma once

class EffectBase;

class EffectTowerHit :public EffectBase
{
public:

	EffectTowerHit();
	~EffectTowerHit();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;

private:



};