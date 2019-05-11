#include "Common.h"

EffectBullet::EffectBullet()
{

}

EffectBullet::~EffectBullet()
{

}

void EffectBullet::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/6/bullet.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}
}

void EffectBullet::EffectUpdatePlayer(CharacterBase * _character)
{
	if (_character->GetAtack())
	{
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
		{
			// �G�t�F�N�g���Đ�����B
			playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
		}
	}
	else
	{
		StopEffekseer3DEffect(playingEffectHandle);
	}

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.f, 2.f, 2.f);

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x - 2, _character->GetPos().y + Player::GetPlayerTargetCameraPos(), _character->GetPos().z);

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectBullet::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectBullet::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
