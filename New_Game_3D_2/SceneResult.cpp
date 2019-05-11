#include "Common.h"

int SceneResult::playerModelHandle;

SceneResult::SceneResult()
{

	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		delete(se);
	}

}

SceneResult::~SceneResult()
{
	Release();
}

void SceneResult::Init()
{

	// 効果音読み込み
	se = new SoundEffect("Music/SE/decision9.mp3");


	// キャラクターの落ちていく画像
	playerGraphHandle[0] = LoadGraph("img/character/ukon_fall.png");
	playerGraphHandle[1] = LoadGraph("img/character/Ruby_fall.png");
	playerGraphHandle[2] = LoadGraph("img/character/ちなみ_fall.png");
	playerGraphHandle[3] = LoadGraph("img/character/白茶犬_fall.png");
	playerGraphHandle[4] = LoadGraph("img/character/カラス_fall.png");

	// キャラクターの倒れた画像
	playerLandingGraphHandle[0] = LoadGraph("img/character/ukon_die.png");
	playerLandingGraphHandle[1] = LoadGraph("img/character/Ruby_die.png");
	playerLandingGraphHandle[2] = LoadGraph("img/character/ちなみ_die.png");
	playerLandingGraphHandle[3] = LoadGraph("img/character/白茶犬_die.png");
	playerLandingGraphHandle[4] = LoadGraph("img/character/カラス_die.png");

	// ボタン画像
	resultPushGraphHandle[0] = LoadGraph("img/push2.png");
	resultPushGraphHandle[1] = LoadGraph("img/push.png");


	// アニメーションをアタッチ
	animAttachIndex = MV1AttachAnim(playerModelHandle, 6, -1, FALSE);

	// 勝利時
	if (SceneGame::GetResult() == "WIN")
	{
		// プレイヤー画像の削除
		playerFallGraphHandle = NULL;
		// 背景を勝利画面に
		resultGraphHandle = LoadGraph("img/clear.jpg");
		// 勝利画像
		resultWinOrLoseGraphHandle = LoadGraph("img/win.png");
		// BGM読み込み
		bgm = new BackGroundMusic("Music/BGM/winBGM.mp3");
	}
	// 敗北時
	else
	{
		// 背景を敗北画面に
		resultGraphHandle = LoadGraph("img/lose.png");
		// 敗北画面
		resultWinOrLoseGraphHandle = LoadGraph("img/lose_.png");

		// 敗北時のプレイヤー情報取得しプレイヤー画像の入れ込み
		if (SceneMenu::GetPlayer() == "character/original/右折ちゃん_Gun/ukon.pmx") { playerFallGraphHandle = playerGraphHandle[0]; playerLandGraphHandle = playerLandingGraphHandle[0]; }
		if (SceneMenu::GetPlayer() == "character/original/Ruby_Gun/Ruby.pmx") { playerFallGraphHandle = playerGraphHandle[1]; playerLandGraphHandle = playerLandingGraphHandle[1]; }
		if (SceneMenu::GetPlayer() == "character/original/高科ちなみ_Gun/高科ちなみV4.pmx") { playerFallGraphHandle = playerGraphHandle[2]; playerLandGraphHandle = playerLandingGraphHandle[2]; }
		if (SceneMenu::GetPlayer() == "character/original/MMD用踊る犬_Gun/白茶犬.pmx") { playerFallGraphHandle = playerGraphHandle[3]; playerLandGraphHandle = playerLandingGraphHandle[3]; }
		if (SceneMenu::GetPlayer() == "character/original/MMD用踊るカラス_Gun/MMD用踊るカラス.pmx") { playerFallGraphHandle = playerGraphHandle[4]; playerLandGraphHandle = playerLandingGraphHandle[4]; }

		// BGM読み込み
		bgm = new BackGroundMusic("Music/BGM/loseBGM.mp3");
	}

	bound = 0;
	boundCount = 0;
	isFall = true;
	pos = VGet(SCREEN_X / 2, -400, 0);
	count = 0;


	// カメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(50, 15, 50), VGet(-50, 0, -50));

	// フェードイン フェードアウト 初期化
	FADE.Init();

	// BGM再生
	bgm->PlayBackGroundMusic();
}

