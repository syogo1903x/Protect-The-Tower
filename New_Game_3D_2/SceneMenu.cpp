#include "Common.h"

char *SceneMenu::playerModelHandle = "";
char *SceneMenu::stageModelHandle = "";

SceneMenu::SceneMenu()
{
	for (int i = 0; i < 3; i++)
	{
		if (se[i])
		{
			se[i]->Release();
			se[i] = NULL;
		}
	}
}

SceneMenu::~SceneMenu()
{
	Release();
}

void SceneMenu::Init()
{
	// BGM読み込み
	bgm = new BackGroundMusic("Music/BGM/MenuBGM.mp3");
	// 効果音読み込み
	se[0] = new SoundEffect("Music/SE/cursor10.mp3");
	se[1] = new SoundEffect("Music/SE/cancel2.mp3");
	se[2] = new SoundEffect("Music/SE/decision9.mp3");

	mouseX = SCREEN_X / 2;
	mouseY = SCREEN_Y / 2;
	// マウスの初期座標中心
	SetMousePoint(mouseX, mouseY);

	// 
	graphHandle = LoadGraph("img/menu.png");
	// 
	nowLoadingGaprhHandle = LoadGraph("img/nowloading.png");
	optionGraphHandle = LoadGraph("img/option.png");

	// 
	characterModelHandle[0] = "character/original/右折ちゃん_Gun/ukon.pmx";
	characterModelHandle[1] = "character/original/Ruby_Gun/Ruby.pmx";
	characterModelHandle[2] = "character/original/高科ちなみ_Gun/高科ちなみV4.pmx";
	characterModelHandle[3] = "character/original/MMD用踊る犬_Gun/白茶犬.pmx";
	characterModelHandle[4] = "character/original/MMD用踊るカラス_Gun/MMD用踊るカラス.pmx";

	// 
	stageObjModelHandle[0] = "stage/白玉楼ver0.93/白玉楼.pmx";
	stageObjModelHandle[1] = "stage/ラグビーグラウンド1.05/ラグビーグラウンド（芝生）.pmx";
	stageObjModelHandle[2] = "stage/月の都風弾幕ステージ/月の都風弾幕ステージ.pmx";

	// 
	characterGraphHandle[0] = LoadGraph("img/character/ukon_1.png");
	characterGraphHandle[1] = LoadGraph("img/character/Ruby_1.png");
	characterGraphHandle[2] = LoadGraph("img/character/高橋ちなみ_1.png");
	characterGraphHandle[3] = LoadGraph("img/character/白茶犬_1.png");
	characterGraphHandle[4] = LoadGraph("img/character/カラス_1.png");
	// 
	characterStartGraphHandle[0] = LoadGraph("img/character/ukon_2.png");
	characterStartGraphHandle[1] = LoadGraph("img/character/Ruby_2.png");
	characterStartGraphHandle[2] = LoadGraph("img/character/高橋ちなみ_2.png");
	characterStartGraphHandle[3] = LoadGraph("img/character/白茶犬_2.png");
	characterStartGraphHandle[4] = LoadGraph("img/character/カラス_2.png");

	stageGraphHandle[0] = LoadGraph("img/stage/白玉楼.png");
	stageGraphHandle[1] = LoadGraph("img/stage/芝生.png");
	stageGraphHandle[2] = LoadGraph("img/stage/月の都.png");

	difficultGraphHandle[0] = LoadGraph("img/easy.png");
	difficultGraphHandle[1] = LoadGraph("img/norm.png");
	difficultGraphHandle[2] = LoadGraph("img/hard.png");

	frameGraphHandle[0] = LoadGraph("img/character/frame.png");
	frameGraphHandle[1] = LoadGraph("img/character/frame2.png");
	//
	LoadDivGraph("img/flan.png", 2, 2, 1, 32, 32, moouseGraphHandle, TRUE);
	// 
	startGraphHandle = LoadGraph("img/OK.png");
	// 
	selectGraphHamdle[0] = LoadGraph("img/mouse_left.png");
	selectGraphHamdle[1] = LoadGraph("img/A.png");
	//
	backGraphHandle[0] = LoadGraph("img/mouse_right.png");
	backGraphHandle[1] = LoadGraph("img/B.png");
	//
	selecctMenuGraphHandle[0] = LoadGraph("img/charcterSelect.png");
	selecctMenuGraphHandle[1] = LoadGraph("img/stageSelect.png");
	selecctPushMenuGraphHandle[0] = LoadGraph("img/select.png");
	selecctPushMenuGraphHandle[1] = LoadGraph("img/back.png");

	//
	isPlayerSelect = false;
	isMenuSelect = false;

	playerModelHandle = 0;
	playerNomer = 0;

	stageNomer = 0;

	menuCount = 0;

	for (int i = 0; i < 5; i++)
	{
		isPlayerDecision[i] = false;
		isSoundEffect[i] = false;
	}
	for (int i = 0;i < 3; i++)
	{
		isMenuDecision[i] = false;
	}

	changeCount = 0;
	isChange = false;


	isPush = false;
	pushCount = 0;

	playerSizeUpCount = 0;
	playerSizeUp = 0;
	playerSizeUpBlank = 0;

	menuSizeUp = 0;
	menuSizeUpBlank = 0;
	menuSizeUpCount = 0;

	// フェードイン フェードアウト 初期化
	FADE.Init();

	// BGM再生
	bgm->PlayBackGroundMusic();

	LOAD_FILE.LoadFileData("GameCount.txt");
}

