#pragma once

class EffectBase;

class EffectBullet :public EffectBase
{
public:

	EffectBullet();
	~EffectBullet();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;

private:


};