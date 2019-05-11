#pragma once

class EffectBase;

class EffectHit :public EffectBase
{
public:
	EffectHit();
	~EffectHit();

	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};