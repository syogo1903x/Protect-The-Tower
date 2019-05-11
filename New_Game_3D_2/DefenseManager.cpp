#include "Common.h"

int DefenseManager::godbyeShopAnimationCount;
int DefenseManager::joinShopAnimationCount;

// コンストラクタ
DefenseManager::DefenseManager()
{

	wallModelHamdel = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_WALL));
	atackBallModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_ATACKBALL));
	fireModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_FIRE));
	soldierModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_SOLDIER));


	buyObject = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_BUY));

	// 兵士の銃弾
	soldierBulletModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::BULLET_SHOT));

	mapFrameGraphHandle = LoadGraph("img/character/frame2.png");

	itemFrameGraphHandle = LoadGraph("img/frame.png");

	buyGraphHandle = LoadGraph("img/Item/buy.png");
	backGraphHandle = LoadGraph("img/Item/deru.png");

	buttonGraphHandle[0] = LoadGraph("img/button/wall.png");
	buttonGraphHandle[1] = LoadGraph("img/button/atack.png");
	buttonGraphHandle[2] = LoadGraph("img/button/fire.png");
	buttonGraphHandle[3] = LoadGraph("img/button/soldier.png");

	backGroundGraphHadle = LoadGraph("img/backGround.png");

	woodGraphHamdle = LoadGraph("img/wood.png");

	// ディフェンスアイテムの画像
	nodeGraphHandle[0] = LoadGraph("img/Item/wall.png");
	nodeGraphHandle[1] = LoadGraph("img/Item/atack.png");
	nodeGraphHandle[2] = LoadGraph("img/Item/fire.png");
	nodeGraphHandle[3] = LoadGraph("img/Item/soldier.png");

	LoadDivGraph("img/flan.png", 2, 2, 1, 32, 32, moouseGraphHandle, TRUE);
	LoadDivGraph("img/舞台幕/640/pipo-curtain1.png", 10, 1, 10, 640, 480, openShopGraphHandle, TRUE);
	LoadDivGraph("img/舞台幕/640/pipo-curtain2.png", 18, 1, 18, 640, 480, closeShopGraphHandle, TRUE);

	// マップの画像取得
	if (SceneMenu::GetStage() == "stage/白玉楼ver0.93/白玉楼.pmx") { mapGraphHandle = LoadGraph("img/map/map1.png"); }
	if (SceneMenu::GetStage() == "stage/ラグビーグラウンド1.05/ラグビーグラウンド（芝生）.pmx") { mapGraphHandle = LoadGraph("img/map/map2.png"); }
	if (SceneMenu::GetStage() == "stage/月の都風弾幕ステージ/月の都風弾幕ステージ.pmx") { mapGraphHandle = LoadGraph("img/map/map3.png"); }

	// 効果音取得
	se[PURCASE] = new SoundEffect("Music/SE/clearing1.mp3");
	se[CHOICE] = new SoundEffect("Music/SE/cursor10.mp3");
	se[DECISION] = new SoundEffect("Music/SE/flying_pan.mp3");
	se[INSTALLATION] = new SoundEffect("Music/SE/sword-clash1.mp3");
	se[CANSEL] = new SoundEffect("Music/SE/cancel6.mp3");
	se[ENTRYSHOP] = new SoundEffect("Music/SE/key-drop1.mp3");
	se[CALL_ENTRY] = new SoundEffect("Music/SE/nyuten.mp3");
	se[CALL_BYE] = new SoundEffect("Music/SE/goodBye.mp3");

	openShopAnimationCount = 0;
	closeShopAnimationCount = 0;
	godbyeShopAnimationCount = 0;
	joinShopAnimationCount = 0;
	isShopEntry = false;

	// 説明用画像
	descriptionGraphHandle[0] = LoadGraph("img/Description_3.png");
	descriptionGraphHandle[1] = LoadGraph("img/Description_4.png");
	// 
	LoadDivGraph("img/number.png", 10, 10, 1, 64, 64, numberGraphHandle, TRUE);
	// 
	moneyGraphHandle = LoadGraph("img/money.png");


	descriptionCount = 0;
	isDescription = false;

	arrowModelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::DEFENSE_ARROW));

	MV1SetScale(arrowModelHandle, VGet(10, 10, 10));
	//MV1SetDifColorScale(arrowModelHandle, GetColorF(255, 255, 255, 255));
	mouseSpeed = 0;
}

// デストラクタ
DefenseManager::~DefenseManager()
{

}

