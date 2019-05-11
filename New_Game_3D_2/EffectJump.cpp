#include "Common.h"

EffectJump::EffectJump()
{

}

EffectJump::~EffectJump()
{

}

void EffectJump::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/jump.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectJump::EffectUpdatePlayer(CharacterBase * _character)
{
	// �K�E�Z���g�����
	if (_character->GetJumpCount() == 1)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 10.f, 4.f, 10.f);
	}

	//if (!_character->GetDeathBlow())StopEffekseer3DEffect(playingEffectHandle);

	// �G�t�F�N�g�̈ʒu��ς���
	if (_character->GetJumpCount() == 1)SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y - 7.f, _character->GetPos().z);

	// �G�t�F�N�g�̉�]��ς���
	//SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectJump::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectJump::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
