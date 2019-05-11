#pragma once

class EffectBase;

class EffectFire :public EffectBase
{
public:

	EffectFire();
	~EffectFire();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;

private:


};