#include "Common.h"

// コンストラクタ
Boss::Boss()
{


}

// デストラクタ
Boss::~Boss()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

// 初期化
void Boss::Init(int model)
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

	radius = 20.0f;
	jumpGravity = 1.0f;

	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;


	characterJump.isJump = false;
	characterMove.isMove = false;
	isFinish = true;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 10;
	isAlive = false;

	pos = characterMove.pos;
}

void Boss::Init(char * _playerNumber)
{
	// ~とくになし
}

// 移動
void Boss::CharacterMove(Camera & _camera)
{
	// 色変更
	SetModelColor();

	// ウェーブがクリアしたら敵の削除
	if (Tower::GetWaveInterval())
	{
		life = 0;
	}

	// 死んだ場合
	if (life <= 0)
	{
		// 
		life = -1;

		// 死んだことにする
		isFinish = true;
	}

	if (isAlive)
	{
		life = 20;
		isAlive = false;
		isFinish = false;
		//EnemyManager::SetEnemyCount(1);
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
		velocity = VScale(characterMove.dir, 0.8f);

		// 移動更新
		characterMove.pos = VAdd(characterMove.pos, velocity);
	}

	// 向き変更
	aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

	// 向き更新
	characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, 0.2f);
}

// ジャンプ (現在不使用)
void Boss::CharacterJump()
{


}

// アタック (現在不使用)
void Boss::CharacterAtack()
{
	// 一回目の攻撃
	if (characterAtack.isAtack)
	{
		characterMove.isMove = false;
		characterAtack.atackCount++;
	}

	// 攻撃終了
	if (characterAtack.atackCount >= 60)
	{
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
	}
}

// アニメーション
void Boss::Animation()
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
		totalTime = AnimationChange(playAnim, ANIMATION_ATACK, modelHandle, animAttachIndex, totalTime);
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
		playTime++;
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

	// アニメーション入れ込み								普通のタイム	1攻撃アニメーション
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount);
}

// エネミーのセット
void Boss::SetBoss()
{
	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = true;
	isFinish = false;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 10;
	isAlive = false;

	isHit = false;
}

// 必殺技 (現在不使用)
void Boss::CharacterDeathBlow()
{
}

// エネミーダメージ
void Boss::CharacterDamage()
{
	// 早くダメージ
	FastDamage();
}

// 色変更
void Boss::SetModelColor()
{
	// 体力ごとに色を変える

	if (life == 0)
	{
		isFinish = true;
	}
	else if (life == 10)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else if (life == 9)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.9f, 0.9f, 0.9f, 1.0f));
	}
	else if (life == 8)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
	}
	else if (life == 7)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
	}
	else if (life == 6)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.6f, 0.6f, 0.6f, 1.0f));
	}
	else if (life == 5)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.5f, 0.5f, 0.5f, 1.0f));
	}
	else if (life == 4)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.4f, 0.4f, 0.4f, 1.0f));
	}
	else if (life == 3)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.3f, 0.3f, 0.3f, 1.0f));
	}
	else if (life == 2)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
	}
	else if (life == 1)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(0.1f, 0.1f, 0.1f, 1.0f));
	}
}

// プレイヤーの向きに移動
void Boss::EnemyMove(VECTOR _pos)
{
	characterMove.dir = VSub(_pos, characterMove.pos);
}

// プレイヤーの向きとは反転に移動
void Boss::EnemyMoveSub(VECTOR _pos)
{
	characterMove.dir = VSub(characterMove.pos, _pos);
}

// 更新
void Boss::EnemyUpdate(CharacterBase * _player, Tower *_tower)
{
	/*
	// ボスがプレイヤーに向かうようにする
	if (HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 2.0f))
	{
		// 攻撃フラグが立っていなければ
		if (!this->GetAtack())
		{
			this->SetAtack(true);
		}
		if (!this->GetMove())
		{
			this->ClerDir();
		}
	}
	else if (!HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 5.0f) && HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 8))
	{
		if (!this->GetAtack())
		{
			this->EnemyMove(_player->GetPos());
		}

		this->SetMove(true);
	}
	else if (!HitCheck::HitCheckCircleTowerToEnemy(_tower, this, 10))
	{
		this->EnemyMove(_tower->GetPos());
	}
	else
	{
		if (!_tower->GetHit())
		{
			_tower->SetHit(true);
			_tower->SetLifeDamege(10);
		}
		life = 0;
	}
	*/

	if (life > 0)
	{
		// エネミーがプレイヤに向かうようにする
		if (HitCheck::HitCheckCircleTowerToEnemy(_tower, this, 2.0f))
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
