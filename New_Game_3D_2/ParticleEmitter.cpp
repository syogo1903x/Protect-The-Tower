#include "ParticleEmitter.h"
#include <stdio.h>

int ParticleEmitter::particleGraphHandle;

// �R���X�g���N�^
ParticleEmitter::ParticleEmitter()
{
	// �p�[�e�B�N���̉摜��ǂݍ���
	particleGraphHandle = LoadGraph("img/particle.png");
	particlesRandData = NULL;

	// �e�ϐ��̏�����
	particleData.positionRange = VGet(0, 0, 0);	// �o���͈�
	particleData.minDirection  = VGet(0, 0, 0);	// �ŏ��̕���
	particleData.maxDirection  = VGet(0, 0, 0);	// �ő�̕���
	particleData.minRotation   = 0;				// �ŏ��̉�]�p
	particleData.maxRotation   = 0;				// �ő�̉�]�p
	particleData.minScale      = 0;				// �ŏ��̑傫��
	particleData.maxScale      = 0;				// �ő�̑傫��
	particleData.minSpeed      = 0;				// �ŏ��̃X�s�[�h
	particleData.maxSpeed      = 0;				// �ő�̃X�s�[�h
	particleData.minStartTime  = 0;				// �ŏ��̔�������
	particleData.maxStartTime  = 0;				// �ő�̔�������
	particleData.minLifeTime   = 0;				// �ŏ��̐�������
	particleData.maxLifeTime   = 0;				// �ő�̐�������
	particleData.colorRed      = 0;				// ��
	particleData.colorGreen    = 0;				// ��
	particleData.colorBlue     = 0;				// ��
	particleData.alpha         = 0;				// �����x
	particleNum				   = 0;				// ������
	centerPosition             = VGet(0,0,0);
	isActive                   = false;
}

// �f�X�g���N�^
ParticleEmitter::~ParticleEmitter()
{

}


// �p�[�e�B�N���̃f�[�^���Z�b�g
void ParticleEmitter::SetParticle(ParticleData _particle)
{
	// �p�[�e�B�N���̃f�[�^���i�[
	particleData.positionRange = _particle.positionRange;	// �o���͈�
	particleData.minDirection  = _particle.minDirection;	// �ŏ��̕���
	particleData.maxDirection  = _particle.maxDirection;	// �ő�̕���
	particleData.minRotation   = _particle.minRotation;		// �ŏ��̉�]�p
	particleData.maxRotation   = _particle.maxRotation;		// �ő�̉�]�p
	particleData.minScale      = _particle.minScale;		// �ŏ��̑傫��
	particleData.maxScale      = _particle.maxScale;		// �ő�̑傫��
	particleData.minSpeed      = _particle.minSpeed;		// �ŏ��̃X�s�[�h
	particleData.maxSpeed      = _particle.maxSpeed;		// �ő�̃X�s�[�h
	particleData.minStartTime  = _particle.minStartTime;	// �ŏ��̔�������
	particleData.maxStartTime  = _particle.maxStartTime;	// �ő�̔�������
	particleData.minLifeTime   = _particle.minLifeTime;		// �ŏ��̐�������
	particleData.maxLifeTime   = _particle.maxLifeTime;		// �ő�̐�������
	particleData.colorRed      = _particle.colorRed;		// ��
	particleData.colorGreen    = _particle.colorGreen;		// ��
	particleData.colorBlue     = _particle.colorBlue;		// ��
	particleData.alpha         = _particle.alpha;			// �����x
	particleNum				   = _particle.particleNum;		// ������
	// �p�[�e�B�N���𐶐�
	particlesRandData = new ParticleRandData[particleNum];
}

// ������
void ParticleEmitter::Initialize()
{
	for (int i = 0; i < particleNum; i++)
	{
		particlesRandData[i].isActive = false;
	}
}