SceneBase * SceneMenu::Update()
{
	GetMousePoint(&mouseX, &mouseY);
	animation++;

	if (menuCount == 0)
	{
		// メニューサイズをリセットする	
		menuSizeUp = 0;
		menuSizeUpBlank = 0;
		menuSizeUpCount = 0;

		// 決定されていないことにする
		isPlayerSelect = false;
		// 右が押されれば
		if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000 && !isPush)
		{
			// リセット
			playerSizeUpBlank = 0;
			playerSizeUp = 0;
			playerSizeUpCount = 0;

			// 選択音再生
			se[0]->PlaySoundEffect();

			// 押したフラグをオン
			isPush = true;
			playerNomer++;
		}

		// 左が押されれば
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000 && !isPush)
		{
			// リセット
			playerSizeUpBlank = 0;
			playerSizeUp = 0;
			playerSizeUpCount = 0;

			// 選択音再生
			se[0]->PlaySoundEffect();

			// 押したフラグをオン
			isPush = true;
			playerNomer--;
		}
	}
	else
	{
		// 決定されていないことにする
		isMenuSelect = false;
		// プレイヤーサイズリセット
		playerSizeUpBlank = 0;
		playerSizeUp = 0;
		playerSizeUpCount = 0;

		// 右が押されれば
		if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000 && !isPush)
		{
			// リセットする	
			menuSizeUp = 0;
			menuSizeUpBlank = 0;
			menuSizeUpCount = 0;

			// 選択音再生
			se[0]->PlaySoundEffect();

			// 押したフラグをオン
			isPush = true;
			stageNomer++;
		}

		// 左が押されれば
		if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000 && !isPush)
		{
			// リセットする	
			menuSizeUp = 0;
			menuSizeUpBlank = 0;
			menuSizeUpCount = 0;

			// 選択音再生
			se[0]->PlaySoundEffect();

			// 押したフラグをオン
			isPush = true;
			stageNomer--;
		}
	}

	// 押され続けないようにする
	if (isPush) { pushCount ++; }
	if (pushCount > 7) { isPush = false; pushCount = 0; }

	// 最大値と最小値を超えない
	if (playerNomer > PLAYER_MAX)
	{
		playerNomer = 0;
	}
	if (playerNomer < 0)
	{
		playerNomer = PLAYER_MAX;
	}


	// 最大値と最小値を超えない
	if (stageNomer > MENU_MAX)
	{
		stageNomer = 0;
	}
	if (stageNomer < 0)
	{
		stageNomer = MENU_MAX;
	}

	//　キャラクター入れ込み
	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		if (playerNomer == i)
		{
			playerModelHandle = characterModelHandle[i];
		}
	}

	//　ステージ入れ込み
	for (int i = 0; i < MENU_COUNT; i++)
	{
		if (stageNomer == i)
		{
			stageModelHandle = stageObjModelHandle[i];
		}
	}

	// キーが押されたら
	if (menuCount == 0)
	{
		for (int i = 0; i < PLAYER_COUNT; i++)
		{
			// 当たり判定
			if ((PLAYER_BLANK + HIT_SIZE * i) - HIT_CHECK < mouseX && (PLAYER_BLANK + HIT_SIZE * i) + HIT_CHECK > mouseX &&
				PLAYER_BLANK_Y - HIT_CHECK < mouseY && PLAYER_BLANK_Y + HIT_CHECK > mouseY)
			{
				// 
				if (!isSoundEffect[i])
				{
					// 選択音再生
					se[0]->PlaySoundEffect();
					isSoundEffect[i] = true;
				}

				isPlayerDecision[i] = true;
				playerNomer = i;
				// マウスが押されれば
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
				{
					// 決定音再生
					se[2]->PlaySoundEffect();

					// カウント変更
					menuCount = 1;
					isPlayerSelect = true;
				}
			}
			else
			{
				isPlayerDecision[i] = false;
				isSoundEffect[i] = false;
			}

			// プレイヤー選択時色変更
			if (playerNomer == i)
			{
				isPlayerDecision[i] = true;
			}
		}

		if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A))
		{
			// 決定音再生
			se[2]->PlaySoundEffect();

			// カウント変更
			menuCount = 1;
			isPlayerSelect = true;
		}

		// プレイヤー選択に戻る
		if (KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B) || MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT))
		{
			// キャンセル音再生
			se[1]->PlaySoundEffect();

			// フェードアウトが完了したかの条件分岐
			FADE.TermsFadeOut_Play("Fast");
		}
	}
	else
	{
		for (int i = 0; i < MENU_COUNT; i++)
		{
			// 当たり判定
			if ((MENU_BLANK + HIT_SIZE * i) - HIT_CHECK < mouseX && (MENU_BLANK + HIT_SIZE * i) + HIT_CHECK > mouseX &&
				MENU_Y + 30 - HIT_CHECK < mouseY && MENU_Y + 30 + HIT_CHECK > mouseY)
			{
				// 
				if (!isSoundEffect[i]) 
				{
					// 選択音再生
					se[0]->PlaySoundEffect();
					isSoundEffect[i] = true;
				}
				// 
				stageNomer = i;
				isMenuDecision[i] = true;
				// マウスが押されれば
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
				{
					// 決定音再生
					se[2]->PlaySoundEffect();

					// 変更フラグのオン
					isChange = true;
					isMenuSelect = true;
				}
			}
			else
			{
				isMenuDecision[i] = false;
				isSoundEffect[i] = false;
			}

			// ステージ選択時色変更
			if (stageNomer == i)
			{
				isMenuDecision[i] = true;
			}
		}

		if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON|| PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A))
		{
			// 決定音再生
			se[2]->PlaySoundEffect();

			// 変更フラグのオン
			isChange = true;
			isMenuSelect = true;
		}

		// プレイヤー選択に戻る
		if (KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B) || MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT))
		{
			// キャンセル音再生
			se[1]->PlaySoundEffect();

			// カウント変更
			menuCount = 0;
		}

	}

	if (isChange)	changeCount++;

	if (changeCount > 4)
	{
		// 解放
		Release();
		// 切り替え
		return new SceneGame;
	}

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

