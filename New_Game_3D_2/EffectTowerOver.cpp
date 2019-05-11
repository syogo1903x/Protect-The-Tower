#include "Common.h"

EffectTowerOver::EffectTowerOver()
{

}

EffectTowerOver::~EffectTowerOver()
{

}

void EffectTowerOver::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/4/towerOver.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectTowerOver::EffectUpdatePlayer(CharacterBase * _character)
{
	// キャラクター用
	// ~特になし
}

void EffectTowerOver::EffectUpdateDefense(DefenseBase * _defense)
{
	// 防御アイテム用
	// ~特になし
}

void EffectTowerOver::EffectUpdateTower(Tower * _tower)
{
	time++;

	// エフェクトを再生する。
	if (time == 1) { playingEffectHandle = PlayEffekseer3DEffect(effectHandle); }

	//if (time >= 30) { StopEffekseer3DEffect(playingEffectHandle); }
	if (time >= 60) { time = 0; }

	// エフェクトの拡大率を設定する。
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 4.f, 4.f, 4.f);

	// エフェクトの位置を変える
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _tower->GetPos().x - 2, _tower->GetPos().y + 20, _tower->GetPos().z);

	// エフェクトの回転を変える
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 0, 0);

	if (_tower->GetLife() < 0 || SceneGame::GetTimer() >= 90)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}
}
