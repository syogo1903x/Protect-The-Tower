#include "Common.h"

EffectAppearMedium::EffectAppearMedium()
{
}

EffectAppearMedium::~EffectAppearMedium()
{

}

void EffectAppearMedium::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/2/Appear.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectAppearMedium::EffectUpdatePlayer(CharacterBase * _character)
{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

	// エフェクトの拡大率を設定する。
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.f, 2.f, 2.f);

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x - 2, _character->GetPos().y + Player::GetPlayerTargetCameraPos(), _character->GetPos().z);

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectAppearMedium::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectAppearMedium::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
