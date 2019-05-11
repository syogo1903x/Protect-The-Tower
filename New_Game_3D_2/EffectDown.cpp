#include "Common.h"

EffectDown::EffectDown()
{

}

EffectDown::~EffectDown()
{

}

void EffectDown::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/5/down.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectDown::EffectUpdatePlayer(CharacterBase * _character)
{
	// ���񂾂Ƃ�
	if (_character->GetLife() <= 0)
	{
		time++;
	}
	else
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

	if (time == 1)
	{
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		SetScalePlayingEffekseer3DEffect(playingEffectHandle, 3.f, 3.f, 3.f);
	}
	
	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x, _character->GetPos().y, _character->GetPos().z);

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectDown::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectDown::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
