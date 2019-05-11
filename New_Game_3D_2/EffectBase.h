#pragma once

class CharacterBase;
class DefenseBase;
class Tower;

class EffectBase
{
public :
	EffectBase();
	virtual ~EffectBase();

	virtual void UpdateCharter(CharacterBase *_player);
	virtual void UpdateDefense(DefenseBase *_defense);
	virtual void UpdateTower(Tower *_tower);
	virtual void Draw();
	virtual void Release();

	virtual void EffectInit() = 0;
	virtual void EffectUpdatePlayer(CharacterBase *_character) = 0;
	virtual void EffectUpdateDefense(DefenseBase *_defense) = 0;
	virtual void EffectUpdateTower(Tower *_tower) = 0;

	// �Z�b�^�[
	void SetTime(int _set) { time = _set; }


	// �Q�b�^�[
	const int &GetTime() { return time ; }



protected:

	int effectHandle;
	int effectGraphHandle;

	int time;
	int playingEffectHandle;


};