#include "Common.h"

EffectDown::EffectDown()
{

}

EffectDown::~EffectDown()
{

}

void EffectDown::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/down.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectDown::EffectUpdatePlayer(CharacterBase * _character)
{
	// 死んだとき
	if (_character->GetLife() <= 0)
	{
		time++;
	}
	else
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	if (time == 1)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 3.f, 3.f, 3.f);
	}
	
	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y, _character->GetPos().z);

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectDown::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectDown::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
