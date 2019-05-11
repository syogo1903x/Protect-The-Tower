#pragma once

class EffectBase;

class EffectTowerDown :public EffectBase
{
public:

	EffectTowerDown();
	~EffectTowerDown();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;

private:


};