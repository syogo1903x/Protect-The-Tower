#include "Common.h"

bool Camera::isCameraTarget = false;
bool Camera::isCameraSetComplet = false;
VECTOR Camera::camTmpPos;

const float Camera::MIN_V = -0.2f;
const float Camera::MAX_V = 0.3f;
const float Camera::MIN_H = 0.0f;
const float Camera::MAX_H = DX_PI_F * 2.0f;
const float Camera::MIN_R = 10.0f;
const float Camera::MAX_R = 30.0f;
const float Camera::ANGLE_RATE = 0.001f;
const float Camera::ZOOM_RATE = 10.0f;

// �R���X�g���N�^
Camera::Camera()
{


}

// �f�X�g���N�^
Camera::~Camera()
{


}

// ������
void Camera::Init()
{
	cameraPos = ZEROCLEAR;
	viewPos = ZEROCLEAR;
	cameraDir = ZEROCLEAR;
	cameraDefaultDir = ZEROCLEAR;
	cameraAngle = 0.0f;

	mouse = ZEROCLEAR;

	newMouseX = 0;
	newMouseY = 0;

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(6.0f, 3000.0f);

	// �}�E�X�̏������W���S
	SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2);

	cameraDir = VGet(0.0f, 0.0f, 50.0f);
	isTarget = false;

	// ���C�g���쐬�@�ύX
	//CreateDirLightHandle(VGet(0.0f, 10.0f, 0.0f));
	//CreateDirLightHandle(VGet(0.0f, -10.0f, 0.0f));
	clearCameraTimeX = -20;
	clearCameraTimeZ = -40;
	gameOverTime = 0;

	tmpGameOverCameraDir = ZEROCLEAR;
	tmpPos = ZEROCLEAR;
	cameraMove = ZEROCLEAR;
	isCameraSetX = false;
	isCameraSetZ = false;
	isCameraSetComplet = false;
}

