#pragma once

class EffectBase;

class EffectLaser :public EffectBase
{
public:
	EffectLaser();
	~EffectLaser();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};