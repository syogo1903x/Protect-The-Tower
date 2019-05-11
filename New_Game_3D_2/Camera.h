#pragma once
#include "Common.h"

// �O���錾
class PlayerBase;

class Camera
{
public:
	Camera();
	~Camera();

	// ������
	void		Init();
	// �X�V
	void		Update(CharacterBase *_player1, Tower *_tower);
	// �J�����ʌ���������
	void		CameraDirInit();
	// �`��
	void		Draw();

	// �^�[�Q�b�g����
	static void	TargetDir(VECTOR _player, Camera *_camera);
	static VECTOR CameraLerp(VECTOR _pVec1, VECTOR _pVec2, float s);

	// �����Z�b�g
	void		SetDir(float _dir) { cameraDir.x = _dir; }
	void		SetDirZ(float _dir) { cameraDir.z = _dir; }
	void		SetPos(VECTOR _pos) { cameraPos = _pos; }
	void		SetPosX(float _pos) { cameraPos.x = _pos; }
	void		SetPosZ(float _pos) { cameraPos.z = _pos; }
	static void	SetTarger(bool _isTarget) { isCameraTarget = _isTarget; }

	// �����擾
	float		&GetRad() { return cameraDir.x; }
	VECTOR		&GetDir() { return cameraDir; }
	VECTOR		&GetPos() { return cameraPos; }
	VECTOR		&GetMousePos() { return mouse; }
	static bool	&GetTarget() { return isCameraTarget; }
	static VECTOR	&GetCamPos() { return camTmpPos; }
	static bool GetCameraSetComplet() { return isCameraSetComplet; }

private:
	// �N���A���J�E���g
	float clearCameraTimeX;
	float clearCameraTimeZ;

	// �J�����ʒu
	VECTOR		cameraPos;
	// ����ʒu
	VECTOR		viewPos;
	// �J��������
	VECTOR		cameraDir;
	// �����J��������
	VECTOR		cameraDefaultDir;
	// �J�����p�x
	float		cameraAngle;

	// �J�����̃^�[�Q�b�g�t���O
	static bool isCameraTarget;

	// �}�E�X
	VECTOR mouse;

	int newMouseX;
	int newMouseY;

	bool isTarget;

	MATRIX RotV;
	MATRIX RotH;

	// �␳�p�萔
	const static float MIN_V;
	const static float MAX_V;
	const static float MIN_H;
	const static float MAX_H;
	const static float MIN_R;
	const static float MAX_R;
	const static float ANGLE_RATE;
	const static float ZOOM_RATE;

	// �J�����ʒu
	static VECTOR camTmpPos;
	static bool isCameraSetComplet;
	bool isCameraSetX;
	bool isCameraSetZ;
	VECTOR tmpGameOverCameraDir;
	VECTOR tmpPos;
	VECTOR cameraMove;
	int gameOverTime;
};