// 初期化
void DefenseManager::Init()
{

	// 壁用リスト初期化
	DefenseWall *defenseWall = new DefenseWall(wallModelHamdel);
	notDefenseWallList.push_back(defenseWall);
	// 攻撃ボール用リスト初期化
	DefenseAtackBall *defenseAtackBall = new DefenseAtackBall(atackBallModelHandle);
	notDefenseAtackBallList.push_back(defenseAtackBall);
	// 炎攻撃用リスト初期化
	DefenseFire *defenseFire = new DefenseFire(fireModelHandle);
	notDefenseFireList.push_back(defenseFire);
	// 兵士攻撃用変数
	DefenseSoldier *defenseSoldier = new DefenseSoldier(soldierModelHandle);
	notDefenseSoldierList.push_back(defenseSoldier);
	

	// 壁 未使用リスト登録
	if (!notDefenseWallList.empty())
	{
		for (notDefenseWallIter = notDefenseWallList.begin(); notDefenseWallIter != notDefenseWallList.end(); notDefenseWallIter++)
		{
			(*notDefenseWallIter)->Init();
			(*notDefenseWallIter)->SetRotain(ZEROCLEAR);
		}
	}

	// 攻撃ボール 未使用リスト登録
	if (!notDefenseAtackBallList.empty())
	{
		for (notDefenseAtackBallIter = notDefenseAtackBallList.begin(); notDefenseAtackBallIter != notDefenseAtackBallList.end(); notDefenseAtackBallIter++)
		{
			(*notDefenseAtackBallIter)->Init();
		}
	}

	// 炎攻撃 未使用リスト登録
	if (!notDefenseFireList.empty())
	{
		for (notDefenseFireIter = notDefenseFireList.begin(); notDefenseFireIter != notDefenseFireList.end(); notDefenseFireIter++)
		{
			(*notDefenseFireIter)->Init();
		}
	}

	// 兵士攻撃 未使用リスト登録
	if (!notDefenseSoldierList.empty())
	{
		for (notDefenseSoldierIter = notDefenseSoldierList.begin(); notDefenseSoldierIter != notDefenseSoldierList.end(); notDefenseSoldierIter++)
		{
			(*notDefenseSoldierIter)->Init();
			(*notDefenseSoldierIter)->SetDefenseObject(soldierBulletModelHandle);
		}
	}

	// ショップ
	defenseBuyObject = new DefenseBuyObject(buyObject);
	defenseBuyObject->Init();

	// テクスチャとモデルの位置変更
	defenseBuyObject->SetPos(SHOP_INIT_POS);

	isDefenseShoppingMode = false;
	
	isWall = false;
	isAtackBall = false;
	isFire = false;
	isSoldier = false;

	for (int i = 0; i < SHOP_LINE; i++)
	{
		for (int j = 0; j < SHOP_COLUMN; j++)
		{
			isNodeFree[i][j] = false;
			isWallNode[i][j] = false;
			isAtackBallNode[i][j] = false;
			isFireNode[i][j] = false;
			isSoldierNode[i][j] = false;
		}
	}

	wallSizeCount = 0;
	atackBallSizeCount = 0;
	fireSizeCount = 0;
	soldierSizeCount = 0;
	isChangeControlor = true;
	itemNumber = 0;
}

// 更新
void DefenseManager::Update(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// ショップ効果音停止
	se[CALL_BYE]->StopSoundEffect();
	// ショップ入店退店のフェード 初期化
	openShopAnimationCount = 0;
	closeShopAnimationCount = 0;

	// お金
	possessionMoney = _player->GetMoney();

	// ショッピングオブジェクトとプレイヤーの当たり判定
	if (HitCheck::HitCheckBoxPlayerToBuyItemObject(_player, defenseBuyObject))
	{
		isShopEntry = true;
	}

	if (godbyeShopAnimationCount >= 17) { godbyeShopAnimationCount = 17; }
	if (joinShopAnimationCount >= 9) { joinShopAnimationCount = 9; }

	// 壁更新
	WallUpdate(_player, _small, _medium, _boss);
	// 攻撃ボール更新
	AttackBallUpdate(_player, _small, _medium, _boss);
	// 炎攻撃
	FireUpdate(_player, _small, _medium, _boss);
	// 兵士攻撃
	SoldierUpdate(_player, _small, _medium, _boss);

	// アイテムショップとプレイヤーの位置計算
	VECTOR buyObjeDir = VSub(_player->GetPos(), SHOP_INIT_POS);
	VECTOR buyObjeAngle = ZEROCLEAR;

	// 正規化
	if (VSquareSize(buyObjeDir) != 0)
	{
		buyObjeDir = VNorm(buyObjeDir);
	}

	// 向き変更
	float aimAngle = vec2Radian(&VGet(0, 0, -1), &buyObjeDir);

	// 向き更新
	buyObjeAngle.y = lerpRadian(buyObjeAngle.y, aimAngle, 1.f);

	// 矢印
	MV1SetPosition(arrowModelHandle, _player->GetPos());
	MV1SetRotationXYZ(arrowModelHandle, buyObjeAngle);

	// ショッピング更新
	defenseBuyObject->Update();

}

// 描画
void DefenseManager::Draw()
{
	// 入店時 退店時 フェード
	ShopFade();

	// 壁表示
	WallDraw();
	// 攻撃ボール表示
	AttackBallDraw();
	// 炎表示
	FireDraw();
	// 兵士表示
	SoldierDraw();
	// ショッピングモール表示
	defenseBuyObject->Draw();
}


// ショップ更新
void DefenseManager::ShopUpdate(CharacterBase *_player)
{
	DescriptionUpdate(_player);
}

// ショップ表示
void DefenseManager::ShopDraw()
{
	DescriptionDraw();
}

// ショップ入店退店フェード
void DefenseManager::ShopFade()
{
	// 入店時フェードイン
	joinShopAnimationCount++;

	// 退店時フェードアウト
	if (isShopEntry)
	{
		godbyeShopAnimationCount++;
		if (godbyeShopAnimationCount >= 10)
		{
			isDefenseShoppingMode = true;
			isShopEntry = false;
		}
	}
}

// 壁描画
void DefenseManager::WallDraw()
{
	// ディフェンス用壁 表示
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			if ((*defenseWallListIter)->GetDefense()) { (*defenseWallListIter)->Draw(); }
		}
	}
}

// 攻撃ボール描画
void DefenseManager::AttackBallDraw()
{
	// ディフェンス用アタックボール 表示
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			if ((*defenseAtackBallListIter)->GetDefense()) { (*defenseAtackBallListIter)->Draw(); }
		}
	}
}

// 炎描画
void DefenseManager::FireDraw()
{

	// ディフェンス用炎 表示
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			if ((*defenseFireListIter)->GetDefense()) { (*defenseFireListIter)->Draw(); }
		}
	}
}

// 兵士描画
void DefenseManager::SoldierDraw()
{

	// ディフェンス用兵士 表示
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			if ((*defenseSoldierListIter)->GetDefense()) { (*defenseSoldierListIter)->Draw(); }
		}
	}
}

