#include "Common.h"

VECTOR Player::playerTargetPos;
float Player::playerTragetCameraPos;
int Player::characterCount;

// �R���X�g���N�^
Player::Player()
{


}

// �f�X�g���N�^
Player::~Player()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	for (int i = 0; i < 4; i++)
	{
		if (se[i])
		{
			se[i]->StopSoundEffect();
			se[i]->Release();
			se[i] = NULL;
			delete(se[i]);
		}
	}
}

// ������
void Player::Init(char *_playerNumber)
{
	modelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::PLAYER));

	if (modelHandle < 0)
	{
		printfDx("error");
	}

	// �A�j���[�V�����̏�����
	AnimationInit();

	// �W�����v�̏d��
	jumpGravity = 1.0f;
	// �̗�
	life = PLAYER_LIFE_MAX;
	// ���a
	radius = 5.0f;

	// �U�������t���O
	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	// ���ʉ��ǂݍ���
	se[SETUP] = new SoundEffect("Music/SE/set.mp3");
	se[JUMP] = new SoundEffect("Music/SE/knife-throw1.mp3");
	se[USE_DEATH_BLOW] = new SoundEffect("Music/SE/ko.mp3");
	se[DEATH_BLOW_START] = new SoundEffect("Music/SE/cannon2.mp3");

	// �L�����N�^�[���Ƃ̃T�C�Y�ϊ�
	if (_playerNumber == "character/original/MMD�p�x�錢_Gun/������.pmx" || _playerNumber == "character/original/MMD�p�x��J���X_Gun/MMD�p�x��J���X.pmx")
	{
		MV1SetScale(modelHandle, VGet(1.2f, 1.2f, 1.2f));
		charaScale = 0.7f;
	}
	else
	{
		charaScale = 1.0f;
	}

	// �e�v���C���[�̎��̊e�󋵂̎擾
	if (_playerNumber == "character/original/�E�܂����_Gun/ukon.pmx")					{ playerTragetCameraPos = 10.0f; characterCount = 0;}
	if (_playerNumber == "character/original/Ruby_Gun/Ruby.pmx")						{ playerTragetCameraPos = 14.0f; characterCount = 1;}
	if (_playerNumber == "character/original/���Ȃ��Ȃ�_Gun/���Ȃ��Ȃ�V4.pmx")			{ playerTragetCameraPos = 11.0f; characterCount = 2;}
	if (_playerNumber == "character/original/MMD�p�x�錢_Gun/������.pmx")				{ playerTragetCameraPos = 16.0f; characterCount = 3;}
	if (_playerNumber == "character/original/MMD�p�x��J���X_Gun/MMD�p�x��J���X.pmx")	{ playerTragetCameraPos = 13.0f; characterCount = 4;}

	// �t���O
	characterJump.isJump = false;

	characterMove.isMove = false;
	characterMove.pos = PLAYER_INIT_POS;
	characterMove.dir = ZEROCLEAR;
	characterMove.angle = ZEROCLEAR;
	isDamage = false;
	isDeathBlowDamage = false;
	isFinish = false;

	// �_���[�W�J�E���g
	damageCount = 0;
	
	// �K�E�Z
	characterAtack.isDeathBlow = false;
	characterAtack.isUseDeathBlow = false;
	characterAtack.deathBlowCount = 0; 
	characterAtack.deathBlowAnimationCount = 0;
	characterAtack.isNowDeathBlow = false;

	deathBlowAnimationCount = 0;
	tmpDirection = ZEROCLEAR;
	
	// �e�̒e����
	shot = new Shot;
	shot->CreateShot(50);
}

void Player::Init(int model)
{
	// ~���ɂȂ�
}

