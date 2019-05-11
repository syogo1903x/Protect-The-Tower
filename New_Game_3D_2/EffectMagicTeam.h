#pragma once

class EffectBase;

class EffectMagicTeam :public EffectBase
{
public:
	EffectMagicTeam();
	~EffectMagicTeam();


	void EffectInit() override;
	void EffectUpdatePlayer(CharacterBase *_character) override;
	void EffectUpdateDefense(DefenseBase *_defense) override;
	void EffectUpdateTower(Tower *_tower) override;


private:



};