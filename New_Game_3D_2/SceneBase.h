#pragma once

class EnemyManager;
class UI;
class MiniMap;
class ItemManager;
class Stage;
class Tower;
class DefenseManager;
class BackGroundMusic;

class SceneBase
{
public:
	SceneBase() {};
	virtual ~SceneBase() {};

	virtual void Init() = 0;
	virtual SceneBase *Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

protected:
	Camera *camera;
	CharacterBase *player;
	EnemyManager *enemy;
	ItemManager *itemManager;
	Tower *tower;
	DefenseManager *defenseManager;
	UI *ui;
	MiniMap *miniMap;
	BackGroundMusic *bgm;

	int graphHandle;
	int changeCount;
	int gameStartCount;
};