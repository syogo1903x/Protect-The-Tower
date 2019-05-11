#include "UI.h"

void UI::Init(char *_playerNumber)
{
	playerHeartDownGraphHandle = LoadGraph("img/player/_heart.png");
	playerHeartGraphHandle = LoadGraph("img/player/heart.png");
	playerIconGraphHandle = LoadGraph("img/player/icon.png");
	playerIconDownGraphHandle = LoadGraph("img/player/iconDown.png");

	playerGraphHandle[0] = LoadGraph("img/character/ukon_2.png");
	playerGraphHandle[1] = LoadGraph("img/character/Ruby_2.png");
	playerGraphHandle[2] = LoadGraph("img/character/高橋ちなみ_2.png");
	playerGraphHandle[3] = LoadGraph("img/character/白茶犬_1.png");
	playerGraphHandle[4] = LoadGraph("img/character/カラス_1.png");

	aimingGraphHandle = LoadGraph("img/rock.png");

	if (_playerNumber == "character/original/右折ちゃん_Gun/ukon.pmx") { playerPutGraphHandle = playerGraphHandle[0]; }
	if (_playerNumber == "character/original/Ruby_Gun/Ruby.pmx") { playerPutGraphHandle = playerGraphHandle[1]; }
	if (_playerNumber == "character/original/高科ちなみ_Gun/高科ちなみV4.pmx") { playerPutGraphHandle = playerGraphHandle[2]; }
	if (_playerNumber == "character/original/MMD用踊る犬_Gun/白茶犬.pmx") { playerPutGraphHandle = playerGraphHandle[3]; }
	if (_playerNumber == "character/original/MMD用踊るカラス_Gun/MMD用踊るカラス.pmx") { playerPutGraphHandle = playerGraphHandle[4]; }

	deathBlowGraphHandle[0] = LoadGraph("img/player/downDeathBlow.png");
	deathBlowGraphHandle[1] = LoadGraph("img/player/deathBlow.png");
	deathBlowGraphHandle[2] = LoadGraph("img/player/upDeathBlow.png");
	deathBlowGraphHandle[3] = LoadGraph("img/player/startDeathBlow.png");

	deathBlowStartGraphHandle[0] = LoadGraph("img/X.png");
	deathBlowStartGraphHandle[1] = LoadGraph("img/mouse_midle.png");

	LoadDivGraph("img/fire.png", 13, 13, 1, 200, 200, fireGraphHandle, TRUE);
	fireCount = 0;
	alhaCount = 0;
	blendCount = 0;

	LoadDivGraph("img/舞台幕/640/pipo-curtain1.png", 10, 1, 10, 640, 480, openShopGraphHandle, TRUE);
	LoadDivGraph("img/舞台幕/640/pipo-curtain2.png", 18, 1, 18, 640, 480, closeShopGraphHandle, TRUE);

	moneyGraphHamdle = LoadGraph("img/money.png");

	gaugeGraphHandle = LoadGraph("img/togetogegarge/ゲージカバー2.png");
};

void UI::Update(CharacterBase *_player)
{

}

