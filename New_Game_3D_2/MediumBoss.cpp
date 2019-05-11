#include "Common.h"

// �R���X�g���N�^
MediumBoss::MediumBoss()
{


}

// �f�X�g���N�^
MediumBoss::~MediumBoss()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

// ������
void MediumBoss::Init(int model)
{
	// ���f���ǂݍ���
	modelHandle = MV1DuplicateModel(model);
	// �A�j���[�V�����̏�����
	AnimationInit();

	if (modelHandle < 0)
	{
		printfDx("�f�[�^�ǂݍ��݂Ɏ��s");
	}

	characterMove.dir = ZEROCLEAR;
	characterMove.angle = ZEROCLEAR;

	jumpGravity = 1.0f;
	radius = 5.0f;

	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = false;
	isFinish = true;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 6;
	isAlive = false;

	MV1SetDifColorScale(modelHandle, GetColorF(redColor, greenColor, blueColor, 1.1f));

	pos = characterMove.pos;
}

void MediumBoss::Init(char * _playerNumber)
{
	// ~�Ƃ��ɂȂ�
}

// �ړ�
void MediumBoss::CharacterMove(Camera & _camera)
{
	SetModelColor();

	// �E�F�[�u���N���A������G�̍폜
	if (Tower::GetWaveInterval())
	{
		life = 0;
	}

	// ���񂾏ꍇ
	if (life <= 0)
	{
		// ���񂾂��Ƃɂ���
		isFinish = true;
		// 
		life = -1;
	}


	// ��]�X�V
	MV1SetRotationXYZ(modelHandle, characterMove.angle);

	// �ʒu�X�V
	MV1SetPosition(modelHandle, characterMove.pos);

	// �d��
	characterMove.pos.y -= jumpGravity;


	// ���K��
	if (VSquareSize(characterMove.dir) != 0)
	{
		characterMove.dir = VNorm(characterMove.dir);
	}

	// �U�����Ă��Ȃ���Έړ��\
	if (!characterAtack.isAtack)
	{
		// �x���V�e�B
		velocity = VScale(characterMove.dir, 1.0f);

		// �ړ��X�V
		characterMove.pos = VAdd(characterMove.pos, velocity);
	}

	// �����ύX
	aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

	// �����X�V
	characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, 0.2f);
	

}

// �W�����v (���ݕs�g�p)
void MediumBoss::CharacterJump()
{


}

// �A�^�b�N (���ݕs�g�p)
void MediumBoss::CharacterAtack()
{

	// ���ڂ̍U��
	if (characterAtack.isAtack)
	{
		characterAtack.atackCount++;
	}

}

// �A�j���[�V����
void MediumBoss::Animation()
{
	// �W�����v��
	if (characterJump.isJump)
	{
		// �W�����v�A�j���[�V�����̕ύX
		totalTime = AnimationChange(playAnim, ANIMATION_JUMP, modelHandle, animAttachIndex, totalTime);
	}
	else if (characterAtack.isAtack && !characterJump.isJump)
	{
		// �U���A�j���[�V�����̕ύX
		totalTime = AnimationChange(playAnim, ANIMATION_ATACK, modelHandle, animAttachIndex, totalTime);
	}
	else if (characterMove.isMove && !characterAtack.isAtack)
	{
		// �ړ��A�j���[�V�����̕ύX
		totalTime = AnimationChange(playAnim, ANIMATION_MOVE, modelHandle, animAttachIndex, totalTime);
	}
	else
	{
		playTime++;
		// �ҋ@�A�j���[�V�����̕ύX
		totalTime = AnimationChange(playAnim, ANIMATION_WAIT, modelHandle, animAttachIndex, totalTime);
	}

	// �e�A�j���[�V�����̍ő�t���[���ݒ�
	if (characterJump.isJump)
	{
		playTime = totalTime / 2;
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
	}
	else if (characterAtack.isAtack)
	{
		characterAtack.atackCount = 0;
		playTime = 0;
	}
	else if (characterAtack.isAtack)
	{
		if (characterAtack.atackCount >= totalTime)
		{
			characterAtack.isAtack = false;
		}
		playTime = 0;
	}
	else if (characterMove.isMove)
	{
		if (playTime >= totalTime)
		{
			playTime -= totalTime;
		}
	}
	else
	{
		if (playTime >= totalTime)
		{
			playTime = 10;
		}
	}

	// �A�j���[�V�������ꍞ��								���ʂ̃^�C��		1�U���A�j���[�V����
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount);
}

// �K�E�Z (���ݕs�g�p)
void MediumBoss::CharacterDeathBlow()
{


}

// �L�����N�^�[�_���[�W
void MediumBoss::CharacterDamage()
{
	// �����_���[�W
	FastDamage();
}

// �F�ύX
void MediumBoss::SetModelColor()
{
	// �F�ύX
	if (life == 6)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor, greenColor, blueColor, 1.0f));
	}
	if (life == 5)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.1f, greenColor - 0.1f, blueColor - 0.1f, 1.0f));
	}
	if (life == 4)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.3f, greenColor - 0.3f, blueColor - 0.3f, 1.0f));
	}
	if (life == 3)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.5f, greenColor - 0.5f, blueColor - 0.5f, 1.0f));
	}
	if (life == 2)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.7f, greenColor - 0.7f, blueColor - 0.7f, 1.0f));
	}
	if (life == 1)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.9f, greenColor - 0.9f, blueColor - 0.9f, 1.0f));
	}

}

// �G�l�~�[�̃Z�b�g
void MediumBoss::SetMedium()
{
	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = false;
	isFinish = false;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 6;
	isAlive = false;

	isHit = false;
}

// �v���C���[�̌����Ɉړ�
void MediumBoss::EnemyMove(VECTOR _pos)
{
	characterMove.dir = VSub(_pos, characterMove.pos);
}

// �v���C���[�̌����Ƃ͔��]�Ɉړ�
void MediumBoss::EnemyMoveSub(VECTOR _pos)
{
	characterMove.dir = VSub(characterMove.pos, _pos);
}

// �X�V
void MediumBoss::EnemyUpdate(CharacterBase * _player, Tower *_tower)
{
	/*
	// �v���C���[�ƒ��{�X�̓����蔻��ƈړ�����
	// ���{�X�̗̑͂�0�ł͂Ȃ����
	if (life > 0)
	{

		// ���{�X���v���C���[�Ɍ������悤�ɂ���
		if (!HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 5.0f) && HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 8))
		{
			this->EnemyMove(_player->GetPos());
			this->SetMove(true);
		}
		// ���{�X��
		else if (HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 5.0f) && !HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 8))
		{
			if (this->GetMove())
			{
				this->ClerDir();
			}
		}
		else if (!HitCheck::HitCheckCircleTowerToEnemy(_tower, this, 10))
		{
			this->EnemyMove(_tower->GetPos());
		}
		else
		{
			if (!_tower->GetHit())
			{
				_tower->SetHit(true);
				_tower->SetLifeDamege(10);
			}
			life = 0;
		}
	}
	*/

	if (life > 0)
	{
		// �G�l�~�[���v���C���Ɍ������悤�ɂ���
		if (HitCheck::HitCheckCircleTowerToEnemy(_tower, this, 5.0f))
		{
			if (!_tower->GetHit())
			{
				loseDamegeSe->PlaySoundEffect();
				_tower->SetHit(true);
				_tower->SetLifeDamege(5);
				// �^���[�ɓ����������Ƃ�m�点��
				isHit = true;
			}
			life = -1;
		}
		else
		{
			this->EnemyMove(_tower->GetPos());
		}
	}
}
