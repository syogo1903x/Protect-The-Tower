#include "Common.h"

EffectFire::EffectFire()
{

}

EffectFire::~EffectFire()
{

}

void EffectFire::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/FirePot1.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectFire::EffectUpdatePlayer(CharacterBase * _character)
{
	// プレイやー用
	// ~特になし
}

void EffectFire::EffectUpdateDefense(DefenseBase * _defense)
{
	// 時間を経過させる。
	time++;


	// 定期的にエフェクトを再生する
	if (time == 1)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 10.f, 5.f, 10.f);

		// エフェクトの位置を変える
		SetPosPlayingEffekseer3DEffect(playingEffectHandle, _defense->GetPos().x, _defense->GetPos().y, _defense->GetPos().z);
	}

	if (time >= 61)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 0, 0);
}

void EffectFire::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
