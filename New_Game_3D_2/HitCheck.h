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

	// プレイヤーとエネミーの攻撃の当たり判定
	static void HitCheckBoxPlayerToOtherPlayer(CharacterBase *_player1, CharacterBase *_player2);

	// プレイヤーとプレイヤーのぶつかり当たり判定
	static void HitCheckCirclePlayerToOtherPlayer(CharacterBase *_player1, CharacterBase *_player2);

	// プレイヤーの必殺技のエネミーダメージ当たり判定
	static void HitCheckCirclePlayerDeathBlowToEnemy(CharacterBase *_player1, CharacterBase *_player2);

	// プレイヤーとエネミーのぶつかり当たり判定
	static bool HitCheckCirclePlayerToEnemy(CharacterBase *_player1, CharacterBase *_player2);
	// タワーとエネミーの当たり判定
	static bool HitCheckCircleTowerToEnemy(Tower *_tower, CharacterBase *_enemy, float _size);

	// プレイヤーと中ボスの範囲の当たり判定
	static bool HitCheckCirclePlayerToMediumBoss(CharacterBase *_player1, CharacterBase *_player2, float _size);

	// プレイヤーとボスの攻撃当たり判定
	static void HitCheckBoxPlayerToBoss(CharacterBase *_player1, CharacterBase *_player2);

	// プレイヤーとエネミーのぶつかり当たり判定
	static VECTOR HitCheckCirclePlayerToEnemy(CharacterBase *_player1, CharacterBase *_player2, Camera *_camera);

	// アイテムとプレイヤーの当たり判定
	static void HitCheckBoxPlayerToItem(CharacterBase *_player1, ItemBase *_item);

	// アイテムとプレイヤーの当たり判定
	static void HitCheckBoxPlayerToCoin(CharacterBase *_player1, ItemBase *_item);

	// アイテムとプレイヤーの当たり判定
	static bool HitCheckCirclePlayerToItemAttract(CharacterBase *_player1, ItemBase *_item, float _scale);


	// 地面との当たり判定
	static void HitCheckPlayerToGound(CharacterBase *_player, Stage *_stage, float _scale);

	// プレイヤーの銃と敵の当たり判定
	static void HitCheckGun(VECTOR _gunPos, CharacterBase *_player2, float _scale);

	// タワーディフェンス用壁との当たり判定
	static void HitCheckDefenseWall(DefenseBase *_defense, CharacterBase *_player, float _scale, int _hitDamage);
	// タワーディフェンスアタック用壁との当たり判定
	static void HitCheckDefenseAtackBall(DefenseBase *_defense, CharacterBase *_player, float _scale,int _atackDamage, int _hitDamage);
	// タワーディフェンス炎用壁との当たり判定
	static void HitCheckDefenseFire(DefenseBase *_defense, CharacterBase *_player, float _scale, int _atackDamage, int _hitDamage);
	// タワーディフェンス兵士用壁との当たり判定
	static void HitCheckDefenseSoldier(DefenseBase *_defense, CharacterBase *_player, float _scale, int _hitDamage);
	// エネミーとディフェンス兵士のぶつかり当たり判定
	static bool HitCheckCircleEnemyToSoldier(CharacterBase *_enemy, DefenseBase *_soldier, float _scale);
	// タワーディフェンス兵士の弾用壁との当たり判定
	static void HitCheckDefenseSoldierBullet(DefenseBase *_defense, CharacterBase *_player, float _scale, int _atackDamage);


	// アイテムショッピングとプレイヤーの当たり判定
	static bool HitCheckBoxPlayerToBuyItemObject(CharacterBase *_player1, DefenseBase *_defense1);

private:
	// 当たり判定開始を距離で測る
	static bool AskObjectLength(VECTOR _pos1, VECTOR _pos2);


};