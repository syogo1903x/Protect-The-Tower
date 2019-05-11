#include "Common.h"

EffectAppearBoss::EffectAppearBoss()
{
}

EffectAppearBoss::~EffectAppearBoss()
{
}

void EffectAppearBoss::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/2/AppearBoss.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectAppearBoss::EffectUpdatePlayer(CharacterBase * _character)
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

void EffectAppearBoss::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectAppearBoss::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
