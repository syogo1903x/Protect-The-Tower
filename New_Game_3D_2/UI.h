#pragma once
#include "Common.h"

class UI
{
public:
	// コンストラクタ
	UI() {}
	// デストラクタ
	~UI() {}
	// 初期化
	void Init(char *_playerNumber);
	// 更新
	void Update(CharacterBase *_player);
	// 描画
	void Draw(CharacterBase *_player, Tower *_tower);
	// フェード描画
	void FadeDraw();
	// 解放
	void Release();

private:
	// プレイヤー体力画像
	int playerHeartGraphHandle;
	// プレイヤーの下の体力
	int playerHeartDownGraphHandle;
	// プレイヤーアイコン
	int playerIconGraphHandle;
	// プレイヤーの下アイコン
	int playerIconDownGraphHandle;
	// エイム画像
	int aimingGraphHandle;

	// プレイヤー画像
	int playerGraphHandle[5];
	int playerPutGraphHandle;

	// 必殺技ゲージ画像
	int deathBlowGraphHandle[4];
	int deathBlowStartGraphHandle[2];
	int fireGraphHandle[13];
	int fireCount;
	int alhaCount;
	int blendCount;

	// フェード画像
	int openShopGraphHandle[10];
	int closeShopGraphHandle[18];

	// 所持金画像
	int moneyGraphHamdle;

	// タワー体力画像
	int gaugeGraphHandle;
};