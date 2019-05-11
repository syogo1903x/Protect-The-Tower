#pragma once

#include "ItemBase.h"

class CharacterBase;
class ItemBase;

class Coin :public ItemBase
{
public:
	Coin();
	~Coin();

	void Init(int model) override;
	void ItemUpdate(CharacterBase *_enemy) override;

private:

	float rota;



};