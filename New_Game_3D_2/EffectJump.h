#pragma once

class EffectBase;

class EffectJump :public EffectBase
{
public:
	EffectJump();
	~EffectJump();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};
