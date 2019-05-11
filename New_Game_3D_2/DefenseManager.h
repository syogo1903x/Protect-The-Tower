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

	// ���
	void Release();

	
	// �Q�b�^�[
	bool GetLetsShop() { return isDefenseShoppingMode; }

	static int GetOpenShopEntry() { return joinShopAnimationCount; }
	static int GetCloseShopEntry() { return godbyeShopAnimationCount; }

private:
	// ���������֐�
	// 
	void ShopFade();
	// �ǃ��X�g������
	void WallInit();
	// �ǃ��X�g������
	void AtackBallInit();
	// �ǃ��X�g������
	void FireInit();
	// �ǃ��X�g������
	void SoldierInit();

	// �Ǖ\��
	void WallDraw();
	// �U���{�[���\��
	void AttackBallDraw();
	// ���\��
	void FireDraw();
	// ���m�\��
	void SoldierDraw();
	// �h�q�A�C�e����HP�\��
	void HpDraw();
	// ��HP
	void WallHp();
	// �U���{�[��HP
	void AttackBallHp();
	// ��HP
	void FireHp();
	// ���mHP
	void SoldierHp();

	// �ǍX�V
	void WallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	// �U���{�[���X�V
	void AttackBallUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	// ���X�V
	void FireUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);
	// ���m�X�V
	void SoldierUpdate(CharacterBase *_player, CharacterBase *_small, CharacterBase *_medium, CharacterBase *_boss);

	// �����X�V
	void DescriptionUpdate(CharacterBase *_player);
	// �V���b�v�̕ǍX�V
	void WallShopUpdate(CharacterBase *_player);
	// �V���b�v�̍U���{�[���X�V
	void AttackBallShopUpdate(CharacterBase *_player);
	// �V���b�v�̉��X�V
	void FireShopUpdate(CharacterBase *_player);
	// �V���b�v�̕��m�X�V
	void SoldierShopUpdate(CharacterBase *_player);

	// �h�q�A�C�e�����Ȃ����̉�
	void ShopItemStopSound();

	// �ǂ̐ݒu
	void WallInstallation(int _row, int _col);
	// �U���{�[���̐ݒu
	void AttackBallInstallation(int _row, int _col);
	// ���̐ݒu
	void FireInstallation(int _row, int _col);
	// ���m�̐ݒu
	void SoldierInstallation(int _row, int _col);

	// �p�b�h�ƃ}�E�X�̐؂�ւ�
	void PadOrMouseChange();

	// �����\��
	void DescriptionDraw();
	// ��2D�\��
	void WallDraw2D();
	// �U���{�[��2D�\��
	void AttackBallDraw2D();
	// ��2D�\��
	void FireDraw2D();
	// ���m2D�\��
	void SoldierDraw2D();

	// �����̕\��
	void ShopMoneyDraw();

	// �h�q�A�C�e���̍ő吔
	const static int ITEM_MAX = 50;
	// �J�X���A�j���[�V����
	int openShopGraphHandle[10];
	// �X���A�j���[�V����
	int closeShopGraphHandle[18];
	// �V���b�v�ɓ������t���O
	bool isShopEntry;
	// ���X���A�j���[�V�����J�E���g
	static int joinShopAnimationCount;
	// �ޓX���A�j���[�V�����J�E���g
	static int godbyeShopAnimationCount;

	// �J�X���A�j���[�V�����J�E���g
	int openShopAnimationCount;
	// �X���A�j���[�V�����J�E���g
	int closeShopAnimationCount;

	// �ǃ��f��
	int wallModelHamdel;
	// �U���{�[�����f��
	int atackBallModelHandle;
	// �����f��
	int fireModelHandle;
	// ���m���f��
	int soldierModelHandle;
	// ���m�̒e���f��
	int soldierBulletModelHandle;
	// ���X���f��
	int buyObject;

	// �Ǘp�ϐ�
	list<DefenseBase*> defenseWallList;
	list<DefenseBase*> notDefenseWallList;
	list<DefenseBase*>::iterator defenseWallListIter;
	list<DefenseBase*>::iterator notDefenseWallIter;

	// �U���{�[���p�ϐ�
	list<DefenseBase*> defenseAtackBallList;
	list<DefenseBase*> notDefenseAtackBallList;
	list<DefenseBase*>::iterator defenseAtackBallListIter;
	list<DefenseBase*>::iterator notDefenseAtackBallIter;

	// ���U���p�ϐ�
	list<DefenseBase*> defenseFireList;
	list<DefenseBase*> notDefenseFireList;
	list<DefenseBase*>::iterator defenseFireListIter;
	list<DefenseBase*>::iterator notDefenseFireIter;

	// ���m�U���p�ϐ�
	list<DefenseBase*> defenseSoldierList;
	list<DefenseBase*> notDefenseSoldierList;
	list<DefenseBase*>::iterator defenseSoldierListIter;
	list<DefenseBase*>::iterator notDefenseSoldierIter;

	// ���X���f��
	DefenseBase *defenseBuyObject;

	// �h�q�A�C�e���𔃂���Ԃɂ���t���O
	bool isDefenseShoppingMode;

	int backGroundGraphHadle;			// �w�i
	int woodGraphHamdle;				// �؉摜
	int buyGraphHandle;					// �����摜
	int backGraphHandle;				// �߂�摜
	int mapGraphHandle;					// �}�b�v�摜 
	int mapFrameGraphHandle;			// �}�b�v�ɂ���t���[���摜
	int moouseGraphHandle[2];			// �}�E�X�摜
	int itemFrameGraphHandle;			// �A�C�e���摜
	int buttonGraphHandle[4];			// �{�^���̉摜
	int nodeGraphHandle[4];				// �m�[�h�摜

	// ���C�g�i�[�p�ϐ�
	int lightHandle;
	int upLightHandle;

	// �}�E�X�ϐ�
	int mouseX;
	int mouseY;
	int mouseSpeed;
	bool isChangeControlor;

	// �A�j���[�V����
	int animation;
	int itemNumber;
	// �������ϐ�
	int moneyGraphHandle;
	int numberGraphHandle[10];
	int possessionMoney;

	// �e�A�C�e���������J�E���g
	int wallSizeCount;
	int atackBallSizeCount;
	int fireSizeCount;
	int soldierSizeCount;

	// �h�q�A�C�e���m�[�h
	bool isNodeFree[10][5];
	bool isWallNode[10][5];
	bool isAtackBallNode[10][5];
	bool isFireNode[10][5];
	bool isSoldierNode[10][5];

	// �e�A�C�e����ԃt���O
	bool isWall;
	bool isAtackBall;
	bool isFire;
	bool isSoldier;

	// �����p�ϐ�
	int descriptionGraphHandle[2];
	int descriptionCount;
	bool isDescription;

	// ���ʉ�
	SoundEffect *se[8];

	// �V���b�v�̏ꏊ���
	int arrowModelHandle;

	// �萔
	const VECTOR SHOP_INIT_POS = VGet(0, 0, 200);						// ���X�����ʒu
	const int SHOP_LINE = 10;											// ��
	const int SHOP_COLUMN = 5;											// �c

	const float NODE_LINE = 150.0f;
	const float NODE_COLUMN = 80.0f;
	const int   NODE_DIVISION_LINE = 40;
	const int   NODE_DIVISION_COLUMN = 30;

	// �Ǘp�萔
	const float WALL_SMALL_ENEMY_RANGE = 1.0f;
	const float WALL_MEDIUM_BOSS_RANGE = 1.0f;
	const float WALL_BOSS_RANGE = 2.5f;
	const float WALL_PLAYER_RANGE = 1.0f;
	const int WALL_SMALL_ENEMY_DAMAGE = 10;
	const int WALL_MEDIUM_BOSS_DAMAGE = 20;
	const int WALL_BOSS_DAMAGE = 30;

	// �U���{�[���萔
	const float ATACKBALL_SMALL_ENEMY_RANGE = 3.0f;		
	const float ATACKBALL_MEDIUM_BOSS_RANGE = 3.0f;		
	const float ATACKBALL_BOSS_RANGE = 5.0f;			
	const int   ATACKBALL_SMALL_ENEMY_ATACK_DAMAGE = 1;	
	const int   ATACKBALL_MEDIUM_BOSS_ATACK_DAMAGE = 2;	
	const int   ATACKBALL_BOSS_ATACK_DAMAGE = 4;		
	const int   ATACKBALL_SMALL_ENEMY_HIT_DAMAGE = 2;	
	const int   ATACKBALL_MEDIUM_BOSS_HIT_DAMAGE = 2;	
	const int   ATACKBALL_BOSS_HIT_DAMAGE = 4;			

	// ���p�萔
	const float FIRE_SMALL_ENEMY_RANGE = 4.0f;			
	const float FIRE_MEDIUM_BOSS_RANGE = 4.0f;			
	const float FIRE_BOSS_RANGE = 4.0f;					
	const int   FIRE_SMALL_ENEMY_ATACK_DAMAGE = 1;		
	const int   FIRE_MEDIUM_BOSS_ATACK_DAMAGE = 1;		
	const int   FIRE_BOSS_ATACK_DAMAGE = 1;				
	const int   FIRE_SMALL_ENEMY_HIT_DAMAGE = 2;		
	const int   FIRE_MEDIUM_BOSS_HIT_DAMAGE = 2;		
	const int   FIRE_BOSS_HIT_DAMAGE = 2;				


	// ���m�p�萔
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

	// �X�e�B�b�N�̌X��
	const int STICK_LEAN = 10000;						
	const int MOUSE_SPEED = 20;							

	// �����
	const int   WALL_MONEY_CONSUMPTION = 100;			
	const int   ATACKBALL_MONEY_CONSUMPTION = 200;		
	const int   FIRE_MONEY_CONSUMPTION = 400;			
	const int   SOLDIER_MONEY_CONSUMPTION = 500;		

	// UI
	const int SHOP_X = 1500;
	const int SHOP_X_2 = 100;	
	const int SHOP_Y = 700;		
	const int SHOP_Y_2 = 400;	

	// �␳
	const int SHOP_BLANK = 100;
	const int SHOP_BLANK_2 = 75;

	const int NODE_BLANK = 20;
};