// �ړ�����
void Player::CharacterMove(Camera &_camera)
{
	// �d�͒ǉ�
	characterMove.pos.y -= jumpGravity;
	// ��������ɏ�����
	characterMove.dir = ZEROCLEAR;
	// �̗͂̏��
	if (life >= PLAYER_LIFE_MAX) { life = PLAYER_LIFE_MAX; }

	// �v���C���[�ړ�����
	PlayerMoveProcess();
	// �v���C���[�̈ړ��X�V
	PlayerMoveUpdate(_camera);
	// �v���C���[�̉�]
	PlayerRotation(_camera);
	// �v���C���[��͈͊O�ɏo���Ȃ�
	PlayerOutOfRangeWall();

	// �|�W�V�����X�V
	MV1SetPosition(modelHandle, characterMove.pos);
}

// �W�����v����
void Player::CharacterJump()
{
	// �Q�[���N���A���Ă��Ȃ���΂܂��̓Q�[���I�|�o�[�ł͂Ȃ����
	if (!SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// �K�E�Z������Ă��Ȃ����
		if (!characterAtack.isUseDeathBlow)
		{
			// �W�����v
			if (KEY_INPUT.GetKey(KEY_INPUT_SPACE) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A))
			{
				if (!characterJump.isJump) se[JUMP]->PlaySoundEffect();
				characterJump.isJump = true;
			}

			// �W�����v��
			if (characterJump.isJump)
			{
				characterJump.jumpCount++;
				characterMove.pos.y += JUMP_POWER;
			}
			// ��ɏd��
			jumpGravity += JUMP_GRAVITY_ACCEL;
		}
	}
}

// �U������
void Player::CharacterAtack()
{
	// �e�̒e�̈ʒu�̎擾
	VECTOR tmpBulPos = VNorm(VSub(playerTargetPos, Camera::GetCamPos()));
	VECTOR playerAimPos = VGet(tmpBulPos.x, (characterMove.angle.x) / 1.5f , tmpBulPos.z);
	// �e�̒e�𔭎ˏo�����
	shot->BulletShot(playerAimPos, characterMove.pos);

	// �Q�[���N���A���Ă��Ȃ���΂܂��̓Q�[���I�|�o�[�ł͂Ȃ����
	if (!SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// �W�����v���Ă��Ȃ���΍U���\
		if (!characterJump.isJump && !characterAtack.isUseDeathBlow)
		{
			// �}�E�X�̉E�������ꂽ
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_LEFT_SHOULDER))
			{
				se[SETUP]->PlaySoundEffect();
			}
			// �}�E�X�̉E��������Ă���
			if (MOUSE_INPUT.MousePresed(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPressed("1P", XINPUT_BUTTON_LEFT_SHOULDER))
			{
				// �U�����
				characterAtack.isAtack = true;
				// �}�E�X�̍��������ꂽ�u��
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_RIGHT_SHOULDER))
				{
					//
					shot->OneBulletPlay();
				}
				// �}�E�X�̍���������Ă��
				if (MOUSE_INPUT.MousePresed(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPressed("1P", XINPUT_BUTTON_RIGHT_SHOULDER))
				{
					// 
					shot->BulletPlay();
				}
			}
			else
			{
				characterAtack.isAtack = false;
			}
		}
	}

	// �e�̒e��������
	shot->Draw();
}


