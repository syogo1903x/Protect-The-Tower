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

	// ゲッター
	// プレイヤーのキャラクターの取得       0.右折ちゃん 1.Ruby 2.ちなみ 3.犬 4.カラス 
	static int GetCharacterCount() { return characterCount; }


	// カメラが見るプレイヤーの位置
	static float GetPlayerTargetCameraPos()
	{
		return playerTragetCameraPos;
	}

	// プレイヤーの位置
	static VECTOR GetPlayerTargetPos()
	{
		return playerTargetPos;
	}


private:
	// 内部処理関数
	VECTOR	PlayerMoveDir(VECTOR _pos, Camera &_camera);
	// プレイヤー移動処理
	void PlayerMoveProcess();
	// プレイヤーの移動更新
	void	PlayerMoveUpdate(Camera &_camera);
	// プレイヤーの回転
	void	PlayerRotation(Camera &_camera);
	// プレイヤーを範囲外に出さない
	void	PlayerOutOfRangeWall();

	// アニメーションフレーム最大処理
	void AnimationMaxFrame();
	// アニメーション設定
	void AninmationConfiguration();
	// アニメーション変更
	void AnimationConfigurationChange();

	float cameraAngle;
	VECTOR camDir;
	static float playerTragetCameraPos;
	static VECTOR playerTargetPos;


	// 定数
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

	// キャラクターで必殺技を変える変数
	static int characterCount;				// 0.右折ちゃん 1.Ruby 2.ちなみ 3.犬 4.カラス 


};