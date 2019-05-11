#include "Common.h"

Coin::Coin()
{
}

// íœ
Coin::~Coin()
{
	MV1DeleteModel(itemModelHandle);
	itemModelHandle = NULL;
}

// ‰Šú‰»
void Coin::Init(int model)
{
	itemModelHandle = MV1DuplicateModel(model);
	isLost = true;
	itemPos = VGet(0, -200, 0);
	// ‘å‚«‚³ŽO”{
	MV1SetScale(itemModelHandle, VGet(3, 3, 3));
	//
	isGet = false;

	rota = 0;
	// Œø‰Ê‰¹“Ç‚Ýž‚Ý
	se = new SoundEffect("Music/SE/pickup03.mp3");

}

// XV
void Coin::ItemUpdate(CharacterBase * _enemy)
{
	// “G‚ªoŒ»‚µ‚Ä‚¢‚½‚ç”ñ•\Ž¦
	if (_enemy->GetLife() > 0)
	{
		isGet = false;
	}

	// “G‚ªŽ€‚ñ‚¾‚ç•\Ž¦@‚©‚Â@‰ñ“]
	if (!_enemy->GetDead())
	{
		rota = 0;
		itemPos = _enemy->GetPos();
		isLost = true;
	}
	else
	{
		// ‰ñ“]
		rota += 0.25f;

		if ((int)rota % 2 == 0)itemPos.y += 0.1f;
		else itemPos.y -= 0.1f;

		isLost = false;
	}

	MV1SetRotationXYZ(itemModelHandle, VGet(0, rota, 0));

}
