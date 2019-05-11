#include "Common.h"

SceneDemo::SceneDemo()
{

}

SceneDemo::~SceneDemo()
{

}

void SceneDemo::Init()
{
	// 動画の読み込み
	videoMovieHandle = LoadGraph("video/movie.mp4");
	circleGraphHandle = LoadGraph("img/circle.png");

	count = 0;
	time = 1;

	demoPos = VGet(2000, 400, 0);
	isPush = false;

	// フェードイン フェードアウト 初期化
	FADE.Init();
	alha = 0;
}

SceneBase * SceneDemo::Update()
{
	// 時間を測定
	count++;
	if (count >= 60) 
	{
		time++; 
		count = 0; 
	}

	if (count > 0 && count < 30) { alha += 8; }
	if (count > 30 && count <= 60) { alha -= 8; }

	demoPos.x -= 10;

	if (demoPos.x <= -1000) { demoPos.x = 2000; }

	PlayMovieToGraph(videoMovieHandle);

	// キーが押されればメニュー移動
	if (KEY_INPUT.GetKey(KEY_INPUT_RETURN) == KEY_ON || PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT))
	{
		isPush = true;
		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");
	}

	// 時間いっぱいになったらタイトル移動
	if (time >= 15)
	{
		isPush = false;
		// フェードアウトが完了したかの条件分岐
		FADE.TermsFadeOut_Play("Fast");
	}

	// フェードアウトが終われば変更
	if (FADE.FadeOutEnd() && !isPush)
	{
		// 解放
		Release();
		// 切り替え
		return new SceneTitle;
	}

	// フェードアウトが終わりかつボタンが押されれば変更
	if (FADE.FadeOutEnd() && isPush)
	{
		// 解放
		Release();
		// 切り替え
		return new SceneMenu;
	}

	// エスケープが押されれば終了
	if (KEY_INPUT.GetKey(KEY_INPUT_ESCAPE) == KEY_ON)
	{
		SceneChange::SetEscape(true);
	}

	return this;
}

void SceneDemo::Draw()
{
	// ビデオ表示
	DrawGraph(0, 0, videoMovieHandle, FALSE);

	SetFontSize(DEFAULT_FONT_SIZE * 3);
	DrawFormatString(1500, 50, GetColor(255, 0, 0), "%d", time);
	SetDrawBright(255, 0, 0);
	DrawCircleGauge(1515, 75, count * 1.8f, circleGraphHandle, 0);
	SetDrawBright(255, 255, 255);

	SetFontSize(DEFAULT_FONT_SIZE * 6);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alha);
	DrawFormatStringF(600, 400, GetColor(255, 0, 0), "デモムービー");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetFontSize(DEFAULT_FONT_SIZE * 3);
	if (SceneChange::GetPadOrKey()) { DrawFormatStringF(700, 850, GetColor(255, 0, 0), "Aボタンを押してね"); }
	else { DrawFormatStringF(700, 850, GetColor(255, 0, 0), "エンター/右クリックを押してね"); }
	SetFontSize(DEFAULT_FONT_SIZE);

	// フェードイン
	FADE.FadeIn_Play();
	// フェードアウト
	FADE.FadeOut_Play();
}

void SceneDemo::Release()
{
	DeleteGraph(videoMovieHandle);
	videoMovieHandle = NULL;

	DeleteGraph(circleGraphHandle);
	circleGraphHandle = NULL;

}
