#include "Common.h"

// コンストラクタ
MediumBoss::MediumBoss()
{


}

// デストラクタ
MediumBoss::~MediumBoss()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;
}

// 初期化
void MediumBoss::Init(int model)
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
	life = 6;
	isAlive = false;

	MV1SetDifColorScale(modelHandle, GetColorF(redColor, greenColor, blueColor, 1.1f));

	pos = characterMove.pos;
}

void MediumBoss::Init(char * _playerNumber)
{
	// ~とくになし
}

// 移動
void MediumBoss::CharacterMove(Camera & _camera)
{
	SetModelColor();

	// ウェーブがクリアしたら敵の削除
	if (Tower::GetWaveInterval())
	{
		life = 0;
	}

	// 死んだ場合
	if (life <= 0)
	{
		// 死んだことにする
		isFinish = true;
		// 
		life = -1;
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
		velocity = VScale(characterMove.dir, 1.0f);

		// 移動更新
		characterMove.pos = VAdd(characterMove.pos, velocity);
	}

	// 向き変更
	aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

	// 向き更新
	characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, 0.2f);
	

}

// ジャンプ (現在不使用)
void MediumBoss::CharacterJump()
{


}

// アタック (現在不使用)
void MediumBoss::CharacterAtack()
{

	// 一回目の攻撃
	if (characterAtack.isAtack)
	{
		characterAtack.atackCount++;
	}

}

// アニメーション
void MediumBoss::Animation()
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

	// 各アニメーションの最大フレーム設定
	if (characterJump.isJump)
	{
		playTime = totalTime / 2;
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
	}
	else if (characterAtack.isAtack)
	{
		characterAtack.atackCount = 0;
		playTime = 0;
	}
	else if (characterAtack.isAtack)
	{
		if (characterAtack.atackCount >= totalTime)
		{
			characterAtack.isAtack = false;
		}
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

	// アニメーション入れ込み								普通のタイム		1攻撃アニメーション
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount);
}

// 必殺技 (現在不使用)
void MediumBoss::CharacterDeathBlow()
{


}

// キャラクターダメージ
void MediumBoss::CharacterDamage()
{
	// 早くダメージ
	FastDamage();
}

// 色変更
void MediumBoss::SetModelColor()
{
	// 色変更
	if (life == 6)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor, greenColor, blueColor, 1.0f));
	}
	if (life == 5)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.1f, greenColor - 0.1f, blueColor - 0.1f, 1.0f));
	}
	if (life == 4)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.3f, greenColor - 0.3f, blueColor - 0.3f, 1.0f));
	}
	if (life == 3)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.5f, greenColor - 0.5f, blueColor - 0.5f, 1.0f));
	}
	if (life == 2)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.7f, greenColor - 0.7f, blueColor - 0.7f, 1.0f));
	}
	if (life == 1)
	{
		MV1SetDifColorScale(modelHandle, GetColorF(redColor - 0.9f, greenColor - 0.9f, blueColor - 0.9f, 1.0f));
	}

}

// エネミーのセット
void MediumBoss::SetMedium()
{
	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	characterJump.isJump = false;
	characterMove.isMove = false;
	isFinish = false;

	isDamage = false;
	isDeathBlowDamage = false;
	damageCount = 0;
	life = 6;
	isAlive = false;

	isHit = false;
}

// プレイヤーの向きに移動
void MediumBoss::EnemyMove(VECTOR _pos)
{
	characterMove.dir = VSub(_pos, characterMove.pos);
}

// プレイヤーの向きとは反転に移動
void MediumBoss::EnemyMoveSub(VECTOR _pos)
{
	characterMove.dir = VSub(characterMove.pos, _pos);
}

// 更新
void MediumBoss::EnemyUpdate(CharacterBase * _player, Tower *_tower)
{
	/*
	// プレイヤーと中ボスの当たり判定と移動処理
	// 中ボスの体力が0ではなければ
	if (life > 0)
	{

		// 中ボスがプレイヤーに向かうようにする
		if (!HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 5.0f) && HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 8))
		{
			this->EnemyMove(_player->GetPos());
			this->SetMove(true);
		}
		// 中ボスの
		else if (HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 5.0f) && !HitCheck::HitCheckCirclePlayerToMediumBoss(_player, this, 8))
		{
			if (this->GetMove())
			{
				this->ClerDir();
			}
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
	}
	*/

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