void SceneMenu::Draw()
{
	DrawGraph(0, 0, graphHandle, TRUE);

	if (menuCount == 0)
	{
		DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 2.f, 1.0f, 0.0f, selecctMenuGraphHandle[0], TRUE);
		// 
		playerSizeUpCount++;
		if (playerSizeUpCount > 0 && playerSizeUpCount <= 30) { playerSizeUp += 0.0015f; playerSizeUpBlank += 0.36f; }
		if (playerSizeUpCount > 30 && playerSizeUpCount <= 60) { playerSizeUp -= 0.0015f; playerSizeUpBlank -= 0.36f; }
		if (playerSizeUpCount >= 60) { playerSizeUpCount = 0; }
	}
	else 
	{
		DrawRotaGraphF(SCREEN_X / 2.f, SCREEN_Y / 2.f, 1.0f, 0.0f, selecctMenuGraphHandle[1], TRUE);
		//
		menuSizeUpCount++;
		if (menuSizeUpCount > 0 && menuSizeUpCount <= 30) { menuSizeUp += 0.0015f; menuSizeUpBlank += 0.36f; }
		if (menuSizeUpCount > 30 && menuSizeUpCount <= 60) { menuSizeUp -= 0.0015f; menuSizeUpBlank -= 0.36f; }
		if (menuSizeUpCount >= 60) { menuSizeUpCount = 0; }
	}

	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 0.4f, 0.0, frameGraphHandle[1], TRUE);

		// キャラクター選択
		if (isPlayerDecision[i])
		{
			//DrawBox(90 + 300 * i - (int)playerSizeUpBlank, 150 - (int)playerSizeUpBlank, 310 + 300 * i + (int)playerSizeUpBlank, 350 + (int)playerSizeUpBlank, GetColor(250, 250, 250), TRUE);
			DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 1.0, 0.0, characterStartGraphHandle[i], TRUE);
			// 決定画像
			if (isPlayerSelect) { DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 0.3f, 0.0f, startGraphHandle, TRUE); }
			if (menuCount == 0) { DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 0.48f + playerSizeUp, 0.0, frameGraphHandle[0], TRUE); }
		}
		else
		{
			DrawRotaGraph(PLAYER_BLANK + HIT_SIZE * i, PLAYER_BLANK_Y, 1.0, 0.0, characterGraphHandle[i], TRUE);
		}
	}

	for (int i = 0; i < MENU_COUNT; i++)
	{
		DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y + 30, 0.4f, 0.0, frameGraphHandle[1], TRUE);
		DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y - 110, 1.0, 0.0, difficultGraphHandle[i], TRUE);
		DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y + 30, 1.0, 0.0, stageGraphHandle[i], TRUE);

		// ステージ選択
		if (isMenuDecision[i])
		{
			//DrawBox(390 + 300 * i - (int)menuSizeUpBlank, 580 - (int)menuSizeUpBlank, 610 + 300 * i + (int)menuSizeUpBlank, 780 + (int)menuSizeUpBlank, GetColor(250, 250, 250), TRUE);
			if (isMenuSelect) { DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y, 0.3f + menuSizeUp, 0.0f, startGraphHandle, TRUE); }
			if (menuCount == 1) { DrawRotaGraph(MENU_BLANK + HIT_SIZE * i, MENU_Y + 30, 0.48f + menuSizeUp, 0.0, frameGraphHandle[0], TRUE); }
		}
	}

	//
	DrawRotaGraph(1250, MENU_Y + 30, 0.4f, 0.0, frameGraphHandle[1], TRUE);

	DrawRotaGraph(1170, 635, 0.3f, 0.0f, selectGraphHamdle[0], TRUE);
	DrawRotaGraph(1235, 635, 0.2f, 0.0f, selectGraphHamdle[1], TRUE);
	DrawRotaGraph(1170, 725, 0.3f, 0.0f, backGraphHandle[0], TRUE);
	DrawRotaGraph(1235, 725, 0.2f, 0.0f, backGraphHandle[1], TRUE);

	DrawRotaGraph(1310, 635, 0.7f, 0.0f, selecctPushMenuGraphHandle[0], TRUE);
	DrawRotaGraph(1310, 725, 0.7f, 0.0f, selecctPushMenuGraphHandle[1], TRUE);


	// マウス位置
	DrawRotaGraph(mouseX, mouseY, 1, 0, moouseGraphHandle[animation % 2], TRUE);

	//
	if (isChange)
	{
		DrawGraph(0, 0, nowLoadingGaprhHandle, TRUE);
		DrawGraph(0, -30, optionGraphHandle, TRUE);
	}

	// フェードイン
	FADE.FadeIn_Play();
	// フェードアウト
	FADE.FadeOut_Play();
	//printfDx("%s\n", stageModelHandle);
}

