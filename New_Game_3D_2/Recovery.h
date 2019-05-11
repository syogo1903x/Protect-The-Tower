#pragma once
#include "ItemBase.h"

class CharacterBase;
class ItemBase;

class Recovery :public ItemBase
{
public:
	Recovery();
	~Recovery();

	void Init(int model) override;
	void ItemUpdate(CharacterBase *_enemy) override;

private:

	float rota;



};