#pragma once

class EffectBase;

class EffectDown :public EffectBase
{
public:
	EffectDown();
	~EffectDown();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};