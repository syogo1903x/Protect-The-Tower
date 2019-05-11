#include "Common.h"

Shader::Shader()
{
}

Shader::~Shader()
{

}

void Shader::Init()
{
	pixelShaderHandle = LoadVertexShader("VertexShader.vso");
	vertexShaderHandle = LoadVertexShader("PixelShader.pso");

	// プログラマブルシェーダーモデル２．０が使用できない場合はエラーを表示して終了
	if (GetValidShaderVersion() < 200)
	{
		// エラー表示
		DrawString(0, 0, "プログラマブルシェーダー２．０が使用できない環境のようです", GetColor(255, 255, 255));

		// キー入力待ち
		WaitKey();

		// ＤＸライブラリの後始末
		DxLib_End();
	}

	// モデルの描画にオリジナルシェーダーを使用する設定をＯＮにする
	MV1SetUseOrigShader(TRUE);

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(vertexShaderHandle);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(pixelShaderHandle);

	// 標準ライトをオフにする
	SetLightEnable(FALSE);

	// ディレクショナルライトを作成する
	directionalLightHandle = CreateDirLightHandle(VGet(-1.0f, -1.0f, 0.0f));

	// ポイントライトハンドルを作成する
	pointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 1000.0f, 0.86f, 0.0000f, 0.0000f);

	// スポットライトを作成する
	spotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.7f, 0.6f, 1000.0f, 0.391586f, 0.001662f, 0.0f);

	// スポットライトのアンビエントカラーを無効にする
	SetLightAmbColorHandle(spotLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// スポットライトのディフューズカラーを緑にする
	SetLightDifColorHandle(spotLightHandle, GetColorF(0.0f, 1.0f, 0.0f, 0.0f));

	lightAngle = 0;

}


void Shader::Update()
{

}

void Shader::Release()
{
	// ディレクショナルライトの削除
	DeleteLightHandle(directionalLightHandle);


	// 読み込んだ頂点シェーダーの削除
	DeleteShader(vertexShaderHandle);

	// 読み込んだピクセルシェーダーの削除
	DeleteShader(pixelShaderHandle);
}
