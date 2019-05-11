#include "Common.h"

VECTOR Player::playerTargetPos;
float Player::playerTragetCameraPos;
int Player::characterCount;

// コンストラクタ
Player::Player()
{


}

// デストラクタ
Player::~Player()
{
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	for (int i = 0; i < 4; i++)
	{
		if (se[i])
		{
			se[i]->StopSoundEffect();
			se[i]->Release();
			se[i] = NULL;
			delete(se[i]);
		}
	}
}

// 初期化
void Player::Init(char *_playerNumber)
{
	modelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::PLAYER));

	if (modelHandle < 0)
	{
		printfDx("error");
	}

	// アニメーションの初期化
	AnimationInit();

	// ジャンプの重力
	jumpGravity = 1.0f;
	// 体力
	life = PLAYER_LIFE_MAX;
	// 半径
	radius = 5.0f;

	// 攻撃処理フラグ
	characterAtack.isAtack = false;
	characterAtack.atackCount = 0;

	// 効果音読み込み
	se[SETUP] = new SoundEffect("Music/SE/set.mp3");
	se[JUMP] = new SoundEffect("Music/SE/knife-throw1.mp3");
	se[USE_DEATH_BLOW] = new SoundEffect("Music/SE/ko.mp3");
	se[DEATH_BLOW_START] = new SoundEffect("Music/SE/cannon2.mp3");

	// キャラクターごとのサイズ変換
	if (_playerNumber == "character/original/MMD用踊る犬_Gun/白茶犬.pmx" || _playerNumber == "character/original/MMD用踊るカラス_Gun/MMD用踊るカラス.pmx")
	{
		MV1SetScale(modelHandle, VGet(1.2f, 1.2f, 1.2f));
		charaScale = 0.7f;
	}
	else
	{
		charaScale = 1.0f;
	}

	// 各プレイヤーの時の各状況の取得
	if (_playerNumber == "character/original/右折ちゃん_Gun/ukon.pmx")					{ playerTragetCameraPos = 10.0f; characterCount = 0;}
	if (_playerNumber == "character/original/Ruby_Gun/Ruby.pmx")						{ playerTragetCameraPos = 14.0f; characterCount = 1;}
	if (_playerNumber == "character/original/高科ちなみ_Gun/高科ちなみV4.pmx")			{ playerTragetCameraPos = 11.0f; characterCount = 2;}
	if (_playerNumber == "character/original/MMD用踊る犬_Gun/白茶犬.pmx")				{ playerTragetCameraPos = 16.0f; characterCount = 3;}
	if (_playerNumber == "character/original/MMD用踊るカラス_Gun/MMD用踊るカラス.pmx")	{ playerTragetCameraPos = 13.0f; characterCount = 4;}

	// フラグ
	characterJump.isJump = false;

	characterMove.isMove = false;
	characterMove.pos = PLAYER_INIT_POS;
	characterMove.dir = ZEROCLEAR;
	characterMove.angle = ZEROCLEAR;
	isDamage = false;
	isDeathBlowDamage = false;
	isFinish = false;

	// ダメージカウント
	damageCount = 0;
	
	// 必殺技
	characterAtack.isDeathBlow = false;
	characterAtack.isUseDeathBlow = false;
	characterAtack.deathBlowCount = 0; 
	characterAtack.deathBlowAnimationCount = 0;
	characterAtack.isNowDeathBlow = false;

	deathBlowAnimationCount = 0;
	tmpDirection = ZEROCLEAR;
	
	// 銃の弾処理
	shot = new Shot;
	shot->CreateShot(50);
}

void Player::Init(int model)
{
	// ~特になし
}

// 移動処理
void Player::CharacterMove(Camera &_camera)
{
	// 重力追加
	characterMove.pos.y -= jumpGravity;
	// 向きを常に初期化
	characterMove.dir = ZEROCLEAR;
	// 体力の上限
	if (life >= PLAYER_LIFE_MAX) { life = PLAYER_LIFE_MAX; }

	// プレイヤー移動処理
	PlayerMoveProcess();
	// プレイヤーの移動更新
	PlayerMoveUpdate(_camera);
	// プレイヤーの回転
	PlayerRotation(_camera);
	// プレイヤーを範囲外に出さない
	PlayerOutOfRangeWall();

	// ポジション更新
	MV1SetPosition(modelHandle, characterMove.pos);
}

// ジャンプ処理
void Player::CharacterJump()
{
	// ゲームクリアしていなければまたはゲームオ－バーではなければ
	if (!SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// 必殺技を放っていなければ
		if (!characterAtack.isUseDeathBlow)
		{
			// ジャンプ
			if (KEY_INPUT.GetKey(KEY_INPUT_SPACE) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A))
			{
				if (!characterJump.isJump) se[JUMP]->PlaySoundEffect();
				characterJump.isJump = true;
			}

			// ジャンプ中
			if (characterJump.isJump)
			{
				characterJump.jumpCount++;
				characterMove.pos.y += JUMP_POWER;
			}
			// 常に重力
			jumpGravity += JUMP_GRAVITY_ACCEL;
		}
	}
}

