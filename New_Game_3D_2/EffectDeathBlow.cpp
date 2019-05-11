#include "Common.h"

EffectDeathBlow::EffectDeathBlow()
{

}

EffectDeathBlow::~EffectDeathBlow()
{

}

void EffectDeathBlow::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/DeathBlow_Use.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectDeathBlow::EffectUpdatePlayer(CharacterBase * _character)
{
	// 必殺技が使われれば
	if (_character->GetDeathBlow() && !_character->GetStartDeathBlow())
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 6.f, 6.f, 6.f);
	}

	if (_character->GetDeathBlow()) { StopEffekseer3DEffect(playingEffectHandle); }

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y - 3, _character->GetPos().z); 
	//if (_character->GetDeathBlowAnimationCount() == 1) 
	//{
	//}

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectDeathBlow::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectDeathBlow::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