// �X�V
void Camera::Update(CharacterBase *_player1, Tower *_tower)
{
	// �Q�[���N���A���Ă��Ȃ����
	if (SceneGame::GetGameClear())
	{
		clearCameraTimeX += 2;
		clearCameraTimeZ += 2.8f;

		// �J�����ʒu
		VECTOR tmpPlayerCameraPos = VGet(Player::GetPlayerTargetPos().x, Player::GetPlayerTargetPos().y + Player::GetPlayerTargetCameraPos(), Player::GetPlayerTargetPos().z);

		//�v���C���[�̌�납��̎��_����v���C���[������p�x�ɃJ������ݒu
		SetCameraPositionAndTarget_UpVecY(VAdd(tmpPlayerCameraPos, VGet(-clearCameraTimeX, 5, -clearCameraTimeZ)), tmpPlayerCameraPos);
		// �N���A�^�C���̍ő�
		if (clearCameraTimeX >= 10)
		{
			clearCameraTimeX = 10;
		}
		if (clearCameraTimeZ >= 10)
		{
			clearCameraTimeZ = 10;
		}
	}
	else if (SceneGame::GetGameOver())
	{
		// �Q�[���I�[�o�[�J�E���g�̊J�n
		gameOverTime++;

		// �ŏ����������ƈʒu���Ƃ�
		if (gameOverTime == 1)
		{
			tmpGameOverCameraDir = VSub(VGet(0, 100, -100), _player1->GetPos());
			tmpPos = _player1->GetPos();
		}

		// ���K��
		if (VSquareSize(tmpGameOverCameraDir) != 0)
		{
			tmpGameOverCameraDir = VNorm(tmpGameOverCameraDir);
		}
		// �����ړ�
		cameraMove =  VScale(tmpGameOverCameraDir, 10.0f);

		// �ʒu�X�V
		tmpPos = VAdd(tmpPos, cameraMove);

		// �ő�l�ݒ� Y
		if (tmpPos.y >= 100) { tmpPos.y = 100; }
		// �ő�l�ݒ� Z
		if (tmpGameOverCameraDir.z < 0)
		{
			if (tmpPos.z <= -100) 
			{
				isCameraSetZ = true;
				tmpPos.z = -100; 
			}
		}
		else
		{
			if (tmpPos.z >= -100)
			{ 
				isCameraSetZ = true;
				tmpPos.z = -100;
			}
		}

		// �ő�l�ݒ� X
		if (tmpGameOverCameraDir.x < 0)
		{
			if (tmpPos.x <= 0) 
			{ 
				isCameraSetX = true;
				tmpPos.x = 0;
			}
		}
		else
		{
			if (tmpPos.x >= 0) 
			{ 
				isCameraSetX = true;
				tmpPos.x = 0; 
			}
		}

		// �e�J�������K��l�𒴂�����t���O�̃I��
		if (isCameraSetX && isCameraSetZ)
		{
			isCameraSetComplet = true;
		}

		//�v���C���[�̌�납��̎��_����v���C���[������p�x�ɃJ������ݒu
		SetCameraPositionAndTarget_UpVecY(tmpPos, VGet(_tower->GetPos().x, _tower->GetPos().y + 20, _tower->GetPos().z));
	}
	else
	{

		// �}�E�X�̎擾
		mouse.x = 0;
		mouse.y = 0;
		//mouse.z = (float)-GetMouseWheelRotVol();

		// �Q�[�����n�܂��
		if (SceneGame::GetStart())
		{
			if (!_player1->GetDeathBlow())
			{
				GetMousePoint(&newMouseX, &newMouseY);
				mouse.x = (float)(newMouseX - SCREEN_X / 2);
				mouse.y = (float)(newMouseY - SCREEN_Y / 2);
				SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2);

				if (PAD_INPUT.GetPadInput("1P").ThumbRX <= -10000)
				{
					mouse.x -= 50;
				}
				if (PAD_INPUT.GetPadInput("1P").ThumbRX >= 10000)
				{
					mouse.x += 50;
				}
				if (PAD_INPUT.GetPadInput("1P").ThumbRY <= -10000)
				{
					mouse.y += 50;
				}
				if (PAD_INPUT.GetPadInput("1P").ThumbRY >= 10000)
				{
					mouse.y -= 50;
				}
			}
			else if (_player1->GetDeathBlow())
			{
				SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2);
				// �J��������]������
				//mouse.x += 61;

				//if (mouse.z > 1.0f) mouse.z = 1.0f;
				// �J�����̏k���@�g��
				//if (_player1->GetDeathBlowAnimationCount() < 70)
				//{
				//	mouse.z -= 0.1f;
				//}
				//else
				//{
				//	mouse.z += 1.f;
				//}
			}

			// �U�����ł���΃J�������߂Â���
			if (_player1->GetAtack())
			{
				mouse.z = -2;
			}
			else
			{
				mouse.z = 1;
			}
		}
		else
		{
			// �J��������]������
			mouse.x += 24;
		}

		//if (mouse.z > 2)mouse.z = 2;
		//if (mouse.z < -2)mouse.z = -2;

		// �}�E�X�̏�񂩂�J�����̏��ɕϊ�
		cameraDir.y -= mouse.y * ANGLE_RATE;
		cameraDir.x += mouse.x * ANGLE_RATE;
		cameraDir.z += mouse.z * ZOOM_RATE;

		// �␳
		if (cameraDir.y > MAX_V) { cameraDir.y = MAX_V; }
		if (cameraDir.y < MIN_V) { cameraDir.y = MIN_V; }
		if (cameraDir.x > MAX_H) { cameraDir.x -= MAX_H; }
		if (cameraDir.x < MIN_H) { cameraDir.x += MAX_H; }
		if (cameraDir.z > MAX_R) { cameraDir.z = MAX_R; }
		if (cameraDir.z < MIN_R) { cameraDir.z = MIN_R; }

		// �J�����̐ݒ�
		RotV = MGetRotX(cameraDir.y);
		RotH = MGetRotY(cameraDir.x);
		cameraPos = VTransform(VTransform(VGet(0.0f, -Player::GetPlayerTargetCameraPos(), -cameraDir.z), RotV), RotH);

		VECTOR tmpCameraPos = VSub(Player::GetPlayerTargetPos(), cameraPos);
		camTmpPos = tmpCameraPos;

		//�v���C���[�̌�납��̎��_����v���C���[������p�x�ɃJ������ݒu
		SetCameraPositionAndTarget_UpVecY(tmpCameraPos, VGet(Player::GetPlayerTargetPos().x, Player::GetPlayerTargetPos().y + Player::GetPlayerTargetCameraPos(), Player::GetPlayerTargetPos().z));
	}
}

// �J��������������
void Camera::CameraDirInit()
{
	cameraPos = ZEROCLEAR;
	viewPos = ZEROCLEAR;
	cameraDir = ZEROCLEAR;
	cameraDefaultDir = ZEROCLEAR;
	cameraAngle = 0.0f;
}

void Camera::Draw()
{

}

// �J�����̃^�[�Q�b�g����  (�g��Ȃ�)
void Camera::TargetDir(VECTOR  _player , Camera *_camera)
{
	// atan2 ���g�p���Ċp�x���擾
	double angle = atan2(_player.x, _player.z);

	_camera->SetDir((float)angle);
}

// �J�����̈ړ�
VECTOR Camera::CameraLerp(VECTOR _pVec1, VECTOR _pVec2, float s)
{
	VECTOR _outVec;

	_outVec.x = _pVec1.x + s * (_pVec2.x - _pVec1.x);
	_outVec.y = _pVec1.y + s * (_pVec2.y - _pVec1.y);
	_outVec.z = _pVec1.z + s * (_pVec2.z - _pVec1.z);

	return _outVec;
}
