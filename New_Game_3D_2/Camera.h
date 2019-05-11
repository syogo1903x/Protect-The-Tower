#pragma once
#include "Common.h"

// 前方宣言
class PlayerBase;

class Camera
{
public:
	Camera();
	~Camera();

	// 初期化
	void		Init();
	// 更新
	void		Update(CharacterBase *_player1, Tower *_tower);
	// カメラぬ向き初期化
	void		CameraDirInit();
	// 描画
	void		Draw();

	// ターゲット向き
	static void	TargetDir(VECTOR _player, Camera *_camera);
	static VECTOR CameraLerp(VECTOR _pVec1, VECTOR _pVec2, float s);

	// 向きセット
	void		SetDir(float _dir) { cameraDir.x = _dir; }
	void		SetDirZ(float _dir) { cameraDir.z = _dir; }
	void		SetPos(VECTOR _pos) { cameraPos = _pos; }
	void		SetPosX(float _pos) { cameraPos.x = _pos; }
	void		SetPosZ(float _pos) { cameraPos.z = _pos; }
	static void	SetTarger(bool _isTarget) { isCameraTarget = _isTarget; }

	// 向き取得
	float		&GetRad() { return cameraDir.x; }
	VECTOR		&GetDir() { return cameraDir; }
	VECTOR		&GetPos() { return cameraPos; }
	VECTOR		&GetMousePos() { return mouse; }
	static bool	&GetTarget() { return isCameraTarget; }
	static VECTOR	&GetCamPos() { return camTmpPos; }
	static bool GetCameraSetComplet() { return isCameraSetComplet; }

private:
	// クリア時カウント
	float clearCameraTimeX;
	float clearCameraTimeZ;

	// カメラ位置
	VECTOR		cameraPos;
	// 見る位置
	VECTOR		viewPos;
	// カメラ向き
	VECTOR		cameraDir;
	// 初期カメラ向き
	VECTOR		cameraDefaultDir;
	// カメラ角度
	float		cameraAngle;

	// カメラのターゲットフラグ
	static bool isCameraTarget;

	// マウス
	VECTOR mouse;

	int newMouseX;
	int newMouseY;

	bool isTarget;

	MATRIX RotV;
	MATRIX RotH;

	// 補正用定数
	const static float MIN_V;
	const static float MAX_V;
	const static float MIN_H;
	const static float MAX_H;
	const static float MIN_R;
	const static float MAX_R;
	const static float ANGLE_RATE;
	const static float ZOOM_RATE;

	// カメラ位置
	static VECTOR camTmpPos;
	static bool isCameraSetComplet;
	bool isCameraSetX;
	bool isCameraSetZ;
	VECTOR tmpGameOverCameraDir;
	VECTOR tmpPos;
	VECTOR cameraMove;
	int gameOverTime;
};