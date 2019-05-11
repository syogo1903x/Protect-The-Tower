#include "Common.h"

EffectBase::EffectBase()
{
	time = 0;
	playingEffectHandle = -1;
}

EffectBase::~EffectBase()
{

}

void EffectBase::UpdateCharter(CharacterBase * _player)
{
	// 各エフェクトの更新
	EffectUpdatePlayer(_player);
}

void EffectBase::UpdateDefense(DefenseBase * _defense)
{
	// 各エフェクトの更新
	EffectUpdateDefense(_defense);
}

// ここでもう一度更新をしないとタワーのエフェクトが出ない
void EffectBase::UpdateTower(Tower *_tower)
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// 各エフェクトの更新
	EffectUpdateTower(_tower);
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffectBase::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffectBase::Release()
{
	DeleteEffekseerEffect(effectHandle);
	effectHandle = NULL;
	playingEffectHandle = NULL;
}
