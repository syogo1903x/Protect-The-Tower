#include "Common.h"

// �R���X�g���N�^
Boss::Boss()
{


}

// �f�X�g���N�^
Boss::~Boss()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

// ������
void Boss::Init(int model)
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

	radius = 20.0f;
	jumpGravity = 1.0f;

	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;


	characterJump.isJump = false;
	characterMove.isMove = false;
	isFinish = true;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 10;
	isAlive = false;

	pos = characterMove.pos;
}

void Boss::Init(char * _playerNumber)
{
	// ~�Ƃ��ɂȂ�
}

// �ړ�
void Boss::CharacterMove(Camera & _camera)
{
	// �F�ύX
	SetModelColor();

	// �E�F�[�u���N���A������G�̍폜
	if (Tower::GetWaveInterval())
	{
		life = 0;
	}

	// ���񂾏ꍇ
	if (life <= 0)
	{
		// 
		life = -1;

		// ���񂾂��Ƃɂ���
		isFinish = true;
	}

	if (isAlive)
	{
		life = 20;
		isAlive = false;
		isFinish = false;
		//EnemyManager::SetEnemyCount(1);
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
		velocity = VScale(characterMove.dir, 0.8f);

		// �ړ��X�V
		characterMove.pos = VAdd(characterMove.pos, velocity);
	}

	// �����ύX
	aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

	// �����X�V
	characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, 0.2f);
}

// �W�����v (���ݕs�g�p)
void Boss::CharacterJump()
{


}

// �A�^�b�N (���ݕs�g�p)
void Boss::CharacterAtack()
{
	// ���ڂ̍U��
	if (characterAtack.isAtack)
	{
		characterMove.isMove = false;
		characterAtack.atackCount++;
	}

	// �U���I��
	if (characterAtack.atackCount >= 60)
	{
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
	}
}

// �A�j���[�V����
void Boss::Animation()
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

	// �A�j���[�V����
	if (characterMove.isMove)
	{
		playTime++;
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

	// �A�j���[�V�������ꍞ��								���ʂ̃^�C��	1�U���A�j���[�V����
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount);
}

// �G�l�~�[�̃Z�b�g
void Boss::SetBoss()
{
	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = true;
	isFinish = false;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 10;
	isAlive = false;

	isHit = false;
}

// �K�E�Z (���ݕs�g�p)
void Boss::CharacterDeathBlow()
{
}

// �G�l�~�[�_���[�W
void Boss::CharacterDamage()
{
	// �����_���[�W
	FastDamage();
}

// �F�ύX
void Boss::SetModelColor()
{
	// �̗͂��ƂɐF��ς���

	if (life == 0)
	{
		isFinish = true;
	}
	else if (life == 10)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (life == 9)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.9f, 0.9f, 0.9f, 1.0f));
	}
	else if (life == 8)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
	}
	else if (life == 7)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
	}
	else if (life == 6)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.6f, 0.6f, 0.6f, 1.0f));
	}
	else if (life == 5)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));
	}
	else if (life == 4)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
	}
	else if (life == 3)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.3f, 0.3f, 0.3f, 1.0f));
	}
	else if (life == 2)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
	}
	else if (life == 1)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.1f, 0.1f, 0.1f, 1.0f));
	}
}

// �v���C���[�̌����Ɉړ�
void Boss::EnemyMove(VECTOR _pos)
{
	characterMove.dir = VSub(_pos, characterMove.pos);
}

// �v���C���[�̌����Ƃ͔��]�Ɉړ�
void Boss::EnemyMoveSub(VECTOR _pos)
{
	characterMove.dir = VSub(characterMove.pos, _pos);
}

// �X�V
void Boss::EnemyUpdate(CharacterBase * _player, Tower *_tower)
{
	/*
	// �{�X���v���C���[�Ɍ������悤�ɂ���
	if (HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 2.0f))
	{
		// �U���t���O�������Ă��Ȃ����
		if (!this->GetAtack())
		{
			this->SetAtack(true);
		}
		if (!this->GetMove())
		{
			this->ClerDir();
		}
	}
	else if (!HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 5.0f) && HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 8))
	{
		if (!this->GetAtack())
		{
			this->EnemyMove(_player->GetPos());
		}

		this->SetMove(true);
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
	*/

	if (life > 0)
	{
		// �G�l�~�[���v���C���Ɍ������悤�ɂ���
		if (HitCheck::HitCheckCircleTowerToEnemy(_tower, this, 2.0f))
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
