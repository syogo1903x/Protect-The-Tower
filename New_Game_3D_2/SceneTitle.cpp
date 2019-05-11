#include "Common.h"

SceneTitle::SceneTitle()
{
	// ロード時に効果音の削除
	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		delete(se);
		se = NULL;
	}
}

SceneTitle::~SceneTitle()
{
	Release();
}

void SceneTitle::Init()
{
	padInputSize = GetJoypadNum();

	// BGM読み込み
	bgm = new BackGroundMusic("Music/BGM/titleBGM.mp3");

	// 効果音読み込み
	se = new SoundEffect("Music/SE/decision9.mp3");

	graphHandle = LoadGraph("img/title1.png");
	LoadDivGraph("img/flan.png", 2, 2, 1, 32, 32, moouseGraphHandle, TRUE);

	titleGraphHandle[0] = LoadGraph("img/title_char.png");
	titleGraphHandle[1] = LoadGraph("img/ground.png");

	titleModelHandle = MV1LoadModel("skyDome/Skydome_CC6/Dome_CC601.pmx");
	MV1SetPosition(titleModelHandle, VGet(0, -700, 0));

	titlePushGraphHandle[0] = LoadGraph("img/push2.png");
	titlePushGraphHandle[1] = LoadGraph("img/push.png");

	animation = 0;
	animationCount = 0;
	isAlhaBlend = true;
	rotate = 0;

	rogoGraphHandle = LoadGraph("img/rogo2.png");

	isDemo = false;
	// フェードイン フェードアウト 初期化
	FADE.Init();

	// BGM再生
	bgm->PlayBackGroundMusic();

	// カメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0, 50, 100), VGet(0, 0, 0));
}

SceneBase * SceneTitle::Update()
{
	GetMousePoint(&mouseX, &mouseY);
	animation++;

	// スカイドームの回転
	rotate += 0.0005f;
	
	// 点滅
	if (animation % 20 == 0)
	{
		isAlhaBlend = !isAlhaBlend;
	}

	if (isAlhaBlend)
	{
		animationCount = 255;
	}
	else
	{
		animationCount = 0;
	}

	// キーが押されたら
	if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
	{
		// 効果音再生
		se->PlaySoundEffect();

		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");

		isDemo = true;
	}

	if (animation >= 300 || KEY_INPUT.GetKey(KEY_INPUT_BACK) == KEY_ON)
	{
		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");

		isDemo = false;
	}


	// フェードアウトが終われば変更
	if (FADE.FadeOutEnd() && isDemo)
	{
		isTitlePass = true;
		// 解放
		Release();
		// 切り替え
		return new SceneMenu;
	}

	// フェードアウトが終われば変更
	if (FADE.FadeOutEnd() && !isDemo)
	{
		isTitlePass = true;
		// 解放
		Release();
		// 切り替え
		return new SceneDemo;
	}

	// エスケープが押されれば終了
	if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON)
	{
		SceneChange::SetEscape(true);
	}

	return this;
}

void SceneTitle::Draw()
{
	MV1SetRotationXYZ(titleModelHandle, VGet(0, rotate, 0));
	MV1DrawModel(titleModelHandle);
	
	DrawGraph(0, 0, titleGraphHandle[1], TRUE);

	DrawRotaGraph(SCREEN_X / 3, (int)(SCREEN_Y / 2.5f), 1.f, 0.0f, rogoGraphHandle, TRUE, TRUE);
	DrawRotaGraph(SCREEN_X / 3, (int)(SCREEN_Y / 2.5f), 0.8f, 0.0f, graphHandle, TRUE);
	DrawGraph(0, 0, titleGraphHandle[0], TRUE);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, animationCount);

	// パッドがついていたら
	if (SceneChange::GetPadOrKey())
	{
		DrawRotaGraphF(SCREEN_X / 3.f, SCREEN_Y / 1.15f, 1.f, 0.0f, titlePushGraphHandle[0], TRUE);
	}
	// キー状態
	else
	{
		DrawRotaGraphF(SCREEN_X / 3.f, SCREEN_Y / 1.15f, 1.f, 0.0f, titlePushGraphHandle[1], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DrawRotaGraph(mouseX, mouseY, 1, 0, moouseGraphHandle[animation % 2], TRUE);

	// フェードアウト
	FADE.FadeOut_Play();

	if (isTitlePass)
	{
		// フェードイン
		FADE.FadeIn_Play();
	}
	else
	{
		FADE.TitleFadeIn_Play();
	}
}

void SceneTitle::Release()
{
	DeleteGraph(graphHandle);
	graphHandle = NULL;

	MV1DeleteModel(titleModelHandle);
	titleModelHandle = NULL;

	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(moouseGraphHandle[i]);
		moouseGraphHandle[i] = NULL;

		DeleteGraph(titleGraphHandle[i]);
		titleGraphHandle[i] = NULL;

		DeleteGraph(titlePushGraphHandle[i]);
		titlePushGraphHandle[i] = NULL;

	}


	DeleteGraph(rogoGraphHandle);
	rogoGraphHandle = NULL;

	if (bgm)
	{
		bgm->StopBackGroundMusic();
		bgm->Release();
		delete(bgm);
		bgm = NULL;
	}
}
