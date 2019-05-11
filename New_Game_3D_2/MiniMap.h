#pragma once

class CharacterBase;
class Player;
class Enemy;
class MediumBoss;
class Boss;
class Tower;

class MiniMap
{
public:
	// コンストラクタ
	MiniMap();
	// デストラクタ
	~MiniMap();

	// 初期化
	void Init();
	// プレイヤー更新
	void UpdatePlayerMap(CharacterBase * _player, Tower * _tower);
	// 雑魚的更新
	void UpdateSmall(CharacterBase * _enemy1, int i);
	// 中ボス更新
	void UpdateMedium(CharacterBase * _enemy2, int i);
	// ボス更新
	void UpdateBoss(CharacterBase * _enemy3, int i);
	// 描画
	void Draw();
	// 説明画像
	void MenuDraw();
	// 解放
	void Release();



private:
	// ミニマップ画像
	int miniMapGraphHandle;
	int playerGraphHandle;
	int enemyGraphHandle[3];
	int enemyBackGraphHandle[3];
	int towerGraphHandle;
	int itemShopGraphHandle;

	VECTOR playerPos;
	VECTOR enemyPos1[20];
	VECTOR enemyPos2[8];
	VECTOR enemyPos3[4];
	bool isEnemy1[20];
	bool isEnemy2[8];
	bool isEnemy3[4];
	VECTOR towerPos;

	// プレイヤー回転
	float playerRota;

	// 定数
	const int MINIMAP_X = 200;
	const float MINIMAP_Y = 500;
	const float MINIMAP_CHARACTER_Y = 562.5f;
	const float MINIMAP_Y_UP_LIMIT = 660;
	const float MINIMAP_Y_DOWN_LIMIT = 350;

	const int MENU_MINIMAP_X = 950;
	const float MENU_MINIMAP_Y = 500;
	const float MENU_MINIMAP_CHARACTER_Y = 562.5f;
	const float MENU_MINIMAP_X_UP_LIMIT = 1300;
	const float MENU_MINIMAP_X_DOWN_LIMIT = 700;
	const float MENU_MINIMAP_Y_UP_LIMIT = 780;
	const float MENU_MINIMAP_Y_DOWN_LIMIT = 200;


};