void UI::Draw(CharacterBase *_player, Tower *_tower)
{
	// プレイヤー画像
	DrawRotaGraph(110, (int)(SCREEN_Y / 1.14f), 0.65f, 0.0f, playerIconDownGraphHandle, TRUE);
	DrawRotaGraph(110, (int)(SCREEN_Y / 1.14f), 1.0f, 0.0f, playerPutGraphHandle, TRUE);
	DrawRotaGraph(110, (int)(SCREEN_Y / 1.14f), 0.65f, 0.0f, playerIconGraphHandle, TRUE);

	int dirX = 0;

	// 移動分
	if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_PRESSED || KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000) { dirX = -140; }
	else if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_PRESSED || KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000) { dirX = 120; }
	else { dirX = 0; }

	// 照準の画像
	if (SceneGame::GetStart() && !_player->GetJump() && !SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || MOUSE_INPUT.MousePresed(MOUSE_INPUT_RIGHT) || PAD_INPUT.GetPadInput("1P").Buttons[XINPUT_BUTTON_LEFT_SHOULDER])
		{
			DrawRotaGraph((int)(SCREEN_X / 1.95f) + dirX, (int)(SCREEN_Y / 2), 0.5f, 0.0f, aimingGraphHandle, TRUE);
		}
	}

	// 必殺技ゲージ
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 1.0f, 0.0f, deathBlowGraphHandle[i], TRUE);
	}

	// 必殺技が溜まるゲージ
	DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 0.0f + (_player->GetDeathBlowCount() / 100), 0.0f, deathBlowGraphHandle[2], TRUE);

	// 必殺技が溜まったら使用可能
	if (_player->GetStartDeathBlow())
	{
		// 溜まったことを知らせる
		DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 1.0f, 0.0f, deathBlowGraphHandle[3], TRUE);

		// 各カウント
		fireCount ++;
		if (fireCount >= 13)fireCount = 0;
		alhaCount += 40;
		if (alhaCount >= 250) { alhaCount = 250; blendCount -= 10;}
		if (blendCount <= -50) { blendCount = -50; }
		// 燃えたら半透明
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alhaCount + blendCount);
		DrawRotaGraphF((SCREEN_X / 1.1f), (SCREEN_Y / 1.35f), 2.1f, 0.0f, fireGraphHandle[fireCount], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (SceneChange::GetPadOrKey()) { DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 0.5f, 0.0f, deathBlowStartGraphHandle[0], TRUE); }
		if (!SceneChange::GetPadOrKey()) { DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 0.5f, 0.0f, deathBlowStartGraphHandle[1], TRUE); }
	}
	else
	{
		fireCount = 0;
		alhaCount = 0;
		blendCount = 0;
	}

	// お金袋表示
	DrawRotaGraph(350, 750, 0.1f, 0.0, moneyGraphHamdle, TRUE);

	// プレイヤーの体力画像
	for (int i = 0; i < 10; i++)
	{
		if (_player->GetLife() > i)
		{
			DrawRotaGraph(200 + 50 * i, (int)(SCREEN_Y / 1.05f), 1.1f, 0.0f, playerHeartDownGraphHandle, TRUE);
			DrawRotaGraph(200 + 50 * i, (int)(SCREEN_Y / 1.05f), 1.0f, 0.0f, playerHeartGraphHandle, TRUE);
		}
	}
	for (int i = 10; i < 20; i++)
	{
		if (_player->GetLife() > i)
		{
			DrawRotaGraph(200 + 50 * (i - 10), (int)(SCREEN_Y / 1.1f), 1.1f, 0.0f, playerHeartDownGraphHandle, TRUE);
			DrawRotaGraph(200 + 50 * (i - 10), (int)(SCREEN_Y / 1.1f), 1.0f, 0.0f, playerHeartGraphHandle, TRUE);
		}
	}


	// タワーの体力
	DrawBox((int)SCREEN_X / 3 + 20, 15, (int)SCREEN_X / 3 + 600, 40, GetColor(255, 0, 0), TRUE);
	DrawBox((int)SCREEN_X / 3 + 20, 15, (int)SCREEN_X / 3 + _tower->GetLife() * 6, 40, GetColor(0, 255, 0), TRUE);
	DrawModiGraph(510, 5, 1200, 5, 1200, 45, 510, 45, gaugeGraphHandle, TRUE);
}

void UI::FadeDraw()
{
	// フェードイン フェードアウト
	DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, closeShopGraphHandle[DefenseManager::GetCloseShopEntry()], TRUE);
	DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, openShopGraphHandle[DefenseManager::GetOpenShopEntry()], TRUE);
}

// 削除
void UI::Release()
{
	DeleteGraph(playerHeartDownGraphHandle);
	playerHeartDownGraphHandle = NULL;

	DeleteGraph(playerHeartGraphHandle);
	playerHeartGraphHandle = NULL;

	DeleteGraph(playerIconGraphHandle);
	playerIconGraphHandle = NULL;

	DeleteGraph(playerIconDownGraphHandle);
	playerIconDownGraphHandle = NULL;

	DeleteGraph(aimingGraphHandle);
	aimingGraphHandle = NULL;

	DeleteGraph(moneyGraphHamdle);
	moneyGraphHamdle = NULL;

	DeleteGraph(deathBlowStartGraphHandle[0]);
	deathBlowStartGraphHandle[0] = NULL;
	DeleteGraph(deathBlowStartGraphHandle[1]);
	deathBlowStartGraphHandle[1] = NULL;



	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(playerGraphHandle[i]);
		playerGraphHandle[i] = NULL;
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(deathBlowGraphHandle[i]);
		deathBlowGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 13; i++)
	{
		DeleteGraph(fireGraphHandle[i]);
		fireGraphHandle[i] = NULL;
	}

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(openShopGraphHandle[i]);
		openShopGraphHandle[i] = NULL;
	}
	for (int i = 0; i < 18; i++)
	{
		DeleteGraph(closeShopGraphHandle[i]);
		closeShopGraphHandle[i] = NULL;
	}


	DeleteGraph(gaugeGraphHandle);
	gaugeGraphHandle = NULL;
}