// HP表示
void DefenseManager::HpDraw()
{
	// ディレクショナルライトの作成
	lightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, -1.0f));
	upLightHandle = CreateDirLightHandle(VGet(0.0f, 1.0f, 0.0f));

	// ディフェンス用壁のHP表示
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			if ((*defenseWallListIter)->GetDefense()) { (*defenseWallListIter)->HpDraw(); }
		}
	}

	// ディフェンス用アタックボールのHP表示
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			if ((*defenseAtackBallListIter)->GetDefense()) { (*defenseAtackBallListIter)->HpDraw(); }
		}
	}

	// ディフェンス用炎のHP表示
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			if ((*defenseFireListIter)->GetDefense()) { (*defenseFireListIter)->HpDraw(); }
			if ((*defenseFireListIter)->GetDefense()) { EFFECT.UpdateFire((*defenseFireListIter), defenseFireList.size()); }
		}
	}

	// ディフェンス用兵士のHP表示
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			if ((*defenseSoldierListIter)->GetDefense()) { (*defenseSoldierListIter)->HpDraw(); }
		}
	}

	if (Tower::GetWaveInterval()) { MV1DrawModel(arrowModelHandle); }
	//MV1DrawModel(arrowModelHandle);

	// ライトの削除
	DeleteLightHandle(lightHandle);
	DeleteLightHandle(upLightHandle);
}

// 壁更新
void DefenseManager::WallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// ディフェンス用壁更新
	// 壁 使用リストにあれば
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			// 出現していれば
			if ((*defenseWallListIter)->GetDefense())
			{
				// 更新
				(*defenseWallListIter)->Update();

				// 壁の当たり判定
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _player, WALL_PLAYER_RANGE, 0);
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _small, WALL_SMALL_ENEMY_RANGE, WALL_SMALL_ENEMY_DAMAGE);
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _medium, WALL_MEDIUM_BOSS_RANGE, WALL_MEDIUM_BOSS_DAMAGE);
				HitCheck::HitCheckDefenseWall((*defenseWallListIter), _boss, WALL_BOSS_RANGE, WALL_BOSS_DAMAGE);
			}

			// 壁の耐久地が減れば未使用リストへの追加
			if ((*defenseWallListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseWallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseWallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isWallNode[(int)(NODE_LINE - (*defenseWallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseWallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// 設置していないことにする
				(*defenseWallListIter)->SetDefense(false);

				// 使用リストから未使用リストへ
				notDefenseWallList.push_back(*defenseWallListIter);
				defenseWallList.remove(*defenseWallListIter);
				break;
			}
		}
	}
}

// 攻撃ボール更新
void DefenseManager::AttackBallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// ディフェンス用アタックボール更新
	// 攻撃ボール 使用リストにあれば
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			// 出現していれば
			if ((*defenseAtackBallListIter)->GetDefense())
			{
				// 更新
				(*defenseAtackBallListIter)->Update();

				// 攻撃ボールとの当たり判定
				HitCheck::HitCheckDefenseAtackBall((*defenseAtackBallListIter), _small, ATACKBALL_SMALL_ENEMY_RANGE, ATACKBALL_SMALL_ENEMY_ATACK_DAMAGE, ATACKBALL_SMALL_ENEMY_HIT_DAMAGE);
				HitCheck::HitCheckDefenseAtackBall((*defenseAtackBallListIter), _medium, ATACKBALL_MEDIUM_BOSS_RANGE, ATACKBALL_MEDIUM_BOSS_ATACK_DAMAGE, ATACKBALL_MEDIUM_BOSS_HIT_DAMAGE);
				HitCheck::HitCheckDefenseAtackBall((*defenseAtackBallListIter), _boss, ATACKBALL_BOSS_RANGE, ATACKBALL_BOSS_ATACK_DAMAGE, ATACKBALL_BOSS_HIT_DAMAGE);
			}
			// 攻撃ボールの耐久地が減れば未使用リストへの追加
			if ((*defenseAtackBallListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseAtackBallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseAtackBallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isAtackBallNode[(int)(NODE_LINE - (*defenseAtackBallListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseAtackBallListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// 設置していないことにする
				(*defenseAtackBallListIter)->SetDefense(false);

				// 使用リストから未使用リストへ
				notDefenseAtackBallList.push_back(*defenseAtackBallListIter);
				defenseAtackBallList.remove(*defenseAtackBallListIter);
				break;
			}
		}
	}
}

// 炎更新
void DefenseManager::FireUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// ディフェンス用炎更新
	// 炎攻撃 使用リストにあれば
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			// 出現していれば
			if ((*defenseFireListIter)->GetDefense())
			{
				// 更新
				(*defenseFireListIter)->Update();

				// 炎攻撃の当たり判定
				HitCheck::HitCheckDefenseFire((*defenseFireListIter), _small, FIRE_SMALL_ENEMY_RANGE, FIRE_SMALL_ENEMY_ATACK_DAMAGE, FIRE_SMALL_ENEMY_HIT_DAMAGE);
				HitCheck::HitCheckDefenseFire((*defenseFireListIter), _medium, FIRE_MEDIUM_BOSS_RANGE, FIRE_MEDIUM_BOSS_ATACK_DAMAGE, FIRE_MEDIUM_BOSS_HIT_DAMAGE);
				HitCheck::HitCheckDefenseFire((*defenseFireListIter), _boss, FIRE_BOSS_RANGE, FIRE_BOSS_ATACK_DAMAGE, FIRE_BOSS_HIT_DAMAGE);
			}
			// 炎攻撃の耐久地が減れば未使用リストへの追加
			if ((*defenseFireListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseFireListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseFireListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isFireNode[(int)(NODE_LINE - (*defenseFireListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseFireListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// 設置していないことにする
				(*defenseFireListIter)->SetDefense(false);
				// 使用リストから未使用リストへ
				notDefenseFireList.push_back(*defenseFireListIter);
				defenseFireList.remove(*defenseFireListIter);
				break;
			}
		}
	}
}

// 兵士更新
void DefenseManager::SoldierUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss)
{
	// ディフェンス用兵士更新
	// 兵士攻撃 使用リストにあれば
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			// 出現していれば
			if ((*defenseSoldierListIter)->GetDefense())
			{
				// 更新
				(*defenseSoldierListIter)->Update();

				// 兵士攻撃の当たり判定
				HitCheck::HitCheckDefenseSoldier((*defenseSoldierListIter), _small, SOLDIER_SMALL_ENEMY_RANGE, SOLDIER_SMALL_ENEMY_HIT_DAMAGE);
				HitCheck::HitCheckDefenseSoldier((*defenseSoldierListIter), _medium, SOLDIER_MEDIUM_BOSS_RANGE, SOLDIER_MEDIUM_BOSS_HIT_DAMAGE);
				HitCheck::HitCheckDefenseSoldier((*defenseSoldierListIter), _boss, SOLDIER_BOSS_RANGE, SOLDIER_BOSS_HIT_DAMAGE);

				// 範囲内かどうか
				if (HitCheck::HitCheckCircleEnemyToSoldier(_small, (*defenseSoldierListIter), SOLDIER_WITH_IN_RANGE))
				{
					HitCheck::HitCheckDefenseSoldierBullet((*defenseSoldierListIter), _small, SOLDIER_SMALL_ENEMY_RANGE, SOLDIER_SMALL_ENEMY_ATACK_DAMAGE);
					(*defenseSoldierListIter)->SetTargetEnemy(_small->GetPos());
					(*defenseSoldierListIter)->SetAngleSpeed(0.2f);
				}
				else if (HitCheck::HitCheckCircleEnemyToSoldier(_medium, (*defenseSoldierListIter), SOLDIER_WITH_IN_RANGE))
				{
					HitCheck::HitCheckDefenseSoldierBullet((*defenseSoldierListIter), _medium, SOLDIER_MEDIUM_BOSS_RANGE, SOLDIER_MEDIUM_BOSS_ATACK_DAMAGE);
					(*defenseSoldierListIter)->SetTargetEnemy(_medium->GetPos());
					(*defenseSoldierListIter)->SetAngleSpeed(0.2f);
				}
				else if (HitCheck::HitCheckCircleEnemyToSoldier(_boss, (*defenseSoldierListIter), SOLDIER_WITH_IN_RANGE))
				{
					HitCheck::HitCheckDefenseSoldierBullet((*defenseSoldierListIter), _boss, SOLDIER_BOSS_RANGE, SOLDIER_BOSS_ATACK_DAMAGE);
					(*defenseSoldierListIter)->SetTargetEnemy(_boss->GetPos());
					(*defenseSoldierListIter)->SetAngleSpeed(0.2f);
				}
				else
				{
					(*defenseSoldierListIter)->SetAngleSpeed(0.f);
				}
			}
			// 兵士攻撃の耐久地が減れば未使用リストへの追加
			if ((*defenseSoldierListIter)->GetLife() <= 0)
			{
				isNodeFree[(int)(NODE_LINE - (*defenseSoldierListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseSoldierListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				isSoldierNode[(int)(NODE_LINE - (*defenseSoldierListIter)->GetPos().x) / NODE_DIVISION_LINE][(int)(NODE_COLUMN + (*defenseSoldierListIter)->GetPos().z) / NODE_DIVISION_COLUMN] = false;
				// 設置していないことにする
				(*defenseSoldierListIter)->SetDefense(false);

				// 使用リストから未使用リストへ
				notDefenseSoldierList.push_back(*defenseSoldierListIter);
				defenseSoldierList.remove(*defenseSoldierListIter);
				break;
			}
		}
	}
}

// 説明更新
void DefenseManager::DescriptionUpdate(CharacterBase *_player)
{
	// 説明用
	if (isDescription)
	{
		se[ENTRYSHOP]->OnePlaySoundEffect();
		se[CALL_ENTRY]->OnePlaySoundEffect();

		godbyeShopAnimationCount = 0;
		joinShopAnimationCount = 0;

		animation++;
		openShopAnimationCount++;

		// プレイヤーの所持金の変更新
		possessionMoney = _player->GetMoney();

		// デバック用 お金貯める減らす
		//if (KEY_INPUT.GetKey(KEY_INPUT_O)) _player->SetMoney(100);
		//if (KEY_INPUT.GetKey(KEY_INPUT_P)) _player->SetMoney(-100);

		bool isMouse = isChangeControlor && MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT);
		bool isControl = !isChangeControlor && PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A);


		// 当たり判定内にあってかつパッドの時は移動を遅くする
		if ((SCREEN_X / 2.5f - 35) - 17.5f < mouseX && (SCREEN_X / 2.5f + 350) + 17.5f > mouseX &&
			(SCREEN_Y / 1.8f - 17) - 17.5f < mouseY && (SCREEN_Y / 1.8f + 175) + 17.5f > mouseY)
		{
			// マウスの速度を下げる
			mouseSpeed = 10;
		}
		else
		{
			// マウスの速度を下げる
			mouseSpeed = 0;
		}

		// マウスの位置取得
		if (isChangeControlor)
		{
			GetMousePoint(&mouseX, &mouseY);
			// 
			if (PAD_INPUT.GetPadInput("1P").ThumbLX <= -STICK_LEAN ||
				PAD_INPUT.GetPadInput("1P").ThumbLX >= STICK_LEAN ||
				PAD_INPUT.GetPadInput("1P").ThumbLY <= -STICK_LEAN ||
				PAD_INPUT.GetPadInput("1P").ThumbLY >= STICK_LEAN)
			{
				isChangeControlor = false;
			}

		}
		else
		{
			if (PAD_INPUT.GetPadInput("1P").ThumbLX <= -STICK_LEAN) { mouseX -= MOUSE_SPEED - mouseSpeed; }
			if (PAD_INPUT.GetPadInput("1P").ThumbLX >= STICK_LEAN) { mouseX += MOUSE_SPEED - mouseSpeed; }
			if (PAD_INPUT.GetPadInput("1P").ThumbLY <= -STICK_LEAN) { mouseY += MOUSE_SPEED - mouseSpeed; }
			if (PAD_INPUT.GetPadInput("1P").ThumbLY >= STICK_LEAN) { mouseY -= MOUSE_SPEED - mouseSpeed; }

			if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) ||
				MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) ||
				MOUSE_INPUT.MousePush(MOUSE_INPUT_MIDDLE))
			{
				isChangeControlor = true;
			}
		}

		// 現在のショップにいる番号
		if (itemNumber == 0)
		{
			if (isMouse || isControl)
			{
				// ショップ壁表示
				WallShopUpdate(_player);
				// ショップ攻撃ボール表示
				AttackBallShopUpdate(_player);
				// ショップ炎表示
				FireShopUpdate(_player);
				// ショップ兵士表示
				SoldierShopUpdate(_player);
			}

			for (int i = 0; i < SHOP_LINE; i++)
			{
				for (int j = 0; j < SHOP_COLUMN; j++)
				{
					// 当たり判定でアイテムがなければ設置
					if ((SCREEN_X / 2.5f + i * 35) - 17.5f < mouseX && (SCREEN_X / 2.5f + i * 35) + 17.5f > mouseX &&
						(SCREEN_Y / 1.8f + j * 35) - 17.5f < mouseY && (SCREEN_Y / 1.8f + j * 35) + 17.5f > mouseY &&
						!isNodeFree[i][j])
					{
						//printfDx("%d : %d \n", i, j);

						if (isMouse || isControl)
						{
							// 各防衛アイテムがない時の音
							ShopItemStopSound();

							// 壁設置
							WallInstallation(i, j);
							// 攻撃ボール設置
							AttackBallInstallation(i, j);
							// 炎設置
							FireInstallation(i, j);
							// 兵士設置
							SoldierInstallation(i, j);							
						}
					}
				}
			}
		}
		else
		{
			closeShopAnimationCount++;
			if (closeShopAnimationCount >= 17)
			{
				isDefenseShoppingMode = false;
				itemNumber = 0;
				se[ENTRYSHOP]->StopSoundEffect();
				se[CALL_ENTRY]->StopSoundEffect();
				// マウスの初期座標中心
				SetMousePoint(SCREEN_X / 2, SCREEN_Y / 2);
			}
		}

		// 当たり判定
		if (1420 - 150 < mouseX && 1420 + 150 > mouseX &&
			110 - 100 < mouseY && 110 + 100 > mouseY)
		{
			if (isMouse || isControl)
			{
				itemNumber = 1;
				se[CALL_BYE]->OnePlaySoundEffect();
			}
		}
	}
	else
	{
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A)) { descriptionCount++; se[DECISION]->PlaySoundEffect(); }
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B)) { descriptionCount--; se[CANSEL]->PlaySoundEffect(); }

		if (descriptionCount >= 2) { isDescription = true; }
		if (descriptionCount < 0) { descriptionCount = 0; }
	}
}

