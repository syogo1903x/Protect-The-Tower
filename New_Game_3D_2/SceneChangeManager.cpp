#include "Common.h"

bool SceneChange::isPad = false;
bool SceneChange::isEscape = false;

SceneChange::SceneChange()
{
	isPad = false;
	isEscape = false;
}

SceneChange::~SceneChange()
{
	Release();
}

// 初期化
void SceneChange::Init()
{
	// 一番最初はタイトル
	SetFirstScene(new SceneTitle);
	// キーの初期化
	KEY_INPUT.Init_Key();
	// シーンの初期化
	nowScene->Init();
	// 最初はキーボード状態
	isPad = false;
}

// 更新
void SceneChange::Update()
{
	// キーの更新
	KEY_INPUT.Update_Key();
	// パッドの更新
	PAD_INPUT.Update("1P");
	// マウスの更新
	MOUSE_INPUT.Update();


	// キーが押されたとき
	if (CheckHitKeyAll() == 1 || MOUSE_INPUT.MousePush(MOUSE_INPUT_LEFT) ||
		MOUSE_INPUT.MousePush(MOUSE_INPUT_RIGHT) ||
		MOUSE_INPUT.MousePush(MOUSE_INPUT_MIDDLE)) { isPad = false; }

	// パッドが押されたとき
	if (PAD_INPUT.GetPadInput("1P").ThumbLX <= -10000 || 
		PAD_INPUT.GetPadInput("1P").ThumbLX >= 10000 ||
		PAD_INPUT.GetPadInput("1P").ThumbLY <= -10000 ||
		PAD_INPUT.GetPadInput("1P").ThumbLY >= 10000 || 
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_A) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_B) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_X) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_Y) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_LEFT_SHOULDER) ||
		PAD_INPUT.PadPush("1P", XINPUT_BUTTON_RIGHT_SHOULDER)) { isPad = true; }

	prevScene = nowScene->Update();

	// 過去のシーンが現在のシーンと一致してい無ければ　シーンを切り替える
	if (prevScene != nowScene)
	{
		nowScene = prevScene;
		nowScene->Init();
	}
}

// 解放
void SceneChange::Release()
{
	// 削除
	if (nowScene)
	{
		nowScene->Release();
		delete nowScene;
		nowScene = NULL;
	}
}

// 表示
void SceneChange::Draw()
{
	nowScene->Draw();
}
