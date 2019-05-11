#include "CharacterBase.h"
#include "SceneGame.h"

// アニメーション初期化
void CharacterBase::AnimationInit()
{
	// アニメーションをアタッチ
	animAttachIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);

	// 走りアニメーションの総時間を取得しておく
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, animAttachIndex);

	// アニメーション再生時間を初期化
	playTime = 20.0f;
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime);

	// アニメーションで移動をしているフレームの番号を検索する
	moveAnimFrameIndex = MV1SearchFrame(modelHandle, "センター");

	// アニメーションで移動をしているフレームを無効にする
	MV1SetFrameUserLocalMatrix(modelHandle, moveAnimFrameIndex, MGetIdent());

	money = 0;
	playTime = 0;
	isHit = false;
	// 音のセット
	hitDamegeSe = new SoundEffect("Music/SE/damage3.mp3");
	loseDamegeSe = new SoundEffect("Music/SE/damage7.mp3");
}

// 更新
void CharacterBase::Update(Camera & _camera)
{
	// アニメーション
	Animation();
	// 移動
	CharacterMove(_camera);

	// ゲームが始まれば操作可能
	if (SceneGame::GetStart())
	{
		// ジャンプ
		CharacterJump();
		// 攻撃
		CharacterAtack();
		// 必殺技
		CharacterDeathBlow();
	}

	// キャラのダメージ
	CharacterDamage();
}

// 描画 
void CharacterBase::Draw()
{
	if (!isFinish)
	{
		MV1DrawModel(modelHandle);
		//VECTOR StringPos = ConvWorldPosToScreenPos(characterMove.pos);
		//DrawFormatString(StringPos.x, StringPos.y, GetColor(255, 0, 0), "Life : %d", life);
	}
}

// 解放
void CharacterBase::Release()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	hitDamegeSe->Release();
	loseDamegeSe->Release();
}

// 素早いダメージ
void CharacterBase::FastDamage()
{
	float alha;

	//  必殺技のダメージを喰らえば
	if (isDeathBlowDamage)
	{
		damageCount++;

		if (damageCount > 10)
		{
			damageCount = 0;
			isDeathBlowDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 10;
		}
	}
	// 通常のダメージを喰らえば
	else if (isDamage)
	{
		damageCount++;

		if (damageCount > 4)
		{
			damageCount = 0;
			isDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 1;
		}
	}

	// ヒット音
	if (life > 0)
	{
		if (damageCount == 1)
		{
			hitDamegeSe->PlaySoundEffect();
		}
	}
	// 死亡音
	if (life <= 0)
	{
		if (damageCount == 1)
		{
			loseDamegeSe->PlaySoundEffect();
		}
	}

	if (damageCount % 2 == 0)
	{
		alha = 1.0f;
	}
	else
	{
		alha = 0.5f;
	}

	MV1SetOpacityRate(modelHandle, alha);
}

// 遅いダメージ
void CharacterBase::SlowDamage()
{
	float alha;

	//  必殺技のダメージを喰らえば
	if (isDeathBlowDamage)
	{
		damageCount++;

		if (damageCount > 60)
		{
			damageCount = 0;
			isDeathBlowDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 10;
		}
	}
	// 通常のダメージを喰らえば
	else if (isDamage)
	{
		damageCount++;

		if (damageCount > 30)
		{
			damageCount = 0;
			isDamage = false;
		}

		if (damageCount == 1)
		{
			life -= 1;
		}
	}

	// 体力が0ではないとき音を出す
	if (life > 0)
	{
		if (damageCount == 1)
		{
			hitDamegeSe->PlaySoundEffect();
		}
	}
	// 体力が0以下の時音を出す
	if (life <= 0)
	{
		if (damageCount == 1)
		{
			loseDamegeSe->PlaySoundEffect();
		}
	}

	// 点滅させる
	if (damageCount % 2 == 0)
	{
		alha = 1.0f;
	}
	else
	{
		alha = 0.5f;
	}
	
	// 透明度変更
	MV1SetOpacityRate(modelHandle, alha);
}

// 円の当たり判定処理
void CharacterBase::OnHit(CharacterBase * _player)
{
	// 自分自身の位置を障害物のあたり判定分ずらす.
	// Z軸とX軸の二次元座標として位置ずらしを行う.
	VECTOR yZeroPlayer = characterMove.pos;
	VECTOR yZeroOtherPlayer = _player->GetPos();

	VECTOR otherPlaterToPlayer = VSub(yZeroPlayer, yZeroOtherPlayer);

	// ぶつかったときに離す距離。ちょうどだとfloat誤差で重なり続けるので少し間をあける.
	float awayRange = (radius + _player->GetRadius() + 0.01f);

	VECTOR awayVec = VScale(VNorm(otherPlaterToPlayer), awayRange);
	characterMove.pos = VAdd(yZeroOtherPlayer, awayVec);

	// ぶつかったら減速する.
	characterMove.dir = VScale(characterMove.dir, 0.4f);
}

// ダメージで下がる処理
void CharacterBase::FlutterCharacter()
{
	// 移動更新
	characterMove.pos = VAdd(characterMove.pos, VScale(VGet(0, 0, -1), 10));
}
