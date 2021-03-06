#pragma once

class DefenseBase;
class DefenseWall;
class DefenseAtackBall;
class DefenseSoldier;
class DefenseFire;
class DefenseBuyObject;

class Player;
class Enemy;
class MediumBoss;
class Boss;
class CharacterBase;

class SoundEffect;

enum SOUND_EFFECT_DEFENSE
{
	PURCASE,
	CHOICE,
	DECISION,
	INSTALLATION,
	CANSEL,
	ENTRYSHOP,
	CALL_ENTRY,
	CALL_BYE,
};

class DefenseManager
{
public:
	DefenseManager();
	~DefenseManager();

	void Init();
	void Update(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	void Draw();
	void ShopUpdate(CharacterBase *_player);
	void ShopDraw();

	// đú
	void Release();

	
	// Qb^[
	bool GetLetsShop() { return isDefenseShoppingMode; }

	static int GetOpenShopEntry() { return joinShopAnimationCount; }
	static int GetCloseShopEntry() { return godbyeShopAnimationCount; }

private:
	// ŕÖ
	// 
	void ShopFade();
	// Ç\Ś
	void WallDraw();
	// U{[\Ś
	void AttackBallDraw();
	// \Ś
	void FireDraw();
	// şm\Ś
	void SoldierDraw();
	// hqACeĚHP\Ś
	void HpDraw();

	// ÇXV
	void WallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	// U{[XV
	void AttackBallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	// XV
	void FireUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	// şmXV
	void SoldierUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);

	// ŕžXV
	void DescriptionUpdate(CharacterBase *_player);
	// VbvĚÇXV
	void WallShopUpdate(CharacterBase *_player);
	// VbvĚU{[XV
	void AttackBallShopUpdate(CharacterBase *_player);
	// VbvĚXV
	void FireShopUpdate(CharacterBase *_player);
	// VbvĚşmXV
	void SoldierShopUpdate(CharacterBase *_player);

	// hqACeŞČ˘Ěš
	void ShopItemStopSound();

	// ÇĚÝu
	void WallInstallation(int _row, int _col);
	// U{[ĚÝu
	void AttackBallInstallation(int _row, int _col);
	// ĚÝu
	void FireInstallation(int _row, int _col);
	// şmĚÝu
	void SoldierInstallation(int _row, int _col);

	// ŕž\Ś
	void DescriptionDraw();
	// Ç2D\Ś
	void WallDraw2D();
	// U{[2D\Ś
	void AttackBallDraw2D();
	// 2D\Ś
	void FireDraw2D();
	// şm2D\Ś
	void SoldierDraw2D();

	// ¨ŕĚ\Ś
	void ShopMoneyDraw();


	const static int ITEM_MAX = 50;
	int openShopGraphHandle[10];
	int closeShopGraphHandle[18];
	bool isShopEntry;
	static int joinShopAnimationCount;
	static int godbyeShopAnimationCount;

	int openShopAnimationCount;
	int closeShopAnimationCount;


	int wallModelHamdel;
	int atackBallModelHandle;
	int fireModelHandle;
	int soldierModelHandle;
	int soldierBulletModelHandle;
	int buyObject;

	// ÇpĎ
	list<DefenseBase*> defenseWallList;
	list<DefenseBase*> notDefenseWallList;
	list<DefenseBase*>::iterator defenseWallListIter;
	list<DefenseBase*>::iterator notDefenseWallIter;

	// U{[pĎ
	list<DefenseBase*> defenseAtackBallList;
	list<DefenseBase*> notDefenseAtackBallList;
	list<DefenseBase*>::iterator defenseAtackBallListIter;
	list<DefenseBase*>::iterator notDefenseAtackBallIter;

	// UpĎ
	list<DefenseBase*> defenseFireList;
	list<DefenseBase*> notDefenseFireList;
	list<DefenseBase*>::iterator defenseFireListIter;
	list<DefenseBase*>::iterator notDefenseFireIter;

	// şmUpĎ
	list<DefenseBase*> defenseSoldierList;
	list<DefenseBase*> notDefenseSoldierList;
	list<DefenseBase*>::iterator defenseSoldierListIter;
	list<DefenseBase*>::iterator notDefenseSoldierIter;

	DefenseBase *defenseBuyObject;

	bool isDefenseShoppingMode;

	int backGroundGraphHadle;			//
	int woodGraphHamdle;				//
	int buyGraphHandle;					//
	int backGraphHandle;				//
	int mapGraphHandle;					// 
	int mapFrameGraphHandle;			// 
	int backGroundGraphHandle[2];		// 
	int moouseGraphHandle[2];			// 
	int itemFrameGraphHandle;			// 
	int buttonGraphHandle[4];			// 
	int nodeGraphHandle[4];

	// Cgi[p
	int lightHandle;
	int upLightHandle;

	int mouseX;
	int mouseY;
	int mouseSpeed;
	bool isChangeControlor;


	int animation;
	int itemNumber;

	int moneyGraphHandle;
	int numberGraphHandle[10];
	int possessionMoney;

	int wallSizeCount;
	int atackBallSizeCount;
	int fireSizeCount;
	int soldierSizeCount;

	bool isNodeFree[10][5];
	bool isWallNode[10][5];
	bool isAtackBallNode[10][5];
	bool isFireNode[10][5];
	bool isSoldierNode[10][5];

	bool isWall;
	bool isAtackBall;
	bool isFire;
	bool isSoldier;

	//
	int descriptionGraphHandle[2];
	int descriptionCount;
	bool isDescription;

	// č
	const VECTOR SHOP_INIT_POS = VGet(0, 0, 200);
	const int SHOP_LINE = 10;
	const int SHOP_COLUMN = 5;

	const float NODE_LINE = 150.0f;
	const float NODE_COLUMN = 80.0f;
	const int   NODE_DIVISION_LINE = 40;
	const int   NODE_DIVISION_COLUMN = 30;

	// Çpč
	const float WALL_SMALL_ENEMY_RANGE = 1.0f;
	const float WALL_MEDIUM_BOSS_RANGE = 1.0f;
	const float WALL_BOSS_RANGE = 2.5f;
	const float WALL_PLAYER_RANGE = 1.0f;
	const int WALL_SMALL_ENEMY_DAMAGE = 10;
	const int WALL_MEDIUM_BOSS_DAMAGE = 20;
	const int WALL_BOSS_DAMAGE = 30;

	// U{[č
	const float ATACKBALL_SMALL_ENEMY_RANGE = 3.0f;
	const float ATACKBALL_MEDIUM_BOSS_RANGE = 3.0f;
	const float ATACKBALL_BOSS_RANGE = 5.0f;
	const int   ATACKBALL_SMALL_ENEMY_ATACK_DAMAGE = 1;
	const int   ATACKBALL_MEDIUM_BOSS_ATACK_DAMAGE = 2;
	const int   ATACKBALL_BOSS_ATACK_DAMAGE = 4;
	const int   ATACKBALL_SMALL_ENEMY_HIT_DAMAGE = 2;
	const int   ATACKBALL_MEDIUM_BOSS_HIT_DAMAGE = 2;
	const int   ATACKBALL_BOSS_HIT_DAMAGE = 4;

	// pč
	const float FIRE_SMALL_ENEMY_RANGE = 4.0f;
	const float FIRE_MEDIUM_BOSS_RANGE = 4.0f;
	const float FIRE_BOSS_RANGE = 4.0f;
	const int   FIRE_SMALL_ENEMY_ATACK_DAMAGE = 1;
	const int   FIRE_MEDIUM_BOSS_ATACK_DAMAGE = 1;
	const int   FIRE_BOSS_ATACK_DAMAGE = 1;
	const int   FIRE_SMALL_ENEMY_HIT_DAMAGE = 2;
	const int   FIRE_MEDIUM_BOSS_HIT_DAMAGE = 2;
	const int   FIRE_BOSS_HIT_DAMAGE = 2;


	// şmpč
	const float SOLDIER_SMALL_ENEMY_RANGE = 2.0f;
	const float SOLDIER_MEDIUM_BOSS_RANGE = 3.0f;
	const float SOLDIER_BOSS_RANGE = 4.0f;
	const int   SOLDIER_SMALL_ENEMY_ATACK_DAMAGE = 1;
	const int   SOLDIER_MEDIUM_BOSS_ATACK_DAMAGE = 1;
	const int   SOLDIER_BOSS_ATACK_DAMAGE = 1;
	const int   SOLDIER_SMALL_ENEMY_HIT_DAMAGE = 5;
	const int   SOLDIER_MEDIUM_BOSS_HIT_DAMAGE = 5;
	const int   SOLDIER_BOSS_HIT_DAMAGE = 5;

	const float SOLDIER_WITH_IN_RANGE = 9.0f;

	// XeBbNĚXŤ
	const int STICK_LEAN = 10000;
	const int MOUSE_SPEED = 20;

	// Áďŕ
	const int   WALL_MONEY_CONSUMPTION = 100;
	const int   ATACKBALL_MONEY_CONSUMPTION = 200;
	const int   FIRE_MONEY_CONSUMPTION = 400;
	const int   SOLDIER_MONEY_CONSUMPTION = 500;

	// UI
	const int SHOP_X = 1500;
	const int SHOP_X_2 = 100;
	const int SHOP_Y = 700;
	const int SHOP_Y_2 = 400;

	// 
	const int SHOP_BLANK = 100;
	const int SHOP_BLANK_2 = 75;

	const int NODE_BLANK = 20;

	//
	SoundEffect *se[8];

	// VbvĚęîó
	int arrowModelHandle;
};