// �Ђ����킴
void Player::CharacterDeathBlow()
{
	// �K�E�Z�J�E���g�����
	characterAtack.deathBlowCount += 0.1f;

	// �K�E�Z�J�E���g���K��l�𒴂���� �K�E�Z�\���
	if (characterAtack.deathBlowCount > DEATHBLOW_COUNT)
	{
		// �Q�[�W���ʉ��Đ�
		se[USE_DEATH_BLOW]->OnePlaySoundEffect();

		characterAtack.isDeathBlow = true;
		characterAtack.isUseDeathBlow = false;
		characterAtack.deathBlowCount = DEATHBLOW_COUNT;
	}

	// �f�o�b�N�p �K�E�Z�Q�[�W����
	if (CheckHitKey(KEY_INPUT_1)) {characterAtack.deathBlowCount = DEATHBLOW_COUNT ;}

	// �Q�[���N���A���Ă��Ȃ���΂܂��̓Q�[���I�|�o�[�ł͂Ȃ����
	if (!SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// �K�E�Z�\��Ԃ̎�
		if (characterAtack.isDeathBlow && !characterJump.isJump)
		{
			// �K�E�Z���g�����Ԃł����
			if (!characterAtack.isUseDeathBlow)
			{
				// �g�����
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_MIDDLE) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_X))
				{
					// �Q�[�W���ʉ���~
					se[USE_DEATH_BLOW]->StopSoundEffect();
					// �K�E�Z���ʉ��Đ�
					se[DEATH_BLOW_START]->OnePlaySoundEffect();

					// �A�j���[�V������K�E�Z�ɂ���
					characterAtack.isDeathBlow = false;
					characterAtack.deathBlowCount = 0;
					deathBlowAnimationCount = 0;
					characterAtack.isUseDeathBlow = true;
					characterAtack.isNowDeathBlow = true;
				}
			}
		}
	}

	// �K�E�Z�̂̂�����A�j���[�V�����J�E���g
	if (characterAtack.deathBlowAnimationCount > 0 && characterAtack.deathBlowAnimationCount <= USE_DEATHBLOW_COUNT / 2)
	{
		deathBlowAnimationCount ++;
	}

	if (characterAtack.deathBlowAnimationCount > USE_DEATHBLOW_COUNT / 2 && characterAtack.deathBlowAnimationCount <= USE_DEATHBLOW_COUNT)
	{
		deathBlowAnimationCount --;
	}

	// �J���������]������J���������Ȃ��悤�ɂ��邽�߂ɕK�E�Z����߂����Ƃɂ���
	if (characterAtack.isUseDeathBlow)
	{
		if (characterAtack.deathBlowAnimationCount > USE_DEATHBLOW_COUNT)
		{
			// �K�E�Z���ʉ���~
			se[DEATH_BLOW_START]->StopSoundEffect();
			// �K�E�Z�g�p�\�t���O���I�t
			characterAtack.isUseDeathBlow = false;
		}
	}

	// �K�E�Z�����𒴂���� �g�����Ԃɂ���
	if (characterAtack.deathBlowCount > NOW_USE_DEATHBLOW_COUNT)
	{
		characterAtack.isNowDeathBlow = false;
	}
}

// �A�j���[�V����
void Player::Animation()
{

	// �v���C���[�̃G�t�F�N�g
	EFFECT.UpdatePlayer(this);

	// �A�j���[�V�����t���[���ő又��
	AnimationMaxFrame();
	// �A�j���[�V�����ݒ�
	AninmationConfiguration();
	// �A�j���[�V�����ύX
	AnimationConfigurationChange();

	// �A�j���[�V�������ꍞ��							���ʂ̃^�C��			�\��
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount + deathBlowAnimationCount);
}

// �L�����N�^�[�_���[�W
void Player::CharacterDamage()
{
	// �������_���[�W
	SlowDamage();
}

// �J�����̌������v�Z
VECTOR Player::PlayerMoveDir(VECTOR _pos, Camera &_camera)
{
	VECTOR tmpPos;
	float sinPram = sinf(_camera.GetRad());
	float cosPram = cosf(_camera.GetRad());

	tmpPos.x =  _pos.z * sinPram - _pos.x * cosPram;
	tmpPos.y = 0;
	tmpPos.z = _pos.x * sinPram + _pos.z * cosPram;

	return tmpPos;
}

void Player::PlayerMoveProcess()
{
	// �Q�[�����n�܂��ĂĂ��Q�[���N���A���Ă��Ȃ���΂܂��̓Q�[���I�|�o�[�ł͂Ȃ����
	if (SceneGame::GetStart() && !SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// ���ړ�
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
		{
			characterMove.dir.x = -1;
		}
		// �E�ړ�
		if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
		{
			characterMove.dir.x = 1;
		}
		// �����낢�ǂ�
		if (KEY_INPUT.GetKey(KEY_INPUT_S) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000)
		{
			characterMove.dir.z = 1;
		}
		// �O�ړ�
		if (KEY_INPUT.GetKey(KEY_INPUT_W) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000)
		{
			characterMove.dir.z = -1;
		}
	}
}

