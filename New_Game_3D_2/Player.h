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

	// 初期化
	void		Init(char *_playerNumber) override;
	void		Init(int model) override;
	// キャラクター移動
	void		CharacterMove(Camera &_camera) override;
	// キャラクタージャンプ
	void		CharacterJump() override;
	// キャラクターアタック
	void		CharacterAtack() override;
	// キャラクター必殺技
	void		CharacterDeathBlow() override;
	// アニメーション
	void		Animation() override;
	// キャラクターダメージ
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

	// カメラ角度
	float cameraAngle;
	// カメラ向き
	VECTOR camDir;
	// プレイヤーがカメラを向く
	static float playerTragetCameraPos;
	static VECTOR playerTargetPos;

	// 効果音
	SoundEffect *se[4];

	// 必殺技カウント
	int deathBlowAnimationCount;

	// キャラクターで必殺技を変える変数
	static int characterCount;				// 0.右折ちゃん 1.Ruby 2.ちなみ 3.犬 4.カラス 


	// 定数
	const int PLAYER_LIFE_MAX = 10;						// プレイヤーの体力の最大
	const float DEATHBLOW_COUNT = 100.0f;				// 必殺技の使用カウント
	const int USE_DEATHBLOW_COUNT = 50;					// 必殺技使用可能カウント
	const int NOW_USE_DEATHBLOW_COUNT = 10;				// 必殺技が使用した後のカウント
	const float PLAYER_SPEED = 2.0f;					// プレイヤー移動速度
	const float PLAYER_CAMERA_MAX = 7.0f;				// カメラがプレイヤーに近づく距離
	const float PLAYER_MOVE_TURN = 0.2f;				// プレイヤーの回転力
	const float PLAYER_ATACK_TURN = 1.0f;				// プレイヤーの攻撃時の回転力
	const float JUMP_GRAVITY_ACCEL = 0.15f;				// ジャンプの重力
	const float JUMP_POWER = 3.5f;						// ジャンプ力

};