// �X�V
void ParticleEmitter::Update()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (isActive == true)
		{
			if (particlesRandData[i].isActive == false)
			{
				// �p�[�e�B�N���̏o���͈͂��Z�b�g
				VECTOR tmpPosition;
				tmpPosition = VGet(GetRand(centerPosition.x - particleData.positionRange.x / 2.0f, centerPosition.x + particleData.positionRange.x / 2.0f),		// X��
								   GetRand(centerPosition.y - particleData.positionRange.y / 2.0f, centerPosition.y + particleData.positionRange.y / 2.0f),		// Y��
								   GetRand(centerPosition.z - particleData.positionRange.z / 2.0f, centerPosition.z + particleData.positionRange.z / 2.0f));	// Z��
				particlesRandData[i].position = tmpPosition;

				// �p�[�e�B�N���̌������Z�b�g
				VECTOR tmpDirection = VGet(GetRand(particleData.minDirection.x, particleData.maxDirection.x),	// X��
										   GetRand(particleData.minDirection.y, particleData.maxDirection.y),	// Y��
										   GetRand(particleData.minDirection.z, particleData.maxDirection.z));	// Z��
				// ���K������
				if (VSquareSize(tmpDirection) != 0)
				{
					tmpDirection = VNorm(tmpDirection);
				}
				// ���K�����������x�N�g�����Z�b�g
				particlesRandData[i].direction = tmpDirection;

				// �p�[�e�B�N���̉�]�p���Z�b�g
				particlesRandData[i].Rotation = GetRand(particleData.minRotation, particleData.maxRotation);
				
				// �p�[�e�B�N���̑傫�����Z�b�g
				particlesRandData[i].scale = GetRand(particleData.minScale, particleData.maxScale);

				// �p�[�e�B�N���̃X�s�[�h���Z�b�g
				particlesRandData[i].speed = GetRand(particleData.minSpeed, particleData.maxSpeed);

				// �p�[�e�B�N���̐F���Z�b�g
				colorRed   = particleData.colorRed;
				colorGreen = particleData.colorGreen;
				colorBlue  = particleData.colorBlue;

				// �����x���Z�b�g
				alpha = particleData.alpha;

				// �p�[�e�B�N���̔������Ԃ��Z�b�g
				particlesRandData[i].startTime = (int)GetRand((float)particleData.minStartTime, (float)particleData.maxStartTime);

				// �p�[�e�B�N���̐������Ԃ��Z�b�g
				particlesRandData[i].lifeTime = (int)GetRand((float)particleData.minLifeTime, (float)particleData.maxLifeTime);

				particlesRandData[i].lifeCount = 0;
				particlesRandData[i].startCount = 0;
				particlesRandData[i].isActive = true;
			}

			// �f�[�^����������A�������Ԃ̃J�E���g����
			if (particlesRandData[i].isActive) { particlesRandData[i].startCount++; }

			// ���������p�[�e�B�N���𐧌�
			if (particlesRandData[i].isActive && 
				particlesRandData[i].startCount > particlesRandData[i].startTime)
			{
				particlesRandData[i].lifeCount++;
				// �ړ�����
				VECTOR velocity = VScale(particlesRandData[i].direction, particlesRandData[i].speed);
				particlesRandData[i].position = VAdd(particlesRandData[i].position, velocity);

				// �������Ԃ��o���������
				if (particlesRandData[i].lifeCount > particlesRandData[i].lifeTime)
				{
					// �ϐ��̏�����
					particlesRandData[i].isActive = false;
					particlesRandData[i].lifeCount = 0;
					particlesRandData[i].startCount = 0;
				}
			}
		}
		else
		{
			// �p�[�e�B�N�����@�\���Ă��Ȃ��ꍇ�́A���W�����[���h��Ԃ̔ޕ��ɐݒ�
			centerPosition				  = VGet(900000, 900000, 900000);
			particlesRandData[i].position = VGet(900000, 900000, 900000);
		}
	}
}

// �`��
void ParticleEmitter::Draw()
{
	// Z�o�b�t�@���g�p����
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�̏������݂͍s��Ȃ�
	SetWriteZBuffer3D(FALSE);

	for (int i = 0; i < particleNum; i++)
	{
		if (isActive == true)
		{
			if (particlesRandData[i].isActive &&
				particlesRandData[i].startCount > particlesRandData[i].startTime)
			{
				// �`����x��ݒ�
				SetDrawBright(colorRed, colorGreen, colorBlue);
				// ���Z�u�����h�Ńp�[�e�B�N���̕`��
				SetDrawBlendMode(DX_BLENDMODE_ADD_X4, alpha * 255);
				DrawBillboard3D(particlesRandData[i].position,	// ���W
								0.5f,							// ���S���W�iX���j
								0.5f,							// ���S���W�iY���j
								particlesRandData[i].scale,		// �傫��
								particlesRandData[i].Rotation,	// ��]�p
								particleGraphHandle,			// �O���t�B�b�N�n���h��
								TRUE);							// ���ߏ��������邩

				// �`����x��߂�
				SetDrawBright(255, 255, 255);
				// �m�[�u�����h
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			}
		}
	}
}

// �����̎擾
float ParticleEmitter::GetRand(float _min, float _max)
{
	return _min + (float)(rand() * (_max - _min + 1.0f) / (1.0f + RAND_MAX));
}