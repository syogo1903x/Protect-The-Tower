#include "Common.h"

// �R���X�g���N�^
Enemy::Enemy()
{


}

// �f�X�g���N�^
Enemy::~Enemy()
{
	// ���f���폜
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

// ������
void Enemy::Init(int model)
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

	life = 3;
	isAlive = false;

	pos = characterMove.pos;
}

void Enemy::Init(char * _playerNumber)
{
	// ~�Ƃ��ɂȂ�
}

// �ړ�
void Enemy::CharacterMove(Camera & _camera)
{
	// �E�F�[�u���N���A������G�̍폜
	if (Tower::GetWaveInterval())
	{
		life = 0;
	}

	//EnemyFlagControl();
	if (isAlive)
	{
		life = 3;
		isFinish = false;
		isAlive = false;
	}

	// �G�̐F�ύX
	if (life == 3)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (life == 2)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
	}

	if (life == 1)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
	}

	if (life <= 0)
	{
		// 
		life = -1;

		isFinish = true;
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
		velocity = VScale(characterMove.dir, 1.5f);

		// �ړ��X�V
		characterMove.pos = VAdd(characterMove.pos, velocity);
	}

	// �����ύX
	aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

	// �����X�V
	characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, 0.2f);
}

// �W�����v (���ݕs�g�p)
void Enemy::CharacterJump()
{
	// �W�����v
	if (characterJump.isJump)
	{
		jumpGravity += 0.1f;
		characterMove.pos.y += 3.5f;
	}
}

// �A�^�b�N (���ݕs�g�p)
void Enemy::CharacterAtack()
{
	// ~~�������������Ń_���[�W
}

// �A�j���[�V����
void Enemy::Animation()
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
		totalTime = AnimationChange(playAnim, ANIMATION_ATACK , modelHandle, animAttachIndex, totalTime);
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
		playTime += 2;
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

	// �A�j���[�V�������ꍞ��							���ʂ̃^�C��	1�U���A�j���[�V����		2�U���A�j���[�V����
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount);
}

// �L�����N�^�[�_���[�W
void Enemy::CharacterDamage()
{
	// �����_���[�W
	FastDamage();
}

// �G�l�~�[�̃Z�b�g
void Enemy::SetEnemy()
{

	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = true;
	isFinish = false;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;

	life = 3;
	isAlive = false;

	isHit = false;
}

// �K�E�Z (���ݕs�g�p)
void Enemy::CharacterDeathBlow()
{

}

// �v���C���[�̌����Ɉړ�
void Enemy::EnemyMove(VECTOR _pos)
{
	characterMove.dir = VSub(_pos, characterMove.pos);
}

// �G�l�~�[�X�V
void Enemy::EnemyUpdate(CharacterBase * _player, Tower *_tower)
{
	// �G�l�~�[�̗̑͂������
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

