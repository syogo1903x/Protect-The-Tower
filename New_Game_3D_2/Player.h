#pragma once
#include "CharacterBase.h"
#include "Shot.h"

enum PLAYER_ANIMATION
{
	ANIMATION_WAIT,
	ANIMATION_MOVE,
	ANIMATION_JUMP,
	ANIMATION_ATACK,
	ANIMATION_DEATHBLOW,
	ANIMATION_WIN,
	ANIMATION_LOSE,
};

enum SOUND_EFFECT_PLAYER
{
	SETUP,
	JUMP,
	USE_DEATH_BLOW,
	DEATH_BLOW_START,
};

class Shot;

class Player :public CharacterBase
{
public:
	Player();
	~Player();

	void		Init(char *_playerNumber) override;
	void		Init(int model) override;
	void		CharacterMove(Camera &_camera) override;
	void		CharacterJump() override;
	void		CharacterAtack() override;
	void		CharacterDeathBlow() override;
	void		Animation() override;
	void		CharacterDamage() override;

	// �Q�b�^�[
	// �v���C���[�̃L�����N�^�[�̎擾       0.�E�܂���� 1.Ruby 2.���Ȃ� 3.�� 4.�J���X 
	static int GetCharacterCount() { return characterCount; }


	// �J����������v���C���[�̈ʒu
	static float GetPlayerTargetCameraPos()
	{
		return playerTragetCameraPos;
	}

	// �v���C���[�̈ʒu
	static VECTOR GetPlayerTargetPos()
	{
		return playerTargetPos;
	}


private:
	// ���������֐�
	VECTOR	PlayerMoveDir(VECTOR _pos, Camera &_camera);
	// �v���C���[�ړ�����
	void PlayerMoveProcess();
	// �v���C���[�̈ړ��X�V
	void	PlayerMoveUpdate(Camera &_camera);
	// �v���C���[�̉�]
	void	PlayerRotation(Camera &_camera);
	// �v���C���[��͈͊O�ɏo���Ȃ�
	void	PlayerOutOfRangeWall();

	// �A�j���[�V�����t���[���ő又��
	void AnimationMaxFrame();
	// �A�j���[�V�����ݒ�
	void AninmationConfiguration();
	// �A�j���[�V�����ύX
	void AnimationConfigurationChange();

	float cameraAngle;
	VECTOR camDir;
	static float playerTragetCameraPos;
	static VECTOR playerTargetPos;


	// �萔
	const int PLAYER_LIFE_MAX = 10;
	const float DEATHBLOW_COUNT = 100.0f;
	const int USE_DEATHBLOW_COUNT = 50;
	const int NOW_USE_DEATHBLOW_COUNT = 10;

	const float PLAYER_SPEED = 2.0f;
	const float PLAYER_CAMERA_MAX = 7.0f;
	const float PLAYER_MOVE_TURN = 0.2f;
	const float PLAYER_ATACK_TURN = 1.0f;
	const float JUMP_GRAVITY_ACCEL = 0.15f;
	const float JUMP_POWER = 3.5f;

	SoundEffect *se[4];

	int deathBlowAnimationCount;

	// �L�����N�^�[�ŕK�E�Z��ς���ϐ�
	static int characterCount;				// 0.�E�܂���� 1.Ruby 2.���Ȃ� 3.�� 4.�J���X 


};