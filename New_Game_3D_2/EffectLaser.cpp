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
	// ���Ԃ��o�߂�����B
	time++;


	// ����I�ɃG�t�F�N�g���Đ�����
	if (time % 60 == 0)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		// Effekseer�ō쐬�����G�t�F�N�g��2D�\���̏ꍇ�A���������邱�Ƃ��w�ǂȂ̂ŕK���g�傷��B
		//SetScalePlayingEffekseer3DEffect(playingEffectHandle, 0.2f, 0.2f, 0.2f);
	}

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y, _character->GetPos().z);
}

void EffectLaser::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectLaser::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