// 攻撃処理
void Player::CharacterAtack()
{
	// 銃の弾の位置の取得
	VECTOR tmpBulPos = VNorm(VSub(playerTargetPos, Camera::GetCamPos()));
	VECTOR playerAimPos = VGet(tmpBulPos.x, (characterMove.angle.x) / 1.5f , tmpBulPos.z);
	// 銃の弾を発射出す状態
	shot->BulletShot(playerAimPos, characterMove.pos);

	// ゲームクリアしていなければまたはゲームオ－バーではなければ
	if (!SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// ジャンプしていなければ攻撃可能
		if (!characterJump.isJump && !characterAtack.isUseDeathBlow)
		{
			// マウスの右が押された
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_LEFT_SHOULDER))
			{
				se[SETUP]->PlaySoundEffect();
			}
			// マウスの右が押されている
			if (MOUSE_INPUT.MousePresed(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPressed("1P", XINPUT_BUTTON_LEFT_SHOULDER))
			{
				// 攻撃状態
				characterAtack.isAtack = true;
				// マウスの左が押された瞬間
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_RIGHT_SHOULDER))
				{
					//
					shot->OneBulletPlay();
				}
				// マウスの左が押されてる間
				if (MOUSE_INPUT.MousePresed(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPressed("1P", XINPUT_BUTTON_RIGHT_SHOULDER))
				{
					// 
					shot->BulletPlay();
				}
			}
			else
			{
				characterAtack.isAtack = false;
			}
		}
	}

	// 銃の弾を見せる
	shot->Draw();
}


// ひっさつわざ
void Player::CharacterDeathBlow()
{
	// 必殺技カウントを取り
	characterAtack.deathBlowCount += 0.1f;

	// 必殺技カウントが規定値を超えれば 必殺技可能状態
	if (characterAtack.deathBlowCount > DEATHBLOW_COUNT)
	{
		// ゲージ効果音再生
		se[USE_DEATH_BLOW]->OnePlaySoundEffect();

		characterAtack.isDeathBlow = true;
		characterAtack.isUseDeathBlow = false;
		characterAtack.deathBlowCount = DEATHBLOW_COUNT;
	}

	// デバック用 必殺技ゲージ溜め
	if (CheckHitKey(KEY_INPUT_1)) {characterAtack.deathBlowCount = DEATHBLOW_COUNT ;}

	// ゲームクリアしていなければまたはゲームオ－バーではなければ
	if (!SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// 必殺技可能状態の時
		if (characterAtack.isDeathBlow && !characterJump.isJump)
		{
			// 必殺技が使得る状態であれば
			if (!characterAtack.isUseDeathBlow)
			{
				// 使われれば
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_MIDDLE) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_X))
				{
					// ゲージ効果音停止
					se[USE_DEATH_BLOW]->StopSoundEffect();
					// 必殺技効果音再生
					se[DEATH_BLOW_START]->OnePlaySoundEffect();

					// アニメーションを必殺技にする
					characterAtack.isDeathBlow = false;
					characterAtack.deathBlowCount = 0;
					deathBlowAnimationCount = 0;
					characterAtack.isUseDeathBlow = true;
					characterAtack.isNowDeathBlow = true;
				}
			}
		}
	}

	// 必殺技ののけぞりアニメーションカウント
	if (characterAtack.deathBlowAnimationCount > 0 && characterAtack.deathBlowAnimationCount <= USE_DEATHBLOW_COUNT / 2)
	{
		deathBlowAnimationCount ++;
	}

	if (characterAtack.deathBlowAnimationCount > USE_DEATHBLOW_COUNT / 2 && characterAtack.deathBlowAnimationCount <= USE_DEATHBLOW_COUNT)
	{
		deathBlowAnimationCount --;
	}

	// カメラが一回転したらカメラが回らないようにするために必殺技をやめたことにする
	if (characterAtack.isUseDeathBlow)
	{
		if (characterAtack.deathBlowAnimationCount > USE_DEATHBLOW_COUNT)
		{
			// 必殺技効果音停止
			se[DEATH_BLOW_START]->StopSoundEffect();
			// 必殺技使用可能フラグをオフ
			characterAtack.isUseDeathBlow = false;
		}
	}

	// 必殺技が一定を超えれば 使える状態にする
	if (characterAtack.deathBlowCount > NOW_USE_DEATHBLOW_COUNT)
	{
		characterAtack.isNowDeathBlow = false;
	}
}

