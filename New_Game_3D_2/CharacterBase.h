#pragma once
#include "Atack.h"
#include "Move.h"
#include "Jump.h"

// 前方宣言
class Camera;
class Shot;
class Tower;
class SoundEffect;

class CharacterBase
{
public:
	CharacterBase() {};
	virtual ~CharacterBase() {};

	virtual		void AnimationInit();
	virtual		void Update(Camera &_camera);
	virtual		void Draw();
	virtual		void Release();
	virtual		void FastDamage();
	virtual		void SlowDamage();
	virtual		void OnHit(CharacterBase *_player);

	virtual		void Init(int model) = 0;
	virtual		void Init(char *_playerNumber) = 0;
	virtual		void Animation() = 0;
	virtual		void CharacterJump() = 0;
	virtual		void CharacterMove(Camera &_camera) = 0;
	virtual		void CharacterAtack() = 0;
	virtual		void CharacterDeathBlow() = 0;
	virtual		void CharacterDamage() = 0;

	// 吹き飛ばし処理
	virtual		void FlutterCharacter();

	// セッター
	// ポジションセット
	void SetPos(const VECTOR _pos) { characterMove.pos = _pos; }
	void SetPosX(const float _pos) { characterMove.pos.x = _pos; }
	void SetPosY(const float _pos) { characterMove.pos.y = _pos; }
	void SetPosZ(const float _pos) { characterMove.pos.z = _pos; }
	// ジャンプセット
	void SetJumpPower(const float _power) { jumpGravity = _power; }
	void SetJump(const bool _isJump) { characterJump.isJump = _isJump; }
	void SetJumpCount(const int _Jump) { characterJump.jumpCount = _Jump; }
	// アタックセット
	void SetAtack(const bool _set) { characterAtack.isAtack = _set; }
	//void SetAtack2(const bool _set) { characterAtack.isAtack[1] = _set; }
	//void SetAtack3(const bool _set) { characterAtack.isAtack[2] = _set; }
	// ムーブセット
	void SetMove(const bool _set) { characterMove.isMove = _set; }
	// 体力減少
	void SetLifeDecrease(const int _decrease) { life -= _decrease; }
	// 体力増少
	void SetLife(const int _decrease) { life += _decrease; }
	// 半径セット
	void SetRadius(const float _radius) { radius = _radius; }
	// ダメージセット
	void SetDamage(const bool _isDamage) { isDamage = _isDamage; }
	void SetDeathBlowDamage(const bool _isDamage) { isDeathBlowDamage = _isDamage; }
	// 生きているかのセット
	void SetAlive(const bool _isAlive) { isAlive = _isAlive; }
	// 必殺技カウントセット
	void  SetDeathBlowCount(const float _setCount) { characterAtack.deathBlowCount += _setCount; }
	void SetTmpDirection(const VECTOR _tmp) { tmpDirection = _tmp; }
	// お金のセッター
	void SetMoney(const int _set) { money += _set; }
	// ヒットセット
	void SetHit(const bool _set) { isHit = _set; }


	// ゲッター
	// ポジション取得
	const VECTOR &GetPos() const { return characterMove.pos; }
	// 向き取得
	const VECTOR &GetDir() const { return characterMove.dir; }
	const VECTOR &GetAngle() const { return characterMove.angle; }
	// ライフ取得
	const int &GetLife() const { return life; }
	// 半径取得
	const float &GetRadius() const { return radius; }
	// モデル取得
	const int &GetModel() const { return modelHandle; }
	// ダメージ
	const bool &GetDamage()const { return isDamage; }
	const bool &GetDeathBlowDamage() const { return isDeathBlowDamage; }
	// ジャンプ
	const bool &GetJump()const { return characterJump.isJump; }
	const int &GetJumpCount()const { return characterJump.jumpCount; }
	// アタック
	const bool &GetAtack()const { return characterAtack.isAtack; }
	//const bool &GetAtack2()const { return characterAtack.isAtack[1]; }
	//const bool &GetAtack3()const { return characterAtack.isAtack[2]; }
	// 移動
	const bool &GetMove()const { return characterMove.isMove; }
	// 必殺技カウント
	const float &GetDeathBlowCount() const { return characterAtack.deathBlowCount; }
	// 必殺技使用可能
	const bool &GetStartDeathBlow() const { return characterAtack.isDeathBlow; }
	// 必殺技が使われた
	const bool &GetDeathBlow() const { return characterAtack.isUseDeathBlow; }
	// 必殺技アニメーションカウント
	const int &GetDeathBlowAnimationCount() const { return characterAtack.deathBlowAnimationCount; }
	// 生きているかの取得
	const bool &GetALive() const { return isAlive; }
	// 死んでいる
	const bool &GetDead() const { return isFinish; }
	// キャラサイズの取得
	const float &GetCharaSize() const { return charaScale; }
	// 弾の取得
	Shot &GetShot() { return *shot; }
	// お金の取得
	int GetMoney() { return money; }
	// ヒットの取得
	bool GetHit() { return isHit; }

protected:
	Atack		characterAtack;		// 攻撃
	Move		characterMove;		// 移動
	Jump		characterJump;		// ジャンプ
	Shot		*shot;


	// モデルハンドル
	int modelHandle;
	// 今の角度
	float aimAngle;

	// 速度
	VECTOR velocity;

	// アニメーション
	int animAttachIndex;
	// アニメーション移動
	int moveAnimFrameIndex;
	// アニメーション時間
	float totalTime;
	float playTime;
	// 現在のアニメーションの番号
	int playAnim;

	// 体力
	int life;
	// 食らったとき
	bool isDamage;
	int damageCount;
	// ダメージしたかどうか
	bool isHit;
	// 必殺技時のダメージ
	bool isDeathBlowDamage;

	// 半径
	float radius;

	// ジャンプ時の重力
	float jumpGravity;
	// 攻撃
	bool isFinish;

	// 死んでいるかどうか
	bool isAlive;

	// キャラのサイズ
	float charaScale;

	// キャラクタ―の向きを一時保存
	VECTOR tmpDirection;

	int money;

	// 効果音
	SoundEffect *hitDamegeSe;
	SoundEffect *loseDamegeSe;
};