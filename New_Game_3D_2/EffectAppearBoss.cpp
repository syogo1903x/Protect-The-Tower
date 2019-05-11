#include "Common.h"

EffectAppearBoss::EffectAppearBoss()
{
}

EffectAppearBoss::~EffectAppearBoss()
{
}

void EffectAppearBoss::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/2/AppearBoss.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}

void EffectAppearBoss::EffectUpdatePlayer(CharacterBase * _character)
{
	// �G�t�F�N�g���Đ�����B
	playingEffectHandle = PlayEffekseer3DEffect(effectHandle);

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 2.f, 2.f, 2.f);

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _character->GetPos().x - 2, _character->GetPos().y + Player::GetPlayerTargetCameraPos(), _character->GetPos().z);

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, _character->GetAngle().y, 0);
}

void EffectAppearBoss::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectAppearBoss::EffectUpdateTower(Tower * _tower)
{
	// �^���[�p
	// ~���ɂȂ�
}