// ショップ壁更新
void DefenseManager::WallShopUpdate(CharacterBase *_player)
{
	// 壁のボタン
	if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
		SHOP_Y_2 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + SHOP_BLANK_2 > mouseY)
	{
		// 効果音再生
		se[CHOICE]->PlaySoundEffect();

		isWall = true;
		isAtackBall = false;
		isFire = false;
		isSoldier = false;
	}

	if (isWall)
	{
		if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
			SHOP_Y_2 + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + 150 + SHOP_BLANK_2 > mouseY)
		{
			if (_player->GetMoney() >= WALL_MONEY_CONSUMPTION)
			{
				// 効果音再生
				se[PURCASE]->PlaySoundEffect();
				// 壁リストがあれば
				if (!notDefenseWallList.empty())
				{
					for (notDefenseWallIter = notDefenseWallList.begin(); notDefenseWallIter != notDefenseWallList.end(); notDefenseWallIter++)
					{
						// 壁の取得を増やす
						wallSizeCount++;
						// 未使用リストから使用リストへ
						defenseWallList.push_back(*notDefenseWallIter);
						notDefenseWallList.remove(*notDefenseWallIter);
						// 買ったお金の削除
						_player->SetMoney(-WALL_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// ショップ攻撃ボール更新
void DefenseManager::AttackBallShopUpdate(CharacterBase *_player)
{
	// 攻撃ボールのボタン
	if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
		SHOP_Y - SHOP_BLANK_2 < mouseY && SHOP_Y + SHOP_BLANK_2 > mouseY)
	{
		// 効果音再生
		se[CHOICE]->PlaySoundEffect();

		isAtackBall = true;
		isWall = false;
		isFire = false;
		isSoldier = false;
	}

	if (isAtackBall)
	{
		if (SHOP_X - SHOP_BLANK < mouseX && SHOP_X + SHOP_BLANK > mouseX &&
			SHOP_Y + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y + 150 + SHOP_BLANK_2 > mouseY)
		{
			// 攻撃ボールであれば
			if (_player->GetMoney() >= ATACKBALL_MONEY_CONSUMPTION)
			{
				// 効果音再生
				se[PURCASE]->PlaySoundEffect();
				// 
				if (!notDefenseAtackBallList.empty())
				{
					for (notDefenseAtackBallIter = notDefenseAtackBallList.begin(); notDefenseAtackBallIter != notDefenseAtackBallList.end(); notDefenseAtackBallIter++)
					{
						// 攻撃ボールの取得を増やす
						atackBallSizeCount++;
						// 未使用リストから使用リストへ
						defenseAtackBallList.push_back(*notDefenseAtackBallIter);
						notDefenseAtackBallList.remove(*notDefenseAtackBallIter);
						// 買ったお金の削除
						_player->SetMoney(-ATACKBALL_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// ショップ炎更新
void DefenseManager::FireShopUpdate(CharacterBase *_player)
{
	// 炎攻撃のボタン
	if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
		SHOP_Y_2 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + SHOP_BLANK_2 > mouseY)
	{
		// 効果音再生
		se[CHOICE]->PlaySoundEffect();

		isAtackBall = false;
		isWall = false;
		isFire = true;
		isSoldier = false;

	}
	if (isFire)
	{
		if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
			SHOP_Y_2 + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y_2 + 150 + SHOP_BLANK_2 > mouseY)
		{
			// 炎攻撃であれば
			if (_player->GetMoney() >= FIRE_MONEY_CONSUMPTION)
			{
				// 効果音再生
				se[PURCASE]->PlaySoundEffect();
				// 
				if (!notDefenseFireList.empty())
				{
					for (notDefenseFireIter = notDefenseFireList.begin(); notDefenseFireIter != notDefenseFireList.end(); notDefenseFireIter++)
					{
						// 炎攻撃の取得を増やす
						fireSizeCount++;
						// 未使用リストから使用リストへ
						defenseFireList.push_back(*notDefenseFireIter);
						notDefenseFireList.remove(*notDefenseFireIter);
						// 買ったお金の削除
						_player->SetMoney(-FIRE_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// ショップ兵士更新
void DefenseManager::SoldierShopUpdate(CharacterBase *_player)
{
	// 兵士攻撃のボタン
	if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
		SHOP_Y - SHOP_BLANK_2 < mouseY && SHOP_Y + SHOP_BLANK_2 > mouseY)
	{
		// 効果音再生
		se[CHOICE]->PlaySoundEffect();
		// 
		isAtackBall = false;
		isWall = false;
		isFire = false;
		isSoldier = true;

	}
	if (isSoldier)
	{
		if (0 < mouseX && SHOP_BLANK * 2 > mouseX &&
			SHOP_Y + 150 - SHOP_BLANK_2 < mouseY && SHOP_Y + 150 + SHOP_BLANK_2 > mouseY)
		{
			// 兵士攻撃であれば
			if (_player->GetMoney() >= SOLDIER_MONEY_CONSUMPTION)
			{
				// 効果音再生
				se[PURCASE]->PlaySoundEffect();
				// 
				if (!notDefenseSoldierList.empty())
				{
					for (notDefenseSoldierIter = notDefenseSoldierList.begin(); notDefenseSoldierIter != notDefenseSoldierList.end(); notDefenseSoldierIter++)
					{
						// 兵士攻撃の取得を増やす
						soldierSizeCount++;
						// 未使用リストから使用リストへ
						defenseSoldierList.push_back(*notDefenseSoldierIter);
						notDefenseSoldierList.remove(*notDefenseSoldierIter);
						// 買ったお金の削除
						_player->SetMoney(-SOLDIER_MONEY_CONSUMPTION);
						break;
					}
				}
			}
			else
			{
				se[CANSEL]->PlaySoundEffect();
			}
		}
	}
}

// 防衛アイテムがない時の音
void DefenseManager::ShopItemStopSound()
{
	if (wallSizeCount == 0 && isWall) { se[CANSEL]->PlaySoundEffect(); }
	if (atackBallSizeCount == 0 && isAtackBall) { se[CANSEL]->PlaySoundEffect(); }
	if (fireSizeCount == 0 && isFire) { se[CANSEL]->PlaySoundEffect(); }
	if (soldierSizeCount == 0 && isSoldier) { se[CANSEL]->PlaySoundEffect(); }
}

// 壁設置
void DefenseManager::WallInstallation(int _row, int _col)
{
	// 壁の使用リストにあれば
	if (!defenseWallList.empty())
	{
		for (defenseWallListIter = defenseWallList.begin(); defenseWallListIter != defenseWallList.end(); defenseWallListIter++)
		{
			// かつ設置されていなければ
			if (!(*defenseWallListIter)->GetDefense() && isWall)
			{
				// 効果音再生
				if (wallSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// 数を減らす
				wallSizeCount--;
				isWallNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// 設置
				(*defenseWallListIter)->SetDefense(true);
				(*defenseWallListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// 攻撃ボール設置
void DefenseManager::AttackBallInstallation(int _row, int _col)
{
	// 攻撃ボールの使用リストにあれば
	if (!defenseAtackBallList.empty())
	{
		for (defenseAtackBallListIter = defenseAtackBallList.begin(); defenseAtackBallListIter != defenseAtackBallList.end(); defenseAtackBallListIter++)
		{
			// かつ設置されていなければ
			if (!(*defenseAtackBallListIter)->GetDefense() && isAtackBall)
			{
				// 効果音再生
				if (atackBallSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// 数を減らし
				atackBallSizeCount--;
				isAtackBallNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// 設置
				(*defenseAtackBallListIter)->SetDefense(true);
				(*defenseAtackBallListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// 炎設置
void DefenseManager::FireInstallation(int _row, int _col)
{
	// 炎攻撃の使用リストにあれば
	if (!defenseFireList.empty())
	{
		for (defenseFireListIter = defenseFireList.begin(); defenseFireListIter != defenseFireList.end(); defenseFireListIter++)
		{
			// かつ設置されていなければ
			if (!(*defenseFireListIter)->GetDefense() && isFire)
			{
				// 効果音再生
				if (fireSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// 数を減らす
				fireSizeCount--;
				isFireNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// 設置
				(*defenseFireListIter)->SetDefense(true);
				(*defenseFireListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// 兵士設置
void DefenseManager::SoldierInstallation(int _row, int _col)
{
	// 兵士攻撃の使用リストにあれば
	if (!defenseSoldierList.empty())
	{
		for (defenseSoldierListIter = defenseSoldierList.begin(); defenseSoldierListIter != defenseSoldierList.end(); defenseSoldierListIter++)
		{
			// かつ設置されていなければ
			if (!(*defenseSoldierListIter)->GetDefense() && isSoldier)
			{
				// 効果音再生
				if (soldierSizeCount > 0) { se[INSTALLATION]->PlaySoundEffect(); }

				// 数を減らし
				soldierSizeCount--;
				isSoldierNode[_row][_col] = true;
				isNodeFree[_row][_col] = true;
				// 設置
				(*defenseSoldierListIter)->SetDefense(true);
				(*defenseSoldierListIter)->SetPos(VGet(NODE_LINE + (_row * -NODE_DIVISION_LINE), 0, -NODE_COLUMN + (_col * NODE_DIVISION_COLUMN)));
				break;
			}
		}
	}
}

// 説明表示
void DefenseManager::DescriptionDraw()
{
	// 説明用
	if (isDescription)
	{
		// 背景
		DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, backGroundGraphHadle, TRUE);


		// アイテムの配置
		if (itemNumber == 0)
		{
			DrawModiGraph(5, 5, 1300, 5, 1300, 220, 5, 220, itemFrameGraphHandle, TRUE);
			DrawRotaGraph(1440, 110, 1.0f, 0.0f, backGraphHandle, TRUE);

			DrawRotaGraph(SCREEN_X / 2, (int)(SCREEN_Y / 1.6f), 1.0f, 0.0f, woodGraphHamdle, TRUE);
			DrawRotaGraph(SCREEN_X / 2, (int)(SCREEN_Y / 1.6f), 1.0f, 0.0f, mapGraphHandle, TRUE);

			// 横10列 縦5行	
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 0.06f, 0.0f, mapFrameGraphHandle, TRUE);

					// そこにあれば表示
					if (isWallNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[0], TRUE); }
					if (isAtackBallNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[1], TRUE); }
					if (isFireNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[2], TRUE); }
					if (isSoldierNode[i][j]) { DrawRotaGraphF((SCREEN_X / 2.5f) + (i * 35), (SCREEN_Y / 1.8f) + (j * 35), 1.0f, 0.0f, nodeGraphHandle[3], TRUE); }

					// 当たり判定でアイテムがあれば警告
					if ((SCREEN_X / 2.5f + i * 35) - 17.5f < mouseX && (SCREEN_X / 2.5f + i * 35) + 17.5f > mouseX &&
						(SCREEN_Y / 1.8f + j * 35) - 17.5f < mouseY && (SCREEN_Y / 1.8f + j * 35) + 17.5f > mouseY &&
						isNodeFree[i][j])
					{
						if (isWall && wallSizeCount > 0 ||
							isAtackBall&& atackBallSizeCount > 0 ||
							isFire && fireSizeCount > 0 ||
							isSoldier&& soldierSizeCount > 0)
						{
							SetFontSize(60);
							DrawStringF(SCREEN_X / 3, 700, "空いてる枠においてね!", GetColor(0, 0, 0), GetColor(255, 255, 255));
							SetFontSize(DEFAULT_FONT_SIZE);
						}
					}
				}
			}

			// 選択されているものの表示黒縁
			// 壁
			WallDraw2D();
			// 攻撃ボール
			AttackBallDraw2D();
			// 炎
			FireDraw2D();
			// 兵士
			SoldierDraw2D();


			if (!isWall && !isAtackBall && !isFire && !isSoldier)
			{
				// 値段の表示
				SetFontSize(60);
				DrawFormatString(100, 50, GetColor(255, 255, 255), "買いたいものを選んでね!");
				SetFontSize(DEFAULT_FONT_SIZE);
			}

			// お金の表示
			ShopMoneyDraw();
		}

		// マウスの変更
		DrawGraph(mouseX, mouseY, moouseGraphHandle[animation % 2], TRUE);

		// フェードイン フェードアウト　描画
		if (closeShopAnimationCount >= 17) { closeShopAnimationCount = 17; }
		if (openShopAnimationCount >= 9) { openShopAnimationCount = 9; }

		DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, closeShopGraphHandle[closeShopAnimationCount], TRUE);
		DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, openShopGraphHandle[openShopAnimationCount], TRUE);
	}
	else
	{
		// 説明画像 描画
		if (descriptionCount == 0) { DrawGraph(0, 0, descriptionGraphHandle[0], TRUE); }
		if (descriptionCount == 1) { DrawGraph(0, 0, descriptionGraphHandle[1], TRUE); }
	}
}

// 壁2D表示
void DefenseManager::WallDraw2D()
{
	if (isWall)
	{
		DrawBox(SHOP_X - 110, SHOP_Y_2 - 75, SHOP_X + 110, SHOP_Y_2 + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X, SHOP_Y_2 + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// 値段の表示
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "壁は相手を止まらせてくれるぞ!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "お値段は100円");
		SetFontSize(DEFAULT_FONT_SIZE);

		// 選択中のアイテム表示
		if (wallSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[0], TRUE); }
	}
}

// 攻撃ボール2D表示
void DefenseManager::AttackBallDraw2D()
{
	if (isAtackBall)
	{
		DrawBox(SHOP_X - 110, SHOP_Y - 75, SHOP_X + 110, SHOP_Y + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X, SHOP_Y + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// 値段の表示
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "攻撃は相手を攻撃して跳ね飛ばすぞ!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "お値段は200円");
		SetFontSize(DEFAULT_FONT_SIZE);

		// 選択中のアイテム表示
		if (atackBallSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[1], TRUE); }
	}
}

// 炎2D表示
void DefenseManager::FireDraw2D()
{
	if (isFire)
	{
		DrawBox(SHOP_X_2 - 110, SHOP_Y_2 - 75, SHOP_X_2 + 110, SHOP_Y_2 + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X_2, SHOP_Y_2 + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// 値段の表示
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "炎は周りに来た敵を倒してくるぞ!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "お値段は400円");
		SetFontSize(DEFAULT_FONT_SIZE);

		// 選択中のアイテム表示
		if (fireSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[2], TRUE); }
	}
}

// 兵士2D表示
void DefenseManager::SoldierDraw2D()
{
	if (isSoldier)
	{
		DrawBox(SHOP_X_2 - 110, SHOP_Y - 75, SHOP_X_2 + 110, SHOP_Y + 75, GetColor(0, 0, 0), TRUE);
		DrawRotaGraph(SHOP_X_2, SHOP_Y + 150, 0.7f, 0.f, buyGraphHandle, TRUE);
		// 値段の表示
		SetFontSize(60);
		DrawFormatString(100, 50, GetColor(255, 255, 255), "兵士は君と一緒に敵を撃ってくれるぞ!");
		DrawFormatString(100, 140, GetColor(255, 255, 255), "お値段は500円");
		SetFontSize(DEFAULT_FONT_SIZE);

		// 選択中のアイテム表示
		if (soldierSizeCount > 0) { DrawGraph(mouseX - NODE_BLANK, mouseY - NODE_BLANK, nodeGraphHandle[3], TRUE); }
	}
}

void DefenseManager::ShopMoneyDraw()
{

	DrawRotaGraph(950, 160, 0.1f, 0.0f, moneyGraphHandle, TRUE);

	// お金の数字の画像
	if (possessionMoney == 0) { DrawRotaGraph(1000, 160, 1.f, 0.0f, numberGraphHandle[0], TRUE); }
	// １００以上
	if (possessionMoney >= 100 && possessionMoney < 1000) {
		DrawRotaGraph(1000, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney / 100], TRUE);
		DrawRotaGraph(1040, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
		DrawRotaGraph(1080, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
	}
	// １０００以上
	if (possessionMoney >= 1000 && possessionMoney < 10000) {
		DrawRotaGraph(1000, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney / 1000], TRUE);
		DrawRotaGraph(1040, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney % 1000 / 100], TRUE);
		DrawRotaGraph(1080, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
		DrawRotaGraph(1120, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
	}
	// １００００以上
	if (possessionMoney >= 10000) {
		DrawRotaGraph(1000, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney / 10000], TRUE);
		DrawRotaGraph(1040, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney % 10000 / 1000], TRUE);
		DrawRotaGraph(1080, 160, 1.0f, 0.0f, numberGraphHandle[possessionMoney % 1000 / 100], TRUE);
		DrawRotaGraph(1120, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
		DrawRotaGraph(1160, 160, 1.0f, 0.0f, numberGraphHandle[0], TRUE);
	}
	// ボタンの配置
	DrawRotaGraph(SHOP_X, SHOP_Y_2, 1.0f, 0.f, buttonGraphHandle[0], TRUE);
	DrawRotaGraph(SHOP_X, SHOP_Y, 1.0f, 0.f, buttonGraphHandle[1], TRUE);
	DrawRotaGraph(SHOP_X_2, SHOP_Y_2, 1.0f, 0.f, buttonGraphHandle[2], TRUE);
	DrawRotaGraph(SHOP_X_2, SHOP_Y, 1.0f, 0.f, buttonGraphHandle[3], TRUE);

	// アイテムの持っている個数
	SetFontSize(60);
	DrawFormatString(SHOP_X - 50, SHOP_Y_2 - 100, GetColor(0, 0, 0), "× %d", wallSizeCount);
	DrawFormatString(SHOP_X - 50, SHOP_Y - 100, GetColor(0, 0, 0), "× %d", atackBallSizeCount);
	DrawFormatString(SHOP_X_2 - 50, SHOP_Y_2 - 100, GetColor(0, 0, 0), "× %d", fireSizeCount);
	DrawFormatString(SHOP_X_2 - 50, SHOP_Y - 100, GetColor(0, 0, 0), "× %d", soldierSizeCount);
	SetFontSize(DEFAULT_FONT_SIZE);
}

// 解放
void DefenseManager::Release()
{
	// モデル
	MV1DeleteModel(wallModelHamdel);
	wallModelHamdel = NULL;
	MV1DeleteModel(atackBallModelHandle);
	atackBallModelHandle = NULL;
	MV1DeleteModel(fireModelHandle);
	fireModelHandle = NULL;
	MV1DeleteModel(soldierModelHandle);
	soldierModelHandle = NULL;
	MV1DeleteModel(buyObject);
	buyObject = NULL;
	MV1DeleteModel(soldierBulletModelHandle);
	soldierBulletModelHandle = NULL;


	MV1DeleteModel(arrowModelHandle);
	arrowModelHandle = NULL;


	// 画像
	DeleteGraph(buyGraphHandle);
	buyGraphHandle = NULL;
	DeleteGraph(backGraphHandle);
	backGraphHandle = NULL;

	DeleteGraph(descriptionGraphHandle[0]);
	descriptionGraphHandle[0] = NULL;
	DeleteGraph(descriptionGraphHandle[1]);
	descriptionGraphHandle[1] = NULL;
	DeleteGraph(mapGraphHandle);
	mapGraphHandle = NULL;

	for (int i = 0; i < 18; i++)
	{
		DeleteGraph(closeShopGraphHandle[i]);
		closeShopGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(openShopGraphHandle[i]);
		openShopGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(buttonGraphHandle[i]);
		buttonGraphHandle[i] = NULL;

		DeleteGraph(nodeGraphHandle[i]);
		nodeGraphHandle[i] = NULL;
	}

	DeleteGraph(mapFrameGraphHandle);
	mapFrameGraphHandle = NULL;
	DeleteGraph(itemFrameGraphHandle);
	itemFrameGraphHandle = NULL;
	DeleteGraph(backGroundGraphHadle);
	backGroundGraphHadle = NULL;
	DeleteGraph(woodGraphHamdle);
	woodGraphHamdle = NULL;
	DeleteGraph(moouseGraphHandle[0]);
	moouseGraphHandle[0] = NULL;
	DeleteGraph(moouseGraphHandle[1]);
	moouseGraphHandle[1] = NULL;

	//
	defenseWallList.clear();
	notDefenseWallList.clear();
	//
	defenseAtackBallList.clear();
	notDefenseAtackBallList.clear();
	//
	defenseFireList.clear();
	notDefenseFireList.clear();
	//
	defenseSoldierList.clear();
	notDefenseSoldierList.clear();

	DeleteGraph(moneyGraphHandle);
	moneyGraphHandle = NULL;

	//
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numberGraphHandle[i]);
		numberGraphHandle[i] = NULL;
	}

	// 
	defenseBuyObject->Release();
	delete(defenseBuyObject);
	defenseBuyObject = NULL;

	// サウンド
	for (int i = 0; i < 5; i++)
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
