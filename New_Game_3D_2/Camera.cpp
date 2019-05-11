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

// コンストラクタ
Camera::Camera()
{


}

// デストラクタ
Camera::~Camera()
{


}

// 初期化
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

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(6.0f, 3000.0f);

	// マウスの初期座標中心
	SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2);

	cameraDir = VGet(0.0f, 0.0f, 50.0f);
	isTarget = false;

	// ライトを作成　変更
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

// 更新
void Camera::Update(CharacterBase *_player1, Tower *_tower)
{
	// ゲームクリアしていなければ
	if (SceneGame::GetGameClear())
	{
		clearCameraTimeX += 2;
		clearCameraTimeZ += 2.8f;

		// カメラ位置
		VECTOR tmpPlayerCameraPos = VGet(Player::GetPlayerTargetPos().x, Player::GetPlayerTargetPos().y + Player::GetPlayerTargetCameraPos(), Player::GetPlayerTargetPos().z);

		//プレイヤーの後ろからの視点からプレイヤーを見る角度にカメラを設置
		SetCameraPositionAndTarget_UpVecY(VAdd(tmpPlayerCameraPos, VGet(-clearCameraTimeX, 5, -clearCameraTimeZ)), tmpPlayerCameraPos);
		// クリアタイムの最大
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
		// ゲームオーバーカウントの開始
		gameOverTime++;

		// 最初だけ向きと位置をとる
		if (gameOverTime == 1)
		{
			tmpGameOverCameraDir = VSub(VGet(0, 100, -100), _player1->GetPos());
			tmpPos = _player1->GetPos();
		}

		// 正規化
		if (VSquareSize(tmpGameOverCameraDir) != 0)
		{
			tmpGameOverCameraDir = VNorm(tmpGameOverCameraDir);
		}
		// 向き移動
		cameraMove =  VScale(tmpGameOverCameraDir, 10.0f);

		// 位置更新
		tmpPos = VAdd(tmpPos, cameraMove);

		// 最大値設定 Y
		if (tmpPos.y >= 100) { tmpPos.y = 100; }
		// 最大値設定 Z
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

		// 最大値設定 X
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

		// 各カメラが規定値を超えたらフラグのオン
		if (isCameraSetX && isCameraSetZ)
		{
			isCameraSetComplet = true;
		}

		//プレイヤーの後ろからの視点からプレイヤーを見る角度にカメラを設置
		SetCameraPositionAndTarget_UpVecY(tmpPos, VGet(_tower->GetPos().x, _tower->GetPos().y + 20, _tower->GetPos().z));
	}
	else
	{

		// マウスの取得
		mouse.x = 0;
		mouse.y = 0;
		//mouse.z = (float)-GetMouseWheelRotVol();

		// ゲームが始まれば
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
				// カメラを回転させる
				//mouse.x += 61;

				//if (mouse.z > 1.0f) mouse.z = 1.0f;
				// カメラの縮小　拡大
				//if (_player1->GetDeathBlowAnimationCount() < 70)
				//{
				//	mouse.z -= 0.1f;
				//}
				//else
				//{
				//	mouse.z += 1.f;
				//}
			}

			// 攻撃中であればカメラを近づける
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
			// カメラを回転させる
			mouse.x += 24;
		}

		//if (mouse.z > 2)mouse.z = 2;
		//if (mouse.z < -2)mouse.z = -2;

		// マウスの情報からカメラの情報に変換
		cameraDir.y -= mouse.y * ANGLE_RATE;
		cameraDir.x += mouse.x * ANGLE_RATE;
		cameraDir.z += mouse.z * ZOOM_RATE;

		// 補正
		if (cameraDir.y > MAX_V) { cameraDir.y = MAX_V; }
		if (cameraDir.y < MIN_V) { cameraDir.y = MIN_V; }
		if (cameraDir.x > MAX_H) { cameraDir.x -= MAX_H; }
		if (cameraDir.x < MIN_H) { cameraDir.x += MAX_H; }
		if (cameraDir.z > MAX_R) { cameraDir.z = MAX_R; }
		if (cameraDir.z < MIN_R) { cameraDir.z = MIN_R; }

		// カメラの設定
		RotV = MGetRotX(cameraDir.y);
		RotH = MGetRotY(cameraDir.x);
		cameraPos = VTransform(VTransform(VGet(0.0f, -Player::GetPlayerTargetCameraPos(), -cameraDir.z), RotV), RotH);

		camTmpPos = VSub(Player::GetPlayerTargetPos(), cameraPos);

		//プレイヤーの後ろからの視点からプレイヤーを見る角度にカメラを設置
		SetCameraPositionAndTarget_UpVecY(camTmpPos, VGet(Player::GetPlayerTargetPos().x, Player::GetPlayerTargetPos().y + Player::GetPlayerTargetCameraPos(), Player::GetPlayerTargetPos().z));
	}
}

// カメラ向き初期化
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

// カメラのターゲット処理  (使わない)
void Camera::TargetDir(VECTOR  _player , Camera *_camera)
{
	// atan2 を使用して角度を取得
	double angle = atan2(_player.x, _player.z);

	_camera->SetDir((float)angle);
}

// カメラの移動
VECTOR Camera::CameraLerp(VECTOR _pVec1, VECTOR _pVec2, float s)
{
	VECTOR _outVec;

	_outVec.x = _pVec1.x + s * (_pVec2.x - _pVec1.x);
	_outVec.y = _pVec1.y + s * (_pVec2.y - _pVec1.y);
	_outVec.z = _pVec1.z + s * (_pVec2.z - _pVec1.z);

	return _outVec;
}
