#include "Common.h"

EffectJump::EffectJump()
{

}

EffectJump::~EffectJump()
{

}

void EffectJump::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/jump.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectJump::EffectUpdatePlayer(CharacterBase * _character)
{
	// 必殺技が使われれば
	if (_character->GetJumpCount() == 1)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 10.f, 4.f, 10.f);
	}

	//if (!_character->GetDeathBlow())StopEffekseer3DEffect(playingEffectHandle);

	// エフェクトの位置を変える
	if (_character->GetJumpCount() == 1)SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y - 7.f, _character->GetPos().z);

	// エフェクトの回転を変える
	//SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectJump::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectJump::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
