#include "Common.h"

EffectMagicTeam::EffectMagicTeam()
{

}

EffectMagicTeam::~EffectMagicTeam()
{

}

void EffectMagicTeam::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/MagicArea.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectMagicTeam::EffectUpdatePlayer(CharacterBase *_character)
{
	// 時間を経過させる。
	time++;

	// 定期的にエフェクトを再生する
	if (time == 1)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 60.f, 10.f, 60.f);
	}

	// エフェクトを止める
	// 初期時間に戻す
	if (time >= 30)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y - 8.5f, _character->GetPos().z);
}

void EffectMagicTeam::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectMagicTeam::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
