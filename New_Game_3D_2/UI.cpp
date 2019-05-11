#include "UI.h"

void UI::Init(char *_playerNumber)
{
	playerHeartDownGraphHandle = LoadGraph("img/player/_heart.png");
	playerHeartGraphHandle = LoadGraph("img/player/heart.png");
	playerIconGraphHandle = LoadGraph("img/player/icon.png");
	playerIconDownGraphHandle = LoadGraph("img/player/iconDown.png");

	playerGraphHandle[0] = LoadGraph("img/character/ukon_2.png");
	playerGraphHandle[1] = LoadGraph("img/character/Ruby_2.png");
	playerGraphHandle[2] = LoadGraph("img/character/�������Ȃ�_2.png");
	playerGraphHandle[3] = LoadGraph("img/character/������_1.png");
	playerGraphHandle[4] = LoadGraph("img/character/�J���X_1.png");

	aimingGraphHandle = LoadGraph("img/rock.png");

	if (_playerNumber == "character/original/�E�܂����_Gun/ukon.pmx") { playerPutGraphHandle = playerGraphHandle[0]; }
	if (_playerNumber == "character/original/Ruby_Gun/Ruby.pmx") { playerPutGraphHandle = playerGraphHandle[1]; }
	if (_playerNumber == "character/original/���Ȃ��Ȃ�_Gun/���Ȃ��Ȃ�V4.pmx") { playerPutGraphHandle = playerGraphHandle[2]; }
	if (_playerNumber == "character/original/MMD�p�x�錢_Gun/������.pmx") { playerPutGraphHandle = playerGraphHandle[3]; }
	if (_playerNumber == "character/original/MMD�p�x��J���X_Gun/MMD�p�x��J���X.pmx") { playerPutGraphHandle = playerGraphHandle[4]; }

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

	LoadDivGraph("img/���䖋/640/pipo-curtain1.png", 10, 1, 10, 640, 480, openShopGraphHandle, TRUE);
	LoadDivGraph("img/���䖋/640/pipo-curtain2.png", 18, 1, 18, 640, 480, closeShopGraphHandle, TRUE);

	moneyGraphHamdle = LoadGraph("img/money.png");

	gaugeGraphHandle = LoadGraph("img/togetogegarge/�Q�[�W�J�o�[2.png");
};

void UI::Update(CharacterBase *_player)
{

}

void UI::Draw(CharacterBase *_player, Tower *_tower)
{
	// �v���C���[�摜
	DrawRotaGraph(110, (int)(SCREEN_Y / 1.14f), 0.65f, 0.0f, playerIconDownGraphHandle, TRUE);
	DrawRotaGraph(110, (int)(SCREEN_Y / 1.14f), 1.0f, 0.0f, playerPutGraphHandle, TRUE);
	DrawRotaGraph(110, (int)(SCREEN_Y / 1.14f), 0.65f, 0.0f, playerIconGraphHandle, TRUE);

	int dirX = 0;

	// �ړ���
	if (KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_PRESSED || KEY_INPUT.GetKey(KEY_INPUT_A) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000) { dirX = -140; }
	else if (KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_PRESSED || KEY_INPUT.GetKey(KEY_INPUT_D) == KEY_ON || PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000) { dirX = 120; }
	else { dirX = 0; }

	// �Ə��̉摜
	if (SceneGame::GetStart() && !_player->GetJump() && !SceneGame::GetGameClear() && !SceneGame::GetGameOver())
	{
		if (MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) || MOUSE_INPUT.MousePresed(MOUSE_INPUT_RIGHT) || PAD_INPUT.GetPadInput("1P").Buttons[XINPUT_BUTTON_LEFT_SHOULDER])
		{
			DrawRotaGraph((int)(SCREEN_X / 1.95f) + dirX, (int)(SCREEN_Y / 2), 0.5f, 0.0f, aimingGraphHandle, TRUE);
		}
	}

	// �K�E�Z�Q�[�W
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 1.0f, 0.0f, deathBlowGraphHandle[i], TRUE);
	}

	// �K�E�Z�����܂�Q�[�W
	DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 0.0f + (_player->GetDeathBlowCount() / 100), 0.0f, deathBlowGraphHandle[2], TRUE);

	// �K�E�Z�����܂�����g�p�\
	if (_player->GetStartDeathBlow())
	{
		// ���܂������Ƃ�m�点��
		DrawRotaGraph((int)(SCREEN_X / 1.1f), (int)(SCREEN_Y / 1.15f), 1.0f, 0.0f, deathBlowGraphHandle[3], TRUE);

		// �e�J�E���g
		fireCount ++;
		if (fireCount >= 13)fireCount = 0;
		alhaCount += 40;
		if (alhaCount >= 250) { alhaCount = 250; blendCount -= 10;}
		if (blendCount <= -50) { blendCount = -50; }
		// �R�����甼����
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

	// �����ܕ\��
	DrawRotaGraph(350, 750, 0.1f, 0.0, moneyGraphHamdle, TRUE);

	// �v���C���[�̗͉̑摜
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


	// �^���[�̗̑�
	DrawBox((int)SCREEN_X / 3 + 20, 15, (int)SCREEN_X / 3 + 600, 40, GetColor(255, 0, 0), TRUE);
	DrawBox((int)SCREEN_X / 3 + 20, 15, (int)SCREEN_X / 3 + _tower->GetLife() * 6, 40, GetColor(0, 255, 0), TRUE);
	DrawModiGraph(510, 5, 1200, 5, 1200, 45, 510, 45, gaugeGraphHandle, TRUE);
}

void UI::FadeDraw()
{
	// �t�F�[�h�C�� �t�F�[�h�A�E�g
	DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, closeShopGraphHandle[DefenseManager::GetCloseShopEntry()], TRUE);
	DrawModiGraph(0, 0, SCREEN_X, 0, SCREEN_X, SCREEN_Y, 0, SCREEN_Y, openShopGraphHandle[DefenseManager::GetOpenShopEntry()], TRUE);
}

// �폜
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