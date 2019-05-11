#include "Common.h"

EffectDeathBlow_Ukon::EffectDeathBlow_Ukon()
{

}

EffectDeathBlow_Ukon::~EffectDeathBlow_Ukon()
{

}

void EffectDeathBlow_Ukon::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/3/DeathBlow_Ukon.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

}

void EffectDeathBlow_Ukon::EffectUpdatePlayer(CharacterBase * _character)
{
	// �K�E�Z���g�����
	if (_character->GetDeathBlowAnimationCount() == 1)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 6.f, 6.f, 6.f);
	}

	if (_character->GetDeathBlowAnimationCount() == 40) { StopEffekseer3DEffect(playingEffectHandle); }

	// �G�t�F�N�g�̈ʒu��ς���
	if (_character->GetDeathBlowAnimationCount() == 1) { SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y, _character->GetPos().z); }

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);

}

void EffectDeathBlow_Ukon::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectDeathBlow_Ukon::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
