#pragma once
#include "Atack.h"
#include "Move.h"
#include "Jump.h"

// �O���錾
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

	// ������΂�����
	virtual		void FlutterCharacter();

	// �Z�b�^�[
	// �|�W�V�����Z�b�g
	void SetPos(const VECTOR _pos) { characterMove.pos = _pos; }
	void SetPosX(const float _pos) { characterMove.pos.x = _pos; }
	void SetPosY(const float _pos) { characterMove.pos.y = _pos; }
	void SetPosZ(const float _pos) { characterMove.pos.z = _pos; }
	// �W�����v�Z�b�g
	void SetJumpPower(const float _power) { jumpGravity = _power; }
	void SetJump(const bool _isJump) { characterJump.isJump = _isJump; }
	void SetJumpCount(const int _Jump) { characterJump.jumpCount = _Jump; }
	// �A�^�b�N�Z�b�g
	void SetAtack(const bool _set) { characterAtack.isAtack = _set; }
	//void SetAtack2(const bool _set) { characterAtack.isAtack[1] = _set; }
	//void SetAtack3(const bool _set) { characterAtack.isAtack[2] = _set; }
	// ���[�u�Z�b�g
	void SetMove(const bool _set) { characterMove.isMove = _set; }
	// �̗͌���
	void SetLifeDecrease(const int _decrease) { life -= _decrease; }
	// �̗͑���
	void SetLife(const int _decrease) { life += _decrease; }
	// ���a�Z�b�g
	void SetRadius(const float _radius) { radius = _radius; }
	// �_���[�W�Z�b�g
	void SetDamage(const bool _isDamage) { isDamage = _isDamage; }
	void SetDeathBlowDamage(const bool _isDamage) { isDeathBlowDamage = _isDamage; }
	// �����Ă��邩�̃Z�b�g
	void SetAlive(const bool _isAlive) { isAlive = _isAlive; }
	// �K�E�Z�J�E���g�Z�b�g
	void  SetDeathBlowCount(const float _setCount) { characterAtack.deathBlowCount += _setCount; }
	void SetTmpDirection(const VECTOR _tmp) { tmpDirection = _tmp; }
	// �����̃Z�b�^�[
	void SetMoney(const int _set) { money += _set; }
	// �q�b�g�Z�b�g
	void SetHit(const bool _set) { isHit = _set; }


	// �Q�b�^�[
	// �|�W�V�����擾
	const VECTOR &GetPos() const { return characterMove.pos; }
	// �����擾
	const VECTOR &GetDir() const { return characterMove.dir; }
	const VECTOR &GetAngle() const { return characterMove.angle; }
	// ���C�t�擾
	const int &GetLife() const { return life; }
	// ���a�擾
	const float &GetRadius() const { return radius; }
	// ���f���擾
	const int &GetModel() const { return modelHandle; }
	// �_���[�W
	const bool &GetDamage()const { return isDamage; }
	const bool &GetDeathBlowDamage() const { return isDeathBlowDamage; }
	// �W�����v
	const bool &GetJump()const { return characterJump.isJump; }
	const int &GetJumpCount()const { return characterJump.jumpCount; }
	// �A�^�b�N
	const bool &GetAtack()const { return characterAtack.isAtack; }
	//const bool &GetAtack2()const { return characterAtack.isAtack[1]; }
	//const bool &GetAtack3()const { return characterAtack.isAtack[2]; }
	// �ړ�
	const bool &GetMove()const { return characterMove.isMove; }
	// �K�E�Z�J�E���g
	const float &GetDeathBlowCount() const { return characterAtack.deathBlowCount; }
	// �K�E�Z�g�p�\
	const bool &GetStartDeathBlow() const { return characterAtack.isDeathBlow; }
	// �K�E�Z���g��ꂽ
	const bool &GetDeathBlow() const { return characterAtack.isUseDeathBlow; }
	// �K�E�Z�A�j���[�V�����J�E���g
	const int &GetDeathBlowAnimationCount() const { return characterAtack.deathBlowAnimationCount; }
	// �����Ă��邩�̎擾
	const bool &GetALive() const { return isAlive; }
	// ����ł���
	const bool &GetDead() const { return isFinish; }
	// �L�����T�C�Y�̎擾
	const float &GetCharaSize() const { return charaScale; }
	// �e�̎擾
	Shot &GetShot() { return *shot; }
	// �����̎擾
	int GetMoney() { return money; }
	// �q�b�g�̎擾
	bool GetHit() { return isHit; }

protected:
	Atack		characterAtack;		// �U��
	Move		characterMove;		// �ړ�
	Jump		characterJump;		// �W�����v
	Shot		*shot;


	// ���f���n���h��
	int modelHandle;
	// ���̊p�x
	float aimAngle;

	// ���x
	VECTOR velocity;

	// �A�j���[�V����
	int animAttachIndex;
	// �A�j���[�V�����ړ�
	int moveAnimFrameIndex;
	// �A�j���[�V��������
	float totalTime;
	float playTime;
	// ���݂̃A�j���[�V�����̔ԍ�
	int playAnim;

	// �̗�
	int life;
	// �H������Ƃ�
	bool isDamage;
	int damageCount;
	// �_���[�W�������ǂ���
	bool isHit;
	// �K�E�Z���̃_���[�W
	bool isDeathBlowDamage;

	// ���a
	float radius;

	// �W�����v���̏d��
	float jumpGravity;
	// �U��
	bool isFinish;

	// ����ł��邩�ǂ���
	bool isAlive;

	// �L�����̃T�C�Y
	float charaScale;

	// �L�����N�^�\�̌������ꎞ�ۑ�
	VECTOR tmpDirection;

	int money;

	// ���ʉ�
	SoundEffect *hitDamegeSe;
	SoundEffect *loseDamegeSe;
};