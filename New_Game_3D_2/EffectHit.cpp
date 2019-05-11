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
	// ���Ԃ��o�߂�����B
	time++;

	// ����I�ɃG�t�F�N�g���Đ�����
	if (time == 1)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 6.f, 6.f, 6.f);
	}

	// �G�t�F�N�g���~�߂�
	// �������Ԃɖ߂�
	if (time >= 30)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x + (-3 + rand() % 6), _character->GetPos().y, _character->GetPos().z + (-3 + rand() % 6));

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);

}

void EffectHit::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectHit::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
