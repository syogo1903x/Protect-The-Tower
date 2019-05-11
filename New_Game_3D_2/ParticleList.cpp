#include "ParticleList.h"

int ParticleList::particleNum = 100;

// �ÓI�C���X�^���X�̐���
ParticleList& ParticleList::CreateParticleList()
{
	static ParticleList particleList;
	return particleList;
}

// �R���X�g���N�^
ParticleList::ParticleList()
{
	// �p�[�e�B�N���̃��������m��
	particle = new ParticleEmitter*[particleNum];
	for (int i = 0; i < particleNum; i++)
	{
		// NULL�ŏ�����
		particle[i] = NULL;
	}
}

// �f�X�g���N�^
ParticleList::~ParticleList()
{
	// ������ł��Ă��Ȃ���΁A�֐����Ă�
	if (particle != NULL)
	{
		DestroyParticle();
	}
}

// �p�[�e�B�N���̐���
ParticleEmitter* ParticleList::CreateParticle(ParticleData _particle)
{
	for (int i = 0; i < particleNum; i++)
	{
		// �m�ۂ��悤�Ƃ��Ă���f�[�^��NULL��������
		if (particle[i] == NULL)
		{
			// �p�[�e�B�N���̃f�[�^���m��
			particle[i] = new ParticleEmitter();
			if (particle[i] != NULL)
			{
				// �����̃f�[�^���p�[�e�B�N���ɓn��
				particle[i]->SetParticle(_particle);
				// �Z�b�g���ꂽ�p�[�e�B�N����Ԃ�
				return particle[i];
			}
		}
		else
		{
			// �f�[�^�����Ɋi�[����Ă�����X�L�b�v����
			continue;
		}
	}
}

// �p�[�e�B�N���̍폜
void ParticleList::DestroyParticle()
{
	for (int i = 0; i < particleNum; i++)
	{
		delete(particle[i]);
		particle[i] = NULL;
	}
	delete[](particle);
	particle = NULL;
}

// ������
void ParticleList::Initialize()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (particle[i] != NULL)
		{
			// �p�[�e�B�N��
			particle[i]->Initialize();
		}
	}
}

// �X�V
void ParticleList::Update()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (particle[i] != NULL)
		{
			// �p�[�e�B�N��
			particle[i]->Update();
		}
	}
}

// �`��
void ParticleList::Draw()
{
	for (int i = 0; i < particleNum; i++)
	{
		if (particle[i] != NULL)
		{
			// �p�[�e�B�N��
			particle[i]->Draw();
		}
	}
}