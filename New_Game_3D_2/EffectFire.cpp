#include "Common.h"

EffectFire::EffectFire()
{

}

EffectFire::~EffectFire()
{

}

void EffectFire::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/FirePot1.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectFire::EffectUpdatePlayer(CharacterBase * _character)
{
	// �v���C��[�p
	// ~���ɂȂ�
}

void EffectFire::EffectUpdateDefense(DefenseBase * _defense)
{
	// ���Ԃ��o�߂�����B
	time++;


	// ����I�ɃG�t�F�N�g���Đ�����
	if (time == 1)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 10.f, 5.f, 10.f);

		// �G�t�F�N�g�̈ʒu��ς���
		SetPosPlayingEffekseer3DEffect(playingEffectHandle, _defense->GetPos().x, _defense->GetPos().y, _defense->GetPos().z);
	}

	if (time >= 61)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 0, 0);
}

void EffectFire::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