// アニメーション
void Player::Animation()
{

	// プレイヤーのエフェクト
	EFFECT.UpdatePlayer(this);

	// アニメーションフレーム最大処理
	AnimationMaxFrame();
	// アニメーション設定
	AninmationConfiguration();
	// アニメーション変更
	AnimationConfigurationChange();

	// アニメーション入れ込み							普通のタイム			構え
	MV1SetAttachAnimTime(modelHandle, animAttachIndex, playTime + characterAtack.atackCount + deathBlowAnimationCount);
}

// キャラクターダメージ
void Player::CharacterDamage()
{
	// ゆっくりダメージ
	SlowDamage();
}

// カメラの向きを計算
VECTOR Player::PlayerMoveDir(VECTOR _pos, Camera &_camera)
{
	VECTOR tmpPos;
	float sinPram = sinf(_camera.GetRad());
	float cosPram = cosf(_camera.GetRad());

	tmpPos.x =  _pos.z * sinPram - _pos.x * cosPram;
	tmpPos.y = 0;
	tmpPos.z = _pos.x * sinPram + _pos.z * cosPram;

	return tmpPos;
}

void Player::PlayerMoveProcess()
{
	// ゲームが始まっててかつゲームクリアしていなければまたはゲームオ－バーではなければ
	if (SceneGame::GetStart() && !SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// 左移動
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
		{
			characterMove.dir.x = -1;
		}
		// 右移動
		if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
		{
			characterMove.dir.x = 1;
		}
		// うしろいどう
		if (KEY_INPUT.GetKey(KEY_INPUT_S) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000)
		{
			characterMove.dir.z = 1;
		}
		// 前移動
		if (KEY_INPUT.GetKey(KEY_INPUT_W) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000)
		{
			characterMove.dir.z = -1;
		}
	}
}

// プレイヤーの移動更新
void Player::PlayerMoveUpdate(Camera &_camera)
{
	// 正規化
	if (VSquareSize(characterMove.dir) != 0)
	{
		characterMove.dir = VNorm(characterMove.dir);
	}

	// 必殺技をしていなければ移動可能
	if (!characterAtack.isUseDeathBlow)
	{
		// ベロシティ
		velocity = VScale(characterMove.dir, PLAYER_SPEED);

		// 移動更新
		characterMove.pos = VAdd(characterMove.pos, PlayerMoveDir(velocity, _camera));
	}
	else
	{
		if (characterAtack.deathBlowAnimationCount > 0 && characterAtack.deathBlowAnimationCount <= USE_DEATHBLOW_COUNT / 2)
		{
			// ベロシティ
			velocity = VScale(VGet(0, 0, 1), PLAYER_SPEED / 4);

			// 移動更新
			characterMove.pos = VAdd(characterMove.pos, PlayerMoveDir(velocity, _camera));
		}
	}

	// 攻撃可能状態であれば カメラを近づける
	if (characterAtack.isAtack)
	{
		playerTargetPos = VAdd(characterMove.pos, VScale(PlayerMoveDir(VGet(-1, 0, 0), _camera), PLAYER_CAMERA_MAX));
	}
	else
	{
		// カメラが見るプレイヤーの先のポジション
		playerTargetPos = characterMove.pos;
	}

	// カメラの向きに移動
	if (SceneGame::GetGameClear())
	{
		// 向きを常に初期化
		characterMove.dir = ZEROCLEAR;

		characterMove.dir = PlayerMoveDir(characterMove.dir, _camera);
	}
	else if (characterMove.isMove && !characterAtack.isAtack)
	{
		characterMove.dir = PlayerMoveDir(characterMove.dir, _camera);
	}
	// 攻撃中であれば構える
	else if (characterAtack.isAtack)
	{
		characterMove.dir = PlayerMoveDir(VSub(ZEROCLEAR, VNorm(_camera.GetDir())), _camera);
	}
	// 動いていない場合はカメラの向こう側を見続ける
	else
	{
		characterMove.dir = PlayerMoveDir(VSub(characterMove.dir, VNorm(_camera.GetDir())), _camera);
	}
}

