#include "CharacterBase.h"
#include "SceneGame.h"

// �A�j���[�V����������
void CharacterBase::AnimationInit()
{
	// �A�j���[�V�������A�^�b�`
	animAttachIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);

	// ����A�j���[�V�����̑����Ԃ��擾���Ă���
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, animAttachIndex);

	// �A�j���[�V�����Đ����Ԃ�������
	playTime = 20.0f;
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime);

	// �A�j���[�V�����ňړ������Ă���t���[���̔ԍ�����������
	moveAnimFrameIndex = MV1SearchFrame(modelHandle, "�Z���^�[");

	// �A�j���[�V�����ňړ������Ă���t���[���𖳌��ɂ���
	MV1SetFrameUserLocalMatrix(modelHandle, moveAnimFrameIndex, MGetIdent());

	money = 0;
	playTime = 0;
	isHit = false;
	// ���̃Z�b�g
	hitDamegeSe = new SoundEffect("Music/SE/damage3.mp3");
	loseDamegeSe = new SoundEffect("Music/SE/damage7.mp3");
}

// �X�V
void CharacterBase::Update(Camera & _camera)
{
	// �A�j���[�V����
	Animation();
	// �ړ�
	CharacterMove(_camera);

	// �Q�[�����n�܂�Α���\
	if (SceneGame::GetStart())
	{
		// �W�����v
		CharacterJump();
		// �U��
		CharacterAtack();
		// �K�E�Z
		CharacterDeathBlow();
	}

	// �L�����̃_���[�W
	CharacterDamage();
}

// �`�� 
void CharacterBase::Draw()
{
	if (!isFinish)
	{
		MV1DrawModel(modelHandle);
		//VECTOR StringPos = ConvWorldPosToScreenPos(characterMove.pos);
		//DrawFormatString(StringPos.x, StringPos.y, GetColor(255, 0, 0), "Life : %d", life);
	}
}

// ���
void CharacterBase::Release()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	hitDamegeSe->Release();
	loseDamegeSe->Release();
}

// �f�����_���[�W
void CharacterBase::FastDamage()
{
	float alha;

	//  �K�E�Z�̃_���[�W����炦��
	if (isDeathBlowDamage)
	{
		damageCount++;

		if (damageCount > 10)
		{
			damageCount = 0;
			isDeathBlowDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 10;
		}
	}
	// �ʏ�̃_���[�W����炦��
	else if (isDamage)
	{
		damageCount++;

		if (damageCount > 4)
		{
			damageCount = 0;
			isDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 1;
		}
	}

	// �q�b�g��
	if (life > 0)
	{
		if (damageCount == 1)
		{
			hitDamegeSe->PlaySoundEffect();
		}
	}
	// ���S��
	if (life <= 0)
	{
		if (damageCount == 1)
		{
			loseDamegeSe->PlaySoundEffect();
		}
	}

	if (damageCount % 2 == 0)
	{
		alha = 1.0f;
	}
	else
	{
		alha = 0.5f;
	}

	MV1SetOpacityRate(modelHandle, alha);
}

// �x���_���[�W
void CharacterBase::SlowDamage()
{
	float alha;

	//  �K�E�Z�̃_���[�W����炦��
	if (isDeathBlowDamage)
	{
		damageCount++;

		if (damageCount > 60)
		{
			damageCount = 0;
			isDeathBlowDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 10;
		}
	}
	// �ʏ�̃_���[�W����炦��
	else if (isDamage)
	{
		damageCount++;

		if (damageCount > 30)
		{
			damageCount = 0;
			isDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 1;
		}
	}

	// �̗͂�0�ł͂Ȃ��Ƃ������o��
	if (life > 0)
	{
		if (damageCount == 1)
		{
			hitDamegeSe->PlaySoundEffect();
		}
	}
	// �̗͂�0�ȉ��̎������o��
	if (life <= 0)
	{
		if (damageCount == 1)
		{
			loseDamegeSe->PlaySoundEffect();
		}
	}

	// �_�ł�����
	if (damageCount % 2 == 0)
	{
		alha = 1.0f;
	}
	else
	{
		alha = 0.5f;
	}
	
	// �����x�ύX
	MV1SetOpacityRate(modelHandle, alha);
}

// �~�̓����蔻�菈��
void CharacterBase::OnHit(CharacterBase * _player)
{
	// �������g�̈ʒu����Q���̂����蔻�蕪���炷.
	// Z����X���̓񎟌����W�Ƃ��Ĉʒu���炵���s��.
	VECTOR yZeroPlayer = characterMove.pos;
	VECTOR yZeroOtherPlayer = _player->GetPos();

	VECTOR otherPlaterToPlayer = VSub(yZeroPlayer, yZeroOtherPlayer);

	// �Ԃ������Ƃ��ɗ��������B���傤�ǂ���float�덷�ŏd�Ȃ葱����̂ŏ����Ԃ�������.
	float awayRange = (radius + _player->GetRadius() + 0.01f);

	VECTOR awayVec = VScale(VNorm(otherPlaterToPlayer), awayRange);
	characterMove.pos = VAdd(yZeroOtherPlayer, awayVec);

	// �Ԃ������猸������.
	characterMove.dir = VScale(characterMove.dir, 0.4f);
}

// �_���[�W�ŉ����鏈��
void CharacterBase::FlutterCharacter()
{
	// �ړ��X�V
	characterMove.pos = VAdd(characterMove.pos, VScale(VGet(0, 0, -1), 10));
}
