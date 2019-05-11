#pragma once
#include "Common.h"
#define PLAYER_H			10.0f
#define PLAYER_Y			2.0f
#define PLAYER_X			4.0f
#define PLAYER_Z			4.0f


class HitCheck
{
public:
	HitCheck();
	~HitCheck();

	// �v���C���[�ƃG�l�~�[�̍U���̓����蔻��
	static void HitCheckBoxPlayerToOtherPlayer(CharacterBase *_player1, CharacterBase *_player2);

	// �v���C���[�ƃv���C���[�̂Ԃ��蓖���蔻��
	static void HitCheckCirclePlayerToOtherPlayer(CharacterBase *_player1, CharacterBase *_player2);

	// �v���C���[�̕K�E�Z�̃G�l�~�[�_���[�W�����蔻��
	static void HitCheckCirclePlayerDeathBlowToEnemy(CharacterBase *_player1, CharacterBase *_player2);

	// �v���C���[�ƃG�l�~�[�̂Ԃ��蓖���蔻��
	static bool HitCheckCirclePlayerToEnemy(CharacterBase *_player1, CharacterBase *_player2);
	// �^���[�ƃG�l�~�[�̓����蔻��
	static bool HitCheckCircleTowerToEnemy(Tower *_tower, CharacterBase *_enemy, float _size);

	// �v���C���[�ƒ��{�X�͈̔͂̓����蔻��
	static bool HitCheckCirclePlayerToMediumBoss(CharacterBase *_player1, CharacterBase *_player2, float _size);

	// �v���C���[�ƃ{�X�̍U�������蔻��
	static void HitCheckBoxPlayerToBoss(CharacterBase *_player1, CharacterBase *_player2);

	// �v���C���[�ƃG�l�~�[�̂Ԃ��蓖���蔻��
	static VECTOR HitCheckCirclePlayerToEnemy(CharacterBase *_player1, CharacterBase *_player2, Camera *_camera);

	// �A�C�e���ƃv���C���[�̓����蔻��
	static void HitCheckBoxPlayerToItem(CharacterBase *_player1, ItemBase *_item);

	// �A�C�e���ƃv���C���[�̓����蔻��
	static void HitCheckBoxPlayerToCoin(CharacterBase *_player1, ItemBase *_item);

	// �A�C�e���ƃv���C���[�̓����蔻��
	static bool HitCheckCirclePlayerToItemAttract(CharacterBase *_player1, ItemBase *_item, float _scale);


	// �n�ʂƂ̓����蔻��
	static void HitCheckPlayerToGound(CharacterBase *_player, Stage *_stage, float _scale);

	// �v���C���[�̏e�ƓG�̓����蔻��
	static void HitCheckGun(VECTOR _gunPos, CharacterBase *_player2, float _scale);

	// �^���[�f�B�t�F���X�p�ǂƂ̓����蔻��
	static void HitCheckDefenseWall(DefenseBase *_defense, CharacterBase *_player, float _scale, int _hitDamage);
	// �^���[�f�B�t�F���X�A�^�b�N�p�ǂƂ̓����蔻��
	static void HitCheckDefenseAtackBall(DefenseBase *_defense, CharacterBase *_player, float _scale,int _atackDamage, int _hitDamage);
	// �^���[�f�B�t�F���X���p�ǂƂ̓����蔻��
	static void HitCheckDefenseFire(DefenseBase *_defense, CharacterBase *_player, float _scale, int _atackDamage, int _hitDamage);
	// �^���[�f�B�t�F���X���m�p�ǂƂ̓����蔻��
	static void HitCheckDefenseSoldier(DefenseBase *_defense, CharacterBase *_player, float _scale, int _hitDamage);
	// �G�l�~�[�ƃf�B�t�F���X���m�̂Ԃ��蓖���蔻��
	static bool HitCheckCircleEnemyToSoldier(CharacterBase *_enemy, DefenseBase *_soldier, float _scale);
	// �^���[�f�B�t�F���X���m�̒e�p�ǂƂ̓����蔻��
	static void HitCheckDefenseSoldierBullet(DefenseBase *_defense, CharacterBase *_player, float _scale, int _atackDamage);


	// �A�C�e���V���b�s���O�ƃv���C���[�̓����蔻��
	static bool HitCheckBoxPlayerToBuyItemObject(CharacterBase *_player1, DefenseBase *_defense1);

private:
	// �����蔻��J�n�������ő���
	static bool AskObjectLength(VECTOR _pos1, VECTOR _pos2);


};