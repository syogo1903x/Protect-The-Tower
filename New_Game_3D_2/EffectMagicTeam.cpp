#include "Common.h"

EffectMagicTeam::EffectMagicTeam()
{

}

EffectMagicTeam::~EffectMagicTeam()
{

}

void EffectMagicTeam::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/MagicArea.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectMagicTeam::EffectUpdatePlayer(CharacterBase *_character)
{
	// ���Ԃ��o�߂�����B
	time++;

	// ����I�ɃG�t�F�N�g���Đ�����
	if (time == 1)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 60.f, 10.f, 60.f);
	}

	// �G�t�F�N�g���~�߂�
	// �������Ԃɖ߂�
	if (time >= 30)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y - 8.5f, _character->GetPos().z);
}

void EffectMagicTeam::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectMagicTeam::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
