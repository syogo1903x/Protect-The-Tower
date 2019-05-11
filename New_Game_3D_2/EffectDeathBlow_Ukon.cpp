#include "Common.h"

EffectDeathBlow_Ukon::EffectDeathBlow_Ukon()
{

}

EffectDeathBlow_Ukon::~EffectDeathBlow_Ukon()
{

}

void EffectDeathBlow_Ukon::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/3/DeathBlow_Ukon.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

}

void EffectDeathBlow_Ukon::EffectUpdatePlayer(CharacterBase * _character)
{
	// 必殺技が使われれば
	if (_character->GetDeathBlowAnimationCount() == 1)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 6.f, 6.f, 6.f);
	}

	if (_character->GetDeathBlowAnimationCount() == 40) { StopEffekseer3DEffect(playingEffectHandle); }

	// エフェクトの位置を変える
	if (_character->GetDeathBlowAnimationCount() == 1) { SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y, _character->GetPos().z); }

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);

}

void EffectDeathBlow_Ukon::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectDeathBlow_Ukon::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
