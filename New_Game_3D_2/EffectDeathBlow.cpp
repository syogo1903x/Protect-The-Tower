#include "Common.h"

EffectDeathBlow::EffectDeathBlow()
{

}

EffectDeathBlow::~EffectDeathBlow()
{

}

void EffectDeathBlow::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/DeathBlow_Use.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectDeathBlow::EffectUpdatePlayer(CharacterBase * _character)
{
	// �K�E�Z���g�����
	if (_character->GetDeathBlow() && !_character->GetStartDeathBlow())
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 6.f, 6.f, 6.f);
	}

	if (_character->GetDeathBlow()) { StopEffekseer3DEffect(playingEffectHandle); }

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y - 3, _character->GetPos().z); 
	//if (_character->GetDeathBlowAnimationCount() == 1) 
	//{
	//}

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectDeathBlow::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectDeathBlow::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
