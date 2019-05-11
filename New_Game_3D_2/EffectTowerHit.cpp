#include "Common.h"

EffectTowerHit::EffectTowerHit()
{

}

EffectTowerHit::~EffectTowerHit()
{

}

void EffectTowerHit::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/7/towerHit.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectTowerHit::EffectUpdatePlayer(CharacterBase * _character)
{
	// キャラクター用
	// ~特になし
}

void EffectTowerHit::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectTowerHit::EffectUpdateTower(Tower * _tower)
{
	time++;

	// エフェクトを再生する。
	if (time == 1) { playingEffectHandle = PlayEffekseer3DEffect(effectHandle); }

	//if (time >= 30) { StopEffekseer3DEffect(playingEffectHandle); }
	if (time >= 60) { time = 0; }

	// エフェクトの拡大率を設定する。
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.f, 2.f, 2.f);

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _tower->GetPos().x - 2, _tower->GetPos().y + 10, _tower->GetPos().z);

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 0, 0);

	if (_tower->GetLife() < 0 || SceneGame::GetTimer() >= 90 /* || KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON*/)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}
}
