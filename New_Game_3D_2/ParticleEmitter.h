#pragma once
#include <DxLib.h>

// �p�[�e�B�N���̃f�[�^���i�[����\����
struct ParticleData
{
	VECTOR positionRange;	// �o���͈�
	VECTOR minDirection;	// �ŏ��̕���
	VECTOR maxDirection;	// �ő�̕���
	float  minRotation;		// �ŏ��̉�]�p
	float  maxRotation;		// �ő�̉�]�p
	float  minScale;		// �ŏ��̑傫��
	float  maxScale;		// �ő�̑傫��
	float  minSpeed;		// �ŏ��̃X�s�[�h
	float  maxSpeed;		// �ő�̃X�s�[�h
	int    minStartTime;	// �ŏ��̔�������
	int    maxStartTime;	// �ő�̔�������
	int    minLifeTime;		// �ŏ��̐�������
	int    maxLifeTime;		// �ő�̐�������
	int    colorRed;		// ��
	int    colorGreen;		// ��
	int    colorBlue;		// ��
	int    alpha;			// �����x
	int    particleNum;		// ������
};


// �p�[�e�B�N��
class ParticleEmitter
{
public:
				 ParticleEmitter();	// �R���X�g���N�^
				~ParticleEmitter();	// �f�X�g���N�^

			void Initialize();		// ������
			void Update();			// �X�V
			void Draw();			// �`��

	inline float GetRand(float _min,float _max);		// �������擾
			void SetParticle(ParticleData _particle);	// �p�[�e�B�N���𐶐�
			
			// �Z�b�^�[�֐��Q
			void SetCenterPosition(VECTOR _set) { centerPosition             = _set; }	// ���S���W
			void SetActive		  (bool   _set) { isActive                   = _set; }	// ��������
			void SetPositionRange (VECTOR _set) { particleData.positionRange = _set; }	// �o���͈�
			void SetMinDirection  (VECTOR _set) { particleData.minDirection  = _set; }	// �ŏ��̕���
			void SetMaxDirection  (VECTOR _set) { particleData.maxDirection  = _set; }	// �ő�̕���
			void SetMinRotation   (float  _set) { particleData.minRotation   = _set; }	// �ŏ��̉�]�p
			void SetMaxRotation   (float  _set) { particleData.maxRotation   = _set; }	// �ő�̉�]�p
			void SetMinScale      (float  _set) { particleData.minScale      = _set; }	// �ŏ��̑傫��
			void SetMaxScale      (float  _set) { particleData.maxScale      = _set; }	// �ő�̑傫��
			void SetMinSpeed      (float  _set) { particleData.minSpeed      = _set; }	// �ŏ��̃X�s�[�h
			void SetMaxSpeed      (float  _set) { particleData.maxSpeed      = _set; }	// �ő�̃X�s�[�h
			void SetMinStartTime  (int    _set) { particleData.minStartTime  = _set; }	// �ŏ��̔�������
			void SetMaxStartTime  (int    _set) { particleData.maxStartTime  = _set; }	// �ő�̔�������
			void SetMinLifeTime   (int    _set) { particleData.minLifeTime   = _set; }	// �ŏ��̐�������
			void SetMaxLifeTime   (int    _set) { particleData.maxLifeTime   = _set; }	// �ő�̐�������
			void SetColorRed      (int    _set) { particleData.colorRed      = _set; }	// ��
			void SetColorGreen    (int    _set) { particleData.colorGreen    = _set; }	// ��
			void SetColorBlue     (int    _set) { particleData.colorBlue     = _set; }	// ��
			void SetAlpha         (int    _set) { particleData.alpha         = _set; }	// �����x
			void SetParticleNum   (int    _set) { particleData.particleNum   = _set; }	// ������

private:
	// �p�[�e�B�N���̗������i�[����\����
	struct ParticleRandData
	{
		VECTOR position;		// �o���ʒu
		VECTOR direction;		// ����
		float  Rotation;		// ��]�p
		float  scale;			// �傫��
		float  speed;			// �X�s�[�h
		int    startTime;		// ��������
		int    startCount;		// �������Ԃ̃J�E���g
		int    lifeTime;		// ��������
		int    lifeCount;		// �������Ԃ̃J�E���g
		bool   isActive;		// ��������Ă��邩
	};

	static int        particleGraphHandle;	// �O���t�B�b�N�n���h��
	ParticleData      particleData;			// �p�[�e�B�N���̃f�[�^���i�[
	VECTOR			  centerPosition;		// ���S���W
	ParticleRandData *particlesRandData;	// �p�[�e�B�N���̗������i�[
	int				  colorRed;				// ��
	int				  colorGreen;			// ��
	int				  colorBlue;			// ��
	int               alpha;				// �����x
	int				  particleNum;			// ������
	bool              isActive;				// �p�[�e�B�N������������

};