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
	MiniMap();
	~MiniMap();

	void Init();
	void UpdatePlayerMap(CharacterBase * _player, Tower * _tower);
	void UpdateSmall(CharacterBase * _enemy1, int i);
	void UpdateMedium(CharacterBase * _enemy2, int i);
	void UpdateBoss(CharacterBase * _enemy3, int i);
	void Draw();
	void MenuDraw();
	void Release();



private:
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

	float playerRota;

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