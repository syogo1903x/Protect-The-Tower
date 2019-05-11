#include "Common.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() < 0)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する
	SetUseDirect3DVersion(DX_DIRECT3D_9);


	// 画面をウィンドウモードにする
	ChangeWindowMode(TRUE);
	//ChangeWindowMode(FALSE);

	// 画面モードのセット
	SetGraphMode(SCREEN_X, SCREEN_Y, 16);

	// うしろ
	SetDrawScreen(DX_SCREEN_BACK);

	// マウス非表示
	SetMouseDispFlag(FALSE);
	// マウスカーソルのウィンドウ外への移動を禁止
	SetValidMousePointerWindowOutClientAreaMoveFlag(FALSE);

	// 生成
	SceneChange *scene = new SceneChange();
	// 初期化
	scene->Init();

	// エフェクトの初期化
	EFFECT.Init();

	// テキスト変更読み込み
	ChangeTextFont();

	// けいおんフォント
	TextFontDraw(3);

	// エラーが出るかエスケープが押されるまでループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !SceneChange::GetEscape())
	{
		// Windowsのご機嫌取り関数
		ProcessMessage();

		// 画面を真っ黒に更新
		ClearDrawScreen();

		// 更新
		scene->Update();

		// 描画
		scene->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

	}

	// テキスト削除
	TextRelease();

	// Effekseerを終了する。
	Effkseer_End();

	// DXライブラリの設定を戻す
	RefreshDxLibDirect3DSetting();

	// 開放
	scene->Release();

	// DdxLibの終了
	DxLib_End();
	return 0;
}