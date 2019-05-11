#include "Common.h"

char *SceneGame::result;		// リザルトの勝敗
bool SceneGame::isStart;		// スタート開始フラグ
int SceneGame::gameTime;		// ゲーム時間
bool SceneGame::isGameClear;	// ゲームクリア
bool SceneGame::isGameOver;		// ゲームオーバー

SceneGame::SceneGame()
{
	// マルチスレッド
	nowLoading = new NowLoad();
	// ローディングを作成
	//nowLoading->CreateSubThread();
	// ローディングをせず作成
	nowLoading->SubThreadUpdate();

	// リザルト用モデルの格納
	SceneResult::CreateModel();
}

SceneGame::~SceneGame()
{
	//Release();
}

void SceneGame::Init()
{
	// ステージ初期化
	STAGE.Init(SceneMenu::GetStage());

	// プレイヤー初期化
	player = new Player();
	player->Init(SceneMenu::GetPlayer());

	// カメラ初期化
	camera = new Camera();
	camera->Init();

	// エネミー初期化
	enemy = new EnemyManager();
	enemy->CreateEnemy();

	// アイテムマネージャー初期化
	itemManager = new ItemManager();
	itemManager->Init();

	// ユーザーインターフェーズ初期化
	ui = new UI();
	ui->Init(SceneMenu::GetPlayer());

	// タワー初期化
	tower = new Tower();
	tower->Init();

	// ディフェンスマネージャ初期化
	defenseManager = new DefenseManager;
	defenseManager->Init();

	// ミニマップ初期化
	miniMap = new MiniMap();
	miniMap->Init();

	// BGM読み込み
	bgm = new BackGroundMusic("Music/BGM/gameBGM.mp3");
	shopBGM = new BackGroundMusic("Music/BGM/shopBGM.mp3");

	// 効果音読み込み
	se[0] = new SoundEffect("Music/SE/decision2.mp3");
	se[1] = new SoundEffect("Music/SE/decision2.mp3");
	se[2] = new SoundEffect("Music/SE/decision2.mp3");
	se[3] = new SoundEffect("Music/SE/roll-finish1.mp3");
	menuSe[0] = new SoundEffect("Music/SE/cursor10.mp3");
	menuSe[1] = new SoundEffect("Music/SE/cancel2.mp3");
	menuSe[2] = new SoundEffect("Music/SE/decision9.mp3");
	menuSe[3] = new SoundEffect("Music/SE/knife-throw1.mp3");

	result = "";

	startCount = 3;

	// 説明画像
	descriptionGraphHandle[0] = LoadGraph("img/Description_1.png");
	descriptionGraphHandle[1] = LoadGraph("img/Description_2.png");

	// ウェーブとタイマー
	waveGraphHandle = LoadGraph("img/weav.png");
	timeGraphHandle = LoadGraph("img/time.png");

	// お金の数字とスタート画像
	moneyCountGraphHandle = LoadGraph("img/money_.png");
	gameStartGraphHandle  = LoadGraph("img/gameStart.png");
	// 数字
	LoadDivGraph("img/number.png", 10, 10, 1, 64, 64, numberGraphHandle, TRUE);
	// カウントダウン
	timeCountGraphHandle[0] = LoadGraph("img/1.png");
	timeCountGraphHandle[1] = LoadGraph("img/2.png");
	timeCountGraphHandle[2] = LoadGraph("img/3.png");
	// 画像
	menuGraphHandle = LoadGraph("img/gameMenu.png");
	menuFrameGraphHandle = LoadGraph("img/frame_.png");
	// 説明画像
	descriptionOperationGraphHandle[0] = LoadGraph("img/Description_1_.png");
	descriptionOperationGraphHandle[1] = LoadGraph("img/Description_2_.png");
	descriptionRuleGraphHandle[0] = LoadGraph("img/Description_3_.png");
	descriptionRuleGraphHandle[1] = LoadGraph("img/Description_4_.png");
	
	descriptionTimeCount = 0;
	isDescription = false;
	isOptionDescription = false;

	// フェードイン フェードアウト 初期化
	FADE.Init();

	// BGN再生
	bgm->PlayBackGroundMusic();

	gameStartCount = 0;
	isStart = false;

	gameCount = 0;
	gameTime = 0;

	gameTimeCount = 0;
	isGameClear = false;
	isGameOver = false;
	isGameMenu = false;
	menuCount = 0;

	menuY = 260;

	isDescriptionOperation = false;
	isDescriptionRule = false;

	descriptionRuleCount = 0;
	descriptionOperationCount = 0;

	menuSizeUp = 0;
	menuSizeCount = 0;

	isPush = false;
	pushingCount = 0;
	isMenuPush = false;
	menuPushingCount = 0;
}

// シーンゲーム更新
SceneBase * SceneGame::Update()
{
	// ゲームが始まって
	if (isStart)
	{
		// メニューが押されたら
		if (!isGameMenu)
		{
			// エスケープかパッドのスタートボタンが押されたら表示
			if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_START))
			{
				isGameMenu = true;
				menuSe[2]->PlaySoundEffect();
			}
			// 初期化
			menuCount = 0;
			descriptionRuleCount = 0;
			descriptionOperationCount = 0;
			isDescriptionOperation = false;
			isDescriptionRule = false;
			menuY = 260;
		}
		else
		{
			menuSizeCount++;

			if (menuSizeCount > 0 && menuSizeCount <= 30) { menuSizeUp += 0.001f; }
			if (menuSizeCount > 30 && menuSizeCount <= 60) { menuSizeUp -= 0.001f; }
			if (menuSizeCount > 60) { menuSizeCount = 0; }

			// 
			if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_START))
			{
				isGameMenu = false;
				menuSe[2]->PlaySoundEffect();
			}

			if (!isDescriptionRule && !isDescriptionOperation)
			{
				if (KEY_INPUT.GetKey(KEY_INPUT_W) == KEY_ON)
				{
					menuCount--;
					menuSe[0]->PlaySoundEffect();
				}

				if (KEY_INPUT.GetKey(KEY_INPUT_S) == KEY_ON )
				{
					menuCount++;
					menuSe[0]->PlaySoundEffect();
				}


				// パッドの一瞬だけ
				if (!isPush && PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000)
				{
					isPush = true;
					menuCount--;
					menuSe[0]->PlaySoundEffect();
				}

				if (!isPush && PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000)
				{
					isPush = true;
					menuCount++;
					menuSe[0]->PlaySoundEffect();
				}

				if (isPush)
				{
					pushingCount++;
				}
				if (pushingCount >= 5)
				{
					isPush = false;
					pushingCount = 0;
				}
			}

			switch (menuCount)
			{
			case 0:
				menuY = 260;
				// マウスの左かパッドのAが押されたらゲームに戻る
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON )
				{
					isGameMenu = false;
					menuSe[2]->PlaySoundEffect();
				}
				break;
			case 1:
				menuY = 380;
				// マウスの左かパッドのAが押されたら操作説明表示
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
				{
					if (!isDescriptionOperation) { menuSe[2]->PlaySoundEffect(); }
					isDescriptionOperation = true;
				}
				break;
			case 2:
				menuY = 495;
				// マウスの左かパッドのAが押されたらルール説明表示
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
				{
					if (!isDescriptionRule) { menuSe[2]->PlaySoundEffect(); }
					isDescriptionRule = true;
				}
				break;
			case 3:
				menuY = 615;
				// マウスの左かパッドのAが押されたらメニューに戻る
				if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
				{
					FADE.TermsFadeOut_Play("Fast");
					menuSe[2]->PlaySoundEffect();
				}
				break;
			}

			// 最大値設定
			if (menuCount < 0) { menuCount = 3; }
			if (menuCount > 3) { menuCount = 0; }
		}
	}

	// 説明用
	if (isDescription)
	{
		if (!isGameMenu)
		{
			// アイテムショップに入っていなければ
			if (!defenseManager->GetLetsShop())
			{
				bullet = player->GetShot().GetShot();
				itr = player->GetShot().GetItr();

				// ゲーム開始まで時間をつける
				gameStartCount++;
				if (gameStartCount >= GAME_START_COUNT) { isStart = true; }
				else { SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2); }

				// タワーのインターバルではないとき
				if (!Tower::GetWaveInterval())
				{
					if (isStart) { gameCount++; }

					if (gameCount % ONE_SECOND == 1) { gameTime++; }
				}

				// プレイヤーと地面の当たり判定
				HitCheck::HitCheckPlayerToGound(player, &STAGE, player->GetCharaSize());

				// 雑魚敵
				for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
				{
					// アイテムとプレイヤーの当たり判定
					HitCheck::HitCheckBoxPlayerToItem(player, &itemManager->GetSmallEnemyItemRecovery(i));
					HitCheck::HitCheckBoxPlayerToCoin(player, &itemManager->GetSmallEnemyItemCoin(i));

					// 雑魚敵と銃弾の当たり判定
					if (!bullet.empty())
					{
						// たまが出ていれば
						for (itr = bullet.begin(); itr != bullet.end(); itr++)
						{
							HitCheck::HitCheckGun((*itr)->pos, &enemy->GetEnemy(i), 2.f);
						}
					}
				}

				// 中ボス
				for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++)
				{
					// アイテムとプレイヤーの当たり判定
					HitCheck::HitCheckBoxPlayerToItem(player, &itemManager->GetMediumBossItemRecovery(i));
					HitCheck::HitCheckBoxPlayerToCoin(player, &itemManager->GetMediumBossItemCoin(i));

					// 中ボスと銃弾の当たり判定
					if (!bullet.empty())
					{
						// たまが出ていれば
						for (itr = bullet.begin(); itr != bullet.end(); itr++)
						{
							HitCheck::HitCheckGun((*itr)->pos, &enemy->GetMedium(i), 2.5f);
						}
					}
				}

				// ボス
				for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++)
				{
					// アイテムとプレイヤーの当たり判定
					HitCheck::HitCheckBoxPlayerToItem(player, &itemManager->GetBossItemRecovery(i));
					HitCheck::HitCheckBoxPlayerToCoin(player, &itemManager->GetBossItemCoin(i));

					// ボスと銃弾の当たり判定
					if (!bullet.empty() && enemy->GetBoss(i).GetLife() != 0)
					{
						// たまが出ていれば
						for (itr = bullet.begin(); itr != bullet.end(); itr++)
						{
							HitCheck::HitCheckGun((*itr)->pos, &enemy->GetBoss(i), 3.f);
						}
					}
				}

				// マップの更新
				STAGE.Update();

				// プレイヤーの更新
				player->Update(*camera);

				// タワーの更新
				tower->Update();

				// エネミーの更新
				enemy->Update(player, camera, tower);

				// 各エネミーの更新
				enemy->EnemyManagerUpdate(player, &STAGE);

				for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++)
				{
					for (int j = 0; j < ItemManager::MEDIUM_BOSS_ITEM_MAX; j++)
					{
						for (int k = 0; k < ItemManager::BOSS_ITEM_MAX; k++)
						{
							// ディフェンス管理
							defenseManager->Update(player, &enemy->GetEnemy(i), &enemy->GetMedium(j), &enemy->GetBoss(k));
							// ミニマップ管理
							miniMap->UpdatePlayerMap(player, tower);
							miniMap->UpdateSmall(&enemy->GetEnemy(i), i);
							miniMap->UpdateMedium(&enemy->GetMedium(j), j);
							miniMap->UpdateBoss(&enemy->GetBoss(k), k);
							// 必殺技使用時の当たり判定
							if (player->GetDeathBlow())
							{
								HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(player, &enemy->GetEnemy(i));
								HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(player, &enemy->GetMedium(j));
								HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(player, &enemy->GetBoss(k));
							}
						}
					}
				}

				// エネミーが持っているアイテム更新
				for (int i = 0; i < ItemManager::SMALL_ENEMY_ITEM_MAX; i++) { itemManager->UpdateSmallEnemy(&enemy->GetEnemy(i), i); }
				for (int i = 0; i < ItemManager::MEDIUM_BOSS_ITEM_MAX; i++) { itemManager->UpdateMediumBoss(&enemy->GetMedium(i), i); }
				for (int i = 0; i < ItemManager::BOSS_ITEM_MAX; i++) { itemManager->UpdateBoss(&enemy->GetBoss(i), i); }

				// アイテムが寄ってくる
				itemManager->UpdatePlayer(player);

				// カメラの更新
				camera->Update(player, tower);

				// 各エフェクトの更新
				EFFECT.Update();

			}
			// アイテムショップに入っていれば
			else
			{
				// プレイヤー初期位置
				player->SetPos(PLAYER_INIT_POS);
				// カメラ初期位置
				camera->CameraDirInit();
				defenseManager->ShopUpdate(player);
			}
		}
	}
	else
	{
		// 時間ごとに進む
		descriptionTimeCount++;
		if (descriptionTimeCount >= 300)
		{
			isOptionDescription = true;
		}
		if (descriptionTimeCount >= 600)
		{
			isDescription = true;
		}

		// 押されたら進む
		if (!isOptionDescription)
		{
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
			{
				isOptionDescription = true;
				menuSe[2]->PlaySoundEffect();
			}

		}
		else
		{
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON)
			{
				isDescription = true;
				menuSe[2]->PlaySoundEffect();
			}

			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B))
			{
				isOptionDescription = false;
				menuSe[1]->PlaySoundEffect();
			}
		}
	}

	// プレイヤーの体力がなくなれば負けフラグのオン
	if (player->GetLife() <= GAME_OVER || tower->GetLife() <= GAME_OVER)
	{
		isGameOver = true;
	}

	// 時間内守り切れば勝ち
	if (gameTime >= GAME_CLEAR_COUNT)
	{
		isGameClear = true;
	}

	// 規定条件を満たしたらフェードアウトの開始
	if (tower->GetTowerCount() >= TOWER_LIFE_ZERO_COUNT/* || KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON*/)
	{
		// 負けました
		result = "LOSE";

		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");
	}

	// 規定条件を満たしたらフェードアウトの開始
	if (Tower::GetWave() == WEAV_THREE && Tower::GetWaveIntervalCount() >= WEAV_THREE_INTERVAL /*|| KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON*/)
	{
		// 勝ちました
		result = "WIN";

		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");
	}

	// フェードアウトが終われば変更
	if (!isGameMenu && FADE.FadeOutEnd())
	{
		// 解放
		Release();
		// 切り替え
		return new SceneResult;
	}

	// 
	if (isGameMenu && FADE.FadeOutEnd())
	{
		// 解放
		Release();
		// 切り替え
		return new SceneMenu;
	}

	// ステージ読み込みがエラーを吐いたらもう一度読み込み
	if (STAGE.GetFailur())
	{
		// 解放
		Release();
		// 切り替え
		return new SceneGame;
	}

	// 現状維持
	return this;
}

void SceneGame::Draw()
{
	// 説明用
	if (isDescription)
	{
		if (!defenseManager->GetLetsShop())
		{
			// ショップBGM 停止
			shopBGM->StopBackGroundMusic();
			// BGN再生
			bgm->OnePlayBackGroundMusic();

			STAGE.Draw();								// ステージ描画
			player->Draw();								// プレイヤー描画
			enemy->Draw();								// 敵描画
			enemy->EnemyManagerDraw(player, camera);	// 敵描画
			itemManager->Draw();						// アイテム描画
			camera->Draw();								// カメラ描画
			tower->Draw();								// タワー描画
			defenseManager->Draw();						// ディフェンス管理
			EFFECT.Draw();								// エフェクトの表示

			// タイムの表示
			if (gameStartCount >= COUNT_THREE) { startCount = 3; se[0]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_TWO) { startCount = 2;   se[1]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_ONE) { startCount = 1;   se[2]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_GAME_START) { startCount = 4; se[3]->OnePlaySoundEffect(); }
			if (gameStartCount >= COUNT_BLANK) startCount = 5;

			// ゲームカウントダウン
			if (startCount == 4) { DrawRotaGraphF(SCREEN_X / 2, 350, 1.0f,0.f, gameStartGraphHandle,TRUE); }
			if (startCount < 4 && startCount > 0) { DrawRotaGraphF(SCREEN_X / 2, 350, 1.0f, 0.f, timeCountGraphHandle[startCount - 1], TRUE); }
	
			// ユーザーインタフェース
			miniMap->Draw();
			ui->Draw(player, tower);

			// フェードイン
			if (!isGameMenu) { ui->FadeDraw(); }

			// タワーのウェーブクリア画像
			tower->GameWaveString();

			// 0秒ずつ始めるカウント
			if (gameTime == WEAV_TWO_COUNT) { gameTimeCount = -WEAV_TWO_COUNT; }
			if (gameTime == WEAV_THREE_COUNT) { gameTimeCount = -WEAV_THREE_COUNT; }

			playerMoneyCount=player->GetMoney();
			gameTimeNumber = gameTimeCount + gameTime;

			// 時間の画像
			DrawRotaGraph(80, 35, 0.4f, 0.0f, timeGraphHandle, TRUE);

			// 数字の画像
			if (gameTimeNumber >= 10) { 
				DrawRotaGraph(195, 35, 1.0f, 0.0f, numberGraphHandle[gameTimeNumber / 10], TRUE);
				DrawRotaGraph(235, 35, 1.0f, 0.0f, numberGraphHandle[gameTimeNumber % 10], TRUE);
			}
			else
			{
				DrawRotaGraph(195, 35, 1.0f, 0.0f, numberGraphHandle[gameTimeNumber], TRUE);
			}

			// ウェーブの画像
			DrawRotaGraph(80, 80, 0.2f, 0.0f, waveGraphHandle, TRUE);
			// 数字の画像
			DrawRotaGraph(190, 80, 1.0f,0.0f, numberGraphHandle[Tower::GetWave() + 1],TRUE);
			// お金の画像
			DrawRotaGraph(420, 750, 0.3f, 0.0f, moneyCountGraphHandle, TRUE);
			// お金の数字の画像
			if (playerMoneyCount == 0) { DrawRotaGraph(500, 750, 1.f, 0.0f, numberGraphHandle[0], TRUE); }
			// １００以上
			if (playerMoneyCount >= 100 && playerMoneyCount < 1000) {
			 DrawRotaGraph(500, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount / 100], TRUE); 
			 DrawRotaGraph(540, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			 DrawRotaGraph(580, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			}
			// １０００以上
			if (playerMoneyCount >= 1000 && playerMoneyCount < 10000) {
			DrawRotaGraph(500, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount / 1000], TRUE); 
			DrawRotaGraph(540, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount % 1000 / 100], TRUE);
			DrawRotaGraph(580, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			DrawRotaGraph(620, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			}
			// １００００以上
			if (playerMoneyCount >= 10000) {
			 DrawRotaGraph(500, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount / 10000], TRUE);
			 DrawRotaGraph(540, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount % 10000 / 1000], TRUE);
			 DrawRotaGraph(580, 750, 1.0f, 0.0f, numberGraphHandle[playerMoneyCount % 1000 / 100], TRUE);
			 DrawRotaGraph(620, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			 DrawRotaGraph(660, 750, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
			}

		}
		else
		{
			// 戦闘BGM停止
			bgm->StopBackGroundMusic();
			// ショップ画面表示
			defenseManager->ShopDraw();
			// ショップBGM再生
			shopBGM->OnePlayBackGroundMusic();
		}
	}
	else
	{
		// 説明画像表示
		if (!isOptionDescription) { DrawGraph(0, 0, descriptionGraphHandle[0], TRUE); }
		else { DrawGraph(0, 0, descriptionGraphHandle[1], TRUE); }
	}

	if (isGameMenu)
	{
		// 操作説明
		if (isDescriptionOperation)
		{
			// 戻るボタン
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B))
			{
				isDescriptionOperation = false;
				menuSe[1]->PlaySoundEffect();
			}
			// カウント増減
			if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON)
			{
				descriptionOperationCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// カウント増加
			if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON)
			{
				descriptionOperationCount++;
				menuSe[3]->PlaySoundEffect();
			}
			// カウント増減
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
			{
				isMenuPush = true;
				descriptionOperationCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// カウント増加
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
			{
				isMenuPush = true;
				descriptionOperationCount++;
				menuSe[3]->PlaySoundEffect();
			}

			if (isMenuPush)
			{
				menuPushingCount++;
			}
			if (menuPushingCount >= 5)
			{
				isMenuPush = false;
				menuPushingCount = 0;
			}

			// 最大値設定
			if (descriptionOperationCount < 0) { descriptionOperationCount = 1; }
			if (descriptionOperationCount > 1) { descriptionOperationCount = 0; }

			// 各値の時表示
			if (descriptionOperationCount == 0)
			{
				DrawGraph(0, 0, descriptionOperationGraphHandle[0], TRUE);
			}
			else
			{
				DrawGraph(0, 0, descriptionOperationGraphHandle[1], TRUE);
			}
		}

		// ルール説明
		if (isDescriptionRule)
		{
			// 戻るボタン
			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B))
			{
				isDescriptionRule = false;
				menuSe[1]->PlaySoundEffect();
			}
			// カウント増減
			if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON)
			{
				descriptionRuleCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// カウント増加
			if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON )
			{
				descriptionRuleCount++;
				menuSe[3]->PlaySoundEffect();
			}
			// カウント増減
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000)
			{
				isMenuPush = true;
				descriptionRuleCount--;
				menuSe[3]->PlaySoundEffect();
			}
			// カウント増加
			if (!isMenuPush && PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000)
			{
				isMenuPush = true;
				descriptionRuleCount++;
				menuSe[3]->PlaySoundEffect();
			}

			if (isMenuPush)
			{
				menuPushingCount++;
			}
			if (menuPushingCount >= 5)
			{
				isMenuPush = false;
				menuPushingCount = 0;
			}


			// 最大値設定
			if (descriptionRuleCount < 0) { descriptionRuleCount = 1; }
			if (descriptionRuleCount > 1) { descriptionRuleCount = 0; }

			// 各値の時表示
			if (descriptionRuleCount == 0)
			{
				DrawGraph(0, 0, descriptionRuleGraphHandle[0], TRUE);
			}
			else
			{
				DrawGraph(0, 0, descriptionRuleGraphHandle[1], TRUE);
			}
		}

		// 操作説明とルール説明じゃないときだけ表示
		if (!isDescriptionRule && !isDescriptionOperation)
		{
			DrawGraph(0, 0, menuGraphHandle, TRUE);
			DrawRotaGraph(530, menuY, 1.0f + menuSizeUp, 0.0f, menuFrameGraphHandle, TRUE);
			miniMap->MenuDraw();
		}
	}

	// フェードイン
	FADE.SlowFadeIn_Play();
	// フェードアウト
	FADE.FadeOut_Play();

}

// 削除
void SceneGame::Release()
{
	// プレイヤー
	if (player)
	{
		player->Release();
		delete(player);
		player = NULL;
	}

	// エネミー
	if (enemy)
	{
		enemy->Release();
		delete(enemy);
		enemy = NULL;
	}

	// マップ削除
	//STAGE.Release();

	// カメラ
	if (camera)
	{
		camera->~Camera();
		delete(camera);
		camera = NULL;
	}

	// ユーザインターフェース
	if (ui)
	{
		ui->Release();
		delete(ui);
		ui = NULL;
	}

	// ミニマップ
	if (miniMap)
	{
		miniMap->Release();
		delete(miniMap);
		miniMap = NULL;
	}

	// タワー
	if (tower)
	{
		tower->Release();
		delete(tower);
		tower = NULL;
	}

	// ディフェンスマネージャー
	if (defenseManager)
	{
		defenseManager->Release();
		delete(defenseManager);
		defenseManager = NULL;
	}

	// アイテムマネージャー
	if (itemManager)
	{
		itemManager->Release();
		delete(itemManager);
		itemManager = NULL;
	}

	// BGM
	if (bgm)
	{
		bgm->StopBackGroundMusic();
		bgm->Release();
		delete(bgm);
		bgm = NULL;
	}

	// ショップBGM
	if (shopBGM)
	{
		shopBGM->StopBackGroundMusic();
		shopBGM->Release();
		delete(shopBGM);
		shopBGM = NULL;
	}

	// 効果音
	for (int i = 0; i < 4; i++)
	{
		if (se[i])
		{
			se[i]->StopSoundEffect();
			se[i]->Release();
			delete(se[i]);
			se[i] = NULL;
		}

		if (menuSe[i])
		{
			menuSe[i]->StopSoundEffect();
			menuSe[i]->Release();
			delete(menuSe[i]);
			menuSe[i] = NULL;
		}
	}

	if (nowLoading)
	{
		nowLoading->Release();
		delete(nowLoading);
		nowLoading = NULL;
	}

	// 説明画像削除
	DeleteGraph(descriptionGraphHandle[0]);
	descriptionGraphHandle[0] = NULL;

	DeleteGraph(descriptionGraphHandle[1]);
	descriptionGraphHandle[1] = NULL;

	// ウェーブ画像
	DeleteGraph(waveGraphHandle);
	waveGraphHandle = NULL;
	// タイム画像
	DeleteGraph(timeGraphHandle);
	timeGraphHandle = NULL;

	// お金の画像
	DeleteGraph(moneyCountGraphHandle);
	moneyCountGraphHandle = NULL;

	// ゲームスタート画像
	DeleteGraph(gameStartGraphHandle);
	gameStartGraphHandle = NULL;
	//
	DeleteGraph(menuGraphHandle);
	menuGraphHandle = NULL;
	DeleteGraph(menuFrameGraphHandle);
	menuFrameGraphHandle = NULL;


	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(descriptionRuleGraphHandle[i]);
		descriptionRuleGraphHandle[i] = NULL;
		DeleteGraph(descriptionOperationGraphHandle[i]);
		descriptionOperationGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(timeCountGraphHandle[i]);
		timeCountGraphHandle[i] = NULL;
	}

	//
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numberGraphHandle[i]);
		numberGraphHandle[i] = NULL;
	}

}