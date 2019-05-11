#include "Common.h"

EffectBullet::EffectBullet()
{

}

EffectBullet::~EffectBullet()
{

}

void EffectBullet::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/6/bullet.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectBullet::EffectUpdatePlayer(CharacterBase * _character)
{
	if (_character->GetAtack())
	{
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
		{
			// エフェクトを再生する。
			playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
		}
	}
	else
	{
		StopEffekseer3DEffect(playingEffectHandle);
	}

	// エフェクトの拡大率を設定する。
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.f, 2.f, 2.f);

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x - 2, _character->GetPos().y + Player::GetPlayerTargetCameraPos(), _character->GetPos().z);

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectBullet::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectBullet::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