// プレイヤーの回転
void Player::PlayerRotation(Camera &_camera)
{
	// 上下回転用
	camDir = VSub(_camera.GetDir(), characterMove.dir);
	// 向き変更
	cameraAngle = vec2Radian(&VGet(0, -1, 0), &camDir);

	// 攻撃をしていなければ向き更新
	if (!characterAtack.isUseDeathBlow && !characterAtack.isAtack || SceneGame::GetGameClear())
	{
		// 向き変更
		aimAngle = vec2Radian(&VGet(0, 0, -1), &characterMove.dir);

		// 左右の回転
		characterMove.angle.y = lerpRadian(characterMove.angle.y, aimAngle, PLAYER_MOVE_TURN);

		// 上下の回転をなくす
		characterMove.angle.x = lerpRadian(characterMove.angle.x, 0, 1.f);
	}
	// 攻撃中であればモデルの回転を上下と左右にする
	else if (!characterAtack.isUseDeathBlow && characterAtack.isAtack)
	{
		// カメラの方向を向く
		VECTOR camtraget = VNorm(VSub(characterMove.pos, Camera::GetCamPos()));
		float camtragetY = atan2(camtraget.x, camtraget.z);

		// 左右の回転
		characterMove.angle.y = lerpRadian(characterMove.angle.y, (camtragetY + PI / 1.3f) /*+ playerHorizontal*/, PLAYER_ATACK_TURN);

		// 上下の回転
		characterMove.angle.x = lerpRadian(characterMove.angle.x, (cameraAngle - PI / 2.f), PLAYER_ATACK_TURN);
	}

	// 回転更新　かつゲームが始まっていれば
	if (SceneGame::GetStart())
	{
		MV1SetRotationXYZ(modelHandle, characterMove.angle);
	}
}

// プレイヤーを範囲外に出さない
void Player::PlayerOutOfRangeWall()
{
	// 上限下限
	if (characterMove.pos.x >= 310) { characterMove.pos.x = 310; }
	if (characterMove.pos.x <= -310) { characterMove.pos.x = -310; }

	if (characterMove.pos.z >= 250) { characterMove.pos.z = 250; }
	if (characterMove.pos.z <= -420) { characterMove.pos.z = -420; }

	// キャラクターが近づいたら範囲外に出さない壁を出す
	if (characterMove.pos.x >= 250) { Stage::SetDangerTrans(0, 0.05f); }
	else { Stage::SetDangerTrans(0, -0.05f); }
	if (characterMove.pos.x <= -250) { Stage::SetDangerTrans(2, 0.05f); }
	else { Stage::SetDangerTrans(2, -0.05f); }

	if (characterMove.pos.z >= 200) { Stage::SetDangerTrans(1, 0.05f); }
	else { Stage::SetDangerTrans(1, -0.05f); }
	if (characterMove.pos.z <= -350) { Stage::SetDangerTrans(3, 0.05f); }
	else { Stage::SetDangerTrans(3, -0.05f); }

	// 範囲外出たときに
	if (characterMove.pos.y <= -50) { characterMove.pos = PLAYER_INIT_POS; }
}


// アニメーションフレーム最大処理
void Player::AnimationMaxFrame()
{
	// 各アニメーションの最大フレーム設定
	if (SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		characterAtack.deathBlowAnimationCount = 0;
		deathBlowAnimationCount = 0;
	}
	else if (characterAtack.isUseDeathBlow)		// 必殺技
	{
		characterAtack.deathBlowAnimationCount++;
		playTime = 0;
		characterAtack.atackCount = 0;
	}
	else if (characterJump.isJump)					// ジャンプ
	{
		playTime = totalTime / 2;
		characterAtack.isAtack = false;
		characterAtack.atackCount = 0;
		characterAtack.deathBlowAnimationCount = 0;
	}
	else if (characterAtack.isAtack)			// 攻撃一回目
	{
		playTime = 0;
	}
	else if (characterMove.isMove)				// 動いているとき
	{
		characterAtack.deathBlowAnimationCount = 0;
		deathBlowAnimationCount = 0;

		if (playTime >= totalTime)
		{
			playTime -= totalTime;
		}
	}
	else										// 待機
	{
		characterAtack.deathBlowAnimationCount = 0;
		deathBlowAnimationCount = 0;
		if (playTime >= totalTime)
		{
			playTime = 6;
		}
	}
}

// アニメーション設定
void Player::AninmationConfiguration()
{
	// ゲームクリアしていなければまたはゲームオ－バーではなければ
	if (SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// 移動アニメーションの変更
		totalTime = AnimationChange(playAnim, ANIMATION_WIN, modelHandle, animAttachIndex, totalTime);
		//
		playTime++;
	}
	else if (characterAtack.isUseDeathBlow && !characterJump.isJump)
	{
		// 攻撃アニメーションの変更
		totalTime = AnimationChange(playAnim, ANIMATION_DEATHBLOW, modelHandle, animAttachIndex, totalTime);
	}
	// ジャンプ時
	else if (characterJump.isJump)
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
}

// アニメーション変更
void Player::AnimationConfigurationChange()
{
	// ゲームが始まっててかつゲームクリアしていなければまたはゲームオ－バーではなければ
	if (SceneGame::GetStart() && !SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		// アニメーション
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else if (KEY_INPUT.GetKey(KEY_INPUT_S) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else if (KEY_INPUT.GetKey(KEY_INPUT_W) == KEY_PRESSED || PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000)
		{
			characterMove.isMove = true;
			playTime++;
		}
		else
		{
			characterMove.isMove = false;
		}
	}
}
