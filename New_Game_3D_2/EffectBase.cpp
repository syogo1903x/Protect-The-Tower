#include "Common.h"

EffectBase::EffectBase()
{
	time = 0;
	playingEffectHandle = -1;
}

EffectBase::~EffectBase()
{

}

void EffectBase::UpdateCharter(CharacterBase * _player)
{
	// �e�G�t�F�N�g�̍X�V
	EffectUpdatePlayer(_player);
}

void EffectBase::UpdateDefense(DefenseBase * _defense)
{
	// �e�G�t�F�N�g�̍X�V
	EffectUpdateDefense(_defense);
}

// �����ł�����x�X�V�����Ȃ��ƃ^���[�̃G�t�F�N�g���o�Ȃ�
void EffectBase::UpdateTower(Tower *_tower)
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
	// �e�G�t�F�N�g�̍X�V
	EffectUpdateTower(_tower);
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();
}

void EffectBase::Draw()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}

void EffectBase::Release()
{
	DeleteEffekseerEffect(effectHandle);
	effectHandle = NULL;
	playingEffectHandle = NULL;
}