void SceneMenu::Release()
{
	DeleteGraph(graphHandle);
	graphHandle = NULL;

	DeleteGraph(nowLoadingGaprhHandle);
	nowLoadingGaprhHandle = NULL;
	DeleteGraph(optionGraphHandle);
	optionGraphHandle = NULL;
	DeleteGraph(startGraphHandle);
	startGraphHandle = NULL;

	DeleteGraph(moouseGraphHandle[0]);
	moouseGraphHandle[0] = NULL;
	DeleteGraph(moouseGraphHandle[1]);
	moouseGraphHandle[1] = NULL;

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(selectGraphHamdle[i]);
		selectGraphHamdle[i] = NULL;

		DeleteGraph(backGraphHandle[i]);
		backGraphHandle[i] = NULL;

		DeleteGraph(frameGraphHandle[i]);
		frameGraphHandle[i] = NULL;

		DeleteGraph(selecctMenuGraphHandle[i]);
		selecctMenuGraphHandle[i] = NULL;

		DeleteGraph(selecctPushMenuGraphHandle[i]);
		selecctPushMenuGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 3; i++)
	{
		// 
		DeleteGraph(stageGraphHandle[i]);
		stageGraphHandle[i] = NULL;

		// 
		DeleteGraph(difficultGraphHandle[i]);
		difficultGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(characterGraphHandle[i]);
		characterGraphHandle[i] = NULL;
		DeleteGraph(characterStartGraphHandle[i]);
		characterStartGraphHandle[i] = NULL;
	}

	bgm->StopBackGroundMusic();
	bgm->Release();
}
