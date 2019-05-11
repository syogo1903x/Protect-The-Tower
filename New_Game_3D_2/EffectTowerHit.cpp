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
	// �L�����N�^�[�p
	// ~���ɂȂ�
}

void EffectTowerHit::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectTowerHit::EffectUpdateTower(Tower * _tower)
{
	time++;

	// �G�t�F�N�g���Đ�����B
	if (time == 1) { playingEffectHandle = PlayEffekseer3DEffect(effectHandle); }

	//if (time >= 30) { StopEffekseer3DEffect(playingEffectHandle); }
	if (time >= 60) { time = 0; }

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.f, 2.f, 2.f);

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _tower->GetPos().x - 2, _tower->GetPos().y + 10, _tower->GetPos().z);

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 0, 0);

	if (_tower->GetLife() < 0 || SceneGame::GetTimer() >= 90 /* || KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON*/)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}
}
