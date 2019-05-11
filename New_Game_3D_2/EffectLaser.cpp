#include "Common.h"

EffectLaser::EffectLaser()
{


}

EffectLaser::~EffectLaser()
{


}

void EffectLaser::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/laser/laser.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectLaser::EffectUpdatePlayer(CharacterBase *_character)
{
	// 時間を経過させる。
	time++;


	// 定期的にエフェクトを再生する
	if (time % 60 == 0)
	{
		// エフェクトを再生する。
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// エフェクトの拡大率を設定する。
		// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
		//SetScalePlayingEffekseer3DEffect(playingEffectHandle, 0.2f, 0.2f, 0.2f);
	}

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y, _character->GetPos().z);
}

void EffectLaser::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectLaser::EffectUpdateTower(Tower * _tower)
{
	// タワー用
	// ~特になし
}
