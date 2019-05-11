#pragma once
#include "ParticleEmitter.h"

class ParticleEmitter;

// �p�[�e�B�N�� / �Ǘ��N���X
class ParticleList final
{
public:
	// �ÓI�C���X�^���X�̐���
	static ParticleList& CreateParticleList();

	~ParticleList();	// �f�X�g���N�^

	void Initialize();	// ������
	void Update();		// �X�V
	void Draw();		// �`��

	// �p�[�e�B�N���̐���
	ParticleEmitter* CreateParticle(ParticleData _particle);
	void             DestroyParticle();

private:
	ParticleList();						// �V���O���g��
	ParticleEmitter **particle;
	static int        particleNum;		// �p�[�e�B�N���̐�
};

#define PARTICLE_LIST ParticleList::CreateParticleList()