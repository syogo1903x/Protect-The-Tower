#include "Common.h"

EffectHit::EffectHit()
{

}

EffectHit::~EffectHit()
{

}

void EffectHit::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/6/hit.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectHit::EffectUpdatePlayer(CharacterBase * _character)
{
	// 時間を経過させる。
	time++;

	// 定期的にエフェクトを再生する
	if (time == 1)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 6.f, 6.f, 6.f);
	}

	// エフェクトを止める
	// 初期時間に戻す
	if (time >= 30)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x + (-3 + rand() % 6), _character->GetPos().y, _character->GetPos().z + (-3 + rand() % 6));

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);

}

void EffectHit::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectHit::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
