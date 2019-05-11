#include "Common.h"

EffectTowerDown::EffectTowerDown()
{

}

EffectTowerDown::~EffectTowerDown()
{

}

void EffectTowerDown::EffectInit()
{
	effectHandle = LoadEffekseerEffect("Effect/6/tower.efk");

	if (effectHandle < 0)
	{
		printfDx("error\n");
	}

	time = 0;
}


void EffectTowerDown::EffectUpdatePlayer(CharacterBase * _character)
{
	// �L�����N�^�[�p
	// ~���ɂȂ�
}

void EffectTowerDown::EffectUpdateDefense(DefenseBase * _defense)
{
	// �h��A�C�e���p
	// ~���ɂȂ�
}

void EffectTowerDown::EffectUpdateTower(Tower * _tower)
{
	time++;

	// �G�t�F�N�g���Đ�����B
	if (time == 1) { playingEffectHandle = PlayEffekseer3DEffect(effectHandle); }

	//if (time >= 30) { StopEffekseer3DEffect(playingEffectHandle); }
	if (time >= 200) { time = 0; }

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, 4.f, 4.f, 4.f);

	// �G�t�F�N�g�̈ʒu��ς���
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _tower->GetPos().x - 2, _tower->GetPos().y + 20, _tower->GetPos().z);

	// �G�t�F�N�g�̉�]��ς���
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0, 0, 0);

	if (_tower->GetLife() < 0 || SceneGame::GetTimer() >= 90)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		time = 0;
	}

}
