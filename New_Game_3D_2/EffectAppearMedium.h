#pragma once

class EffectBase;

class EffectAppearMedium :public EffectBase
{
public:

	EffectAppearMedium();
	~EffectAppearMedium();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};