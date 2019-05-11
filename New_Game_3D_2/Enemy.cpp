#include "Common.h"

// コンストラクタ
Enemy::Enemy()
{


}

// デストラクタ
Enemy::~Enemy()
{
	// モデル削除
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

// 初期化
void Enemy::Init(int model)
{
	// モデル読み込み
	modelHandle = MV1DuplicateModel(model);
	// アニメーションの初期化
	AnimationInit();

	if (modelHandle < 0)
	{
		printfDx("データ読み込みに失敗");
	}

	characterMove.dir = ZEROCLEAR;
	characterMove.angle = ZEROCLEAR;
	
	jumpGravity = 1.0f;

	radius = 5.0f;

	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = false;
	isFinish = true;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;

	life = 3;
	isAlive = false;

	pos = characterMove.pos;
}

void Enemy::Init(char * _playerNumber)
{
	// ~とくになし
}

// 移動
void Enemy::CharacterMove(Camera & _camera)
{
	// ウェーブがクリアしたら敵の削除
	if (Tower::GetWaveInterval())
	{
		life = 0;
	}

	//EnemyFlagControl();
	if (isAlive)
	{
		life = 3;
		isFinish = false;
		isAlive = false;
	}

	// 敵の色変更
	if (life == 3)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (life == 2)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
	}

	if (life == 1)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
	}

	if (life <= 0)
	{
		// 
		life = -1;

		isFinish = true;
	}

	// 回転更新
	MV1SetRotationXYZ(modelHandle, characterMove.angle);
	// 位置更新
	MV1SetPosition(modelHandle, characterMove.pos);

	// 重力
	characterMove.pos.y -= jumpGravity;

	// 正規化
	if (VSquareSize(characterMove.dir) != 0)
	{
		characterMove.dir = VNorm(characterMove.dir);
	}

	// 攻撃していなければ移動可能
	if (!characterAtack.isAtack)
	{
		// ベロシティ
		velocity = VScale(characterMove.dir, 1.5f);

		// 移動更新
		characterMove.pos = VAdd(characterMove.pos, velocity);
	}

	// 向き変更
	aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

	// 向き更新
	characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, 0.2f);
}

// ジャンプ (現在不使用)
void Enemy::CharacterJump()
{
	// ジャンプ
	if (characterJump.isJump)
	{
		jumpGravity += 0.1f;
		characterMove.pos.y += 3.5f;
	}
}

// アタック (現在不使用)
void Enemy::CharacterAtack()
{
	// ~~あたっただけでダメージ
}

// アニメーション
void Enemy::Animation()
{
	// ジャンプ時
	if (characterJump.isJump)
	{
		// ジャンプアニメーションの変更
		totalTime = AnimationChange(playAnim, ANIMATION_JUMP, modelHandle, animAttachIndex, totalTime);
	}
	else if (characterAtack.isAtack && !characterJump.isJump)
	{
		// 攻撃アニメーションの変更
		totalTime = AnimationChange(playAnim, ANIMATION_ATACK , modelHandle, animAttachIndex, totalTime);
	}
	else if (characterMove.isMove && !characterAtack.isAtack)
	{
		// 移動アニメーションの変更
		totalTime = AnimationChange(playAnim, ANIMATION_MOVE, modelHandle, animAttachIndex, totalTime);
	}
	else
	{
		playTime++;
		// 待機アニメーションの変更
		totalTime = AnimationChange(playAnim, ANIMATION_WAIT, modelHandle, animAttachIndex, totalTime);
	}

	// アニメーション
	if (characterMove.isMove)
	{
		playTime += 2;
	}


	// 各アニメーションの最大フレーム設定
	if (characterJump.isJump)
	{
		playTime = totalTime / 2;
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
	}
	else if (characterAtack.isAtack)
	{
		playTime = 0;
	}
	else if (characterMove.isMove)
	{
		if (playTime >= totalTime)
		{
			playTime -= totalTime;
		}
	}
	else
	{
		if (playTime >= totalTime)
		{
			playTime = 10;
		}
	}

	// アニメーション入れ込み							普通のタイム	1攻撃アニメーション		2攻撃アニメーション
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount);
}

// キャラクターダメージ
void Enemy::CharacterDamage()
{
	// 早くダメージ
	FastDamage();
}

// エネミーのセット
void Enemy::SetEnemy()
{

	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = true;
	isFinish = false;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;

	life = 3;
	isAlive = false;

	isHit = false;
}

// 必殺技 (現在不使用)
void Enemy::CharacterDeathBlow()
{

}

// プレイヤーの向きに移動
void Enemy::EnemyMove(VECTOR _pos)
{
	characterMove.dir = VSub(_pos, characterMove.pos);
}

// エネミー更新
void Enemy::EnemyUpdate(CharacterBase * _player, Tower *_tower)
{
	// エネミーの体力があれば
	if (life > 0)
	{
		// エネミーがプレイヤに向かうようにする
		if (HitCheck::HitCheckCircleTowerToEnemy(_tower, this, 5.0f))
		{
			if (!_tower->GetHit())
			{
				loseDamegeSe->PlaySoundEffect();
				_tower->SetHit(true);
				_tower->SetLifeDamege(5);
				// タワーに当たったことを知らせる
				isHit = true;
			}
			life = -1;
		}
		else
		{
			this->EnemyMove(_tower->GetPos());
		}
	}

}