// �v���C���[�̈ړ��X�V
void Player::PlayerMoveUpdate(Camera &_camera)
{
	// ���K��
	if (VSquareSize(characterMove.dir) != 0)
	{
		characterMove.dir = VNorm(characterMove.dir);
	}

	// �K�E�Z�����Ă��Ȃ���Έړ��\
	if (!characterAtack.isUseDeathBlow)
	{
		// �x���V�e�B
		velocity = VScale(characterMove.dir, PLAYER_SPEED);

		// �ړ��X�V
		characterMove.pos = VAdd(characterMove.pos, PlayerMoveDir(velocity, _camera));
	}
	else
	{
		if (characterAtack.deathBlowAnimationCount > 0 && characterAtack.deathBlowAnimationCount <= USE_DEATHBLOW_COUNT / 2)
		{
			// �x���V�e�B
			velocity = VScale(VGet(0, 0, 1), PLAYER_SPEED / 4);

			// �ړ��X�V
			characterMove.pos = VAdd(characterMove.pos, PlayerMoveDir(velocity, _camera));
		}
	}

	// �U���\��Ԃł���� �J�������߂Â���
	if (characterAtack.isAtack)
	{
		playerTargetPos = VAdd(characterMove.pos, VScale(PlayerMoveDir(VGet(-1, 0, 0), _camera), PLAYER_CAMERA_MAX));
	}
	else
	{
		// �J����������v���C���[�̐�̃|�W�V����
		playerTargetPos = characterMove.pos;
	}

	// �J�����̌����Ɉړ�
	if (SceneGame::GetGameClear())
	{
		// ��������ɏ�����
		characterMove.dir = ZEROCLEAR;

		characterMove.dir = PlayerMoveDir(characterMove.dir, _camera);
	}
	else if (characterMove.isMove && !characterAtack.isAtack)
	{
		characterMove.dir = PlayerMoveDir(characterMove.dir, _camera);
	}
	// �U�����ł���΍\����
	else if (characterAtack.isAtack)
	{
		characterMove.dir = PlayerMoveDir(VSub(ZEROCLEAR, VNorm(_camera.GetDir())), _camera);
	}
	// �����Ă��Ȃ��ꍇ�̓J�����̌�����������������
	else
	{
		characterMove.dir = PlayerMoveDir(VSub(characterMove.dir, VNorm(_camera.GetDir())), _camera);
	}
}

// �v���C���[�̉�]
void Player::PlayerRotation(Camera &_camera)
{
	// �㉺��]�p
	camDir = VSub(_camera.GetDir(), characterMove.dir);
	// �����ύX
	cameraAngle = vec2Radian(&VGet(0, -1, 0), &camDir);

	// �U�������Ă��Ȃ���Ό����X�V
	if (!characterAtack.isUseDeathBlow && !characterAtack.isAtack || SceneGame::GetGameClear())
	{
		// �����ύX
		aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

		// ���E�̉�]
		characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, PLAYER_MOVE_TURN);

		// �㉺�̉�]���Ȃ���
		characterMove.angle.x = lerpRadian(characterMove.angle.x, 0, 1.f);
	}
	// �U�����ł���΃��f���̉�]���㉺�ƍ��E�ɂ���
	else if (!characterAtack.isUseDeathBlow && characterAtack.isAtack)
	{
		// �J�����̕���������
		VECTOR camtraget = VNorm(VSub(characterMove.pos, Camera::GetCamPos()));
		float camtragetY = atan2(camtraget.x, camtraget.z);

		// ���E�̉�]
		characterMove.angle.y = lerpRadian(characterMove.angle.y, (camtragetY + PI / 1.3f) /*+ playerHorizontal*/, PLAYER_ATACK_TURN);

		// �㉺�̉�]
		characterMove.angle.x = lerpRadian(characterMove.angle.x, (cameraAngle - PI / 2.f), PLAYER_ATACK_TURN);
	}

	// ��]�X�V�@���Q�[�����n�܂��Ă����
	if (SceneGame::GetStart())
	{
		MV1SetRotationXYZ(modelHandle, characterMove.angle);
	}
}

// �v���C���[��͈͊O�ɏo���Ȃ�
void Player::PlayerOutOfRangeWall()
{
	// �������
	if (characterMove.pos.x >= 310) { characterMove.pos.x = 310; }
	if (characterMove.pos.x <= -310) { characterMove.pos.x = -310; }

	if (characterMove.pos.z >= 250) { characterMove.pos.z = 250; }
	if (characterMove.pos.z <= -420) { characterMove.pos.z = -420; }

	// �L�����N�^�[���߂Â�����͈͊O�ɏo���Ȃ��ǂ��o��
	if (characterMove.pos.x >= 250) { Stage::SetDangerTrans(0, 0.05f); }
	else { Stage::SetDangerTrans(0, -0.05f); }
	if (characterMove.pos.x <= -250) { Stage::SetDangerTrans(2, 0.05f); }
	else { Stage::SetDangerTrans(2, -0.05f); }

	if (characterMove.pos.z >= 200) { Stage::SetDangerTrans(1, 0.05f); }
	else { Stage::SetDangerTrans(1, -0.05f); }
	if (characterMove.pos.z <= -350) { Stage::SetDangerTrans(3, 0.05f); }
	else { Stage::SetDangerTrans(3, -0.05f); }

	// �͈͊O�o���Ƃ���
	if (characterMove.pos.y <= -50) { characterMove.pos = PLAYER_INIT_POS; }
}


// �A�j���[�V�����t���[���ő又��
void Player::AnimationMaxFrame()
{
	// �e�A�j���[�V�����̍ő�t���[���ݒ�
	if (SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		characterAtack.deathBlowAnimationCount = 0;
		deathBlowAnimationCount = 0;
	}
	else if (characterAtack.isUseDeathBlow)		// �K�E�Z
	{
		characterAtack.deathBlowAnimationCount++;
		playTime = 0;
		characterAtack.atackCount = 0;
	}
	else if (characterJump.isJump)					// �W�����v
	{
		playTime = totalTime / 2;
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
		characterAtack.deathBlowAnimationCount = 0;
	}
	else if (characterAtack.isAtack)			// �U������
	{
		playTime = 0;
	}
	else if (characterMove.isMove)				// �����Ă���Ƃ�
	{
		characterAtack.deathBlowAnimationCount = 0;
		deathBlowAnimationCount = 0;

		if (playTime >= totalTime)
		{
			playTime -= totalTime;
		}
	}
	else										// �ҋ@
	{
		characterAtack.deathBlowAnimationCount = 0;
		deathBlowAnimationCount = 0;
		if (playTime >= totalTime)
		{
			playTime = 6;
		}
	}
}

// �A�j���[�V�����ݒ�
void Player::AninmationConfiguration()
{
	// �Q�[���N���A���Ă��Ȃ���΂܂��̓Q�[���I�|�o�[�ł͂Ȃ����
	if (SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// �ړ��A�j���[�V�����̕ύX
		totalTime = AnimationChange(playAnim, ANIMATION_WIN, modelHandle, animAttachIndex, totalTime);
		//
		playTime++;
	}
	else if (characterAtack.isUseDeathBlow && !characterJump.isJump)
	{
		// �U���A�j���[�V�����̕ύX
		totalTime = AnimationChange(playAnim, ANIMATION_DEATHBLOW, modelHandle, animAttachIndex, totalTime);
	}
	// �W�����v��
	else if (characterJump.isJump)
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
}

// �A�j���[�V�����ύX
void Player::AnimationConfigurationChange()
{
	// �Q�[�����n�܂��ĂĂ��Q�[���N���A���Ă��Ȃ���΂܂��̓Q�[���I�|�o�[�ł͂Ȃ����
	if (SceneGame::GetStart() && !SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// �A�j���[�V����
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else if (KEY_INPUT.GetKey(KEY_INPUT_S) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else if (KEY_INPUT.GetKey(KEY_INPUT_W) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else
		{
			characterMove.isMove = false;
		}
	}
}