SceneBase * SceneResult::Update()
{
	//
	count++;
	// 敗北時のバウンド
	pos.y += 50;

	if (pos.y > SCREEN_Y - 140)
	{
		boundCount++;
		pos.y = SCREEN_Y - 140;
	}

	if (boundCount > 10)
	{
		isFall = false;
		boundCount = 10;
	}

	bound = ((sinf(DX_PI_F / 2 * boundCount) * 20));

	MV1SetRotationXYZ(playerModelHandle, VGet(0, -2.14f, 0));
	MV1SetPosition(playerModelHandle, VGet(20, 0, 30));

	// アニメーション入れ込み
	MV1SetAttachAnimTime(playerModelHandle, animAttachIndex, count);


	// キーが押されれば
	if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
	{
		// 効果音再生
		se->PlaySoundEffect();

		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");
	}

	// カウントが規定値を超えたら　フェードアウト
	if (count == 600) { se->PlaySoundEffect(); }
	if (count >= 600) { FADE.TermsFadeOut_Play("Fast"); }

	// フェードアウトが終われば変更
	if (FADE.FadeOutEnd())
	{
		// 解放
		Release();
		// 切り替え
		return new SceneTitle;
	}


	// エスケープが押されれば終了
	if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON)
	{
		SceneChange::SetEscape(true);
	}

	return this;
}

void SceneResult::Draw()
{
	// 勝利時
	if (SceneGame::GetResult() == "WIN")
	{
		STAGE.Draw();								// ステージ描画
		MV1DrawModel(playerModelHandle);			// プレイヤー表示

		// パッドの時
		if (SceneChange::GetPadOrKey())
		{
			DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.2f, 1.f, 0.0f, resultPushGraphHandle[0], TRUE);
		}
		// キーの時
		else
		{
			DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.2f, 1.f, 0.0f, resultPushGraphHandle[1], TRUE);
		}

		// 勝利
		DrawRotaGraphF(SCREEN_X / 3.f, SCREEN_Y / 2.f, 0.6f, 0.0f, resultWinOrLoseGraphHandle, TRUE);
	}
	// 敗北時
	else
	{
		DrawGraph(0, 0, resultGraphHandle, TRUE);

		// 落下状態
		if (isFall)
		{
			DrawRotaGraphF(pos.x, pos.y + bound, 1.0f, 0.0f, playerFallGraphHandle, TRUE);
		}
		else
		{
			// パッドの時
			if (SceneChange::GetPadOrKey())
			{
				DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.9f, 1.f, 0.0f, resultPushGraphHandle[0], TRUE);
			}
			// キーの時
			else
			{
				DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 1.9f, 1.f, 0.0f, resultPushGraphHandle[1], TRUE);
			}

			DrawRotaGraphF(pos.x, pos.y + bound / 2, 1.0f, 0.0f, playerLandGraphHandle, TRUE);

			// 敗北
			DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 2.f, 1.0f, 0.0f, resultWinOrLoseGraphHandle, TRUE);
		}
	}

	// フェードイン
	FADE.FadeIn_Play();
	// フェードアウト
	FADE.FadeOut_Play();
}

// 解放
void SceneResult::Release()
{
	// 削除
	DeleteGraph(graphHandle);
	graphHandle = NULL;

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(resultPushGraphHandle[i]);
		resultPushGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(playerGraphHandle[i]);
		playerGraphHandle[i] = NULL;
		DeleteGraph(playerLandingGraphHandle[i]);
		playerLandingGraphHandle[i] = NULL;
	}

	DeleteGraph(playerFallGraphHandle);
	playerFallGraphHandle = NULL;
	DeleteGraph(playerLandGraphHandle);
	playerLandGraphHandle = NULL;
	DeleteGraph(resultGraphHandle);
	resultGraphHandle = NULL;
	DeleteGraph(resultWinOrLoseGraphHandle);
	resultWinOrLoseGraphHandle = NULL;

	if (bgm)
	{
		bgm->StopBackGroundMusic();
		bgm->Release();
		delete(bgm);
		bgm = NULL;
	}

	// ステージ削除
	STAGE.Release();


	// モデル削除
	MV1DeleteModel(playerModelHandle);
	playerModelHandle = NULL;
}

void SceneResult::CreateModel()
{
	playerModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::PLAYER));

	if (playerModelHandle < 0) { printfDx("モデルエラー\n"); }
}
