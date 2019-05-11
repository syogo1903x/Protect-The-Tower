#pragma once
#include "Common.h"

using namespace std;

struct GunShot 
{
	VECTOR pos;
	VECTOR dir;
	int modelHandle;
	bool isActive;
	float life;
};


class Shot
{
public:
	Shot();
	~Shot();

	void CreateShot(int _creater);
	void BulletShot(VECTOR _dir, VECTOR _pos);
	void OneBulletPlay();
	void BulletPlay();

	void Draw();

	// ゲッター
	// 玉の数を取得してそのPositionを返す
	const list<GunShot*>::iterator &GetItr() { return itr; }

	// 
	//const bool &GetActive()
	//{
	//	// たまが出ていれば
	//	for (itr = bullet.begin(); itr != bullet.end(); itr++)
	//	{
	//		return (*itr)->isActive;
	//	}
	//}


	const list<GunShot*> &GetShot() { return bullet; }

private:
	GunShot *bul[50];
	list<GunShot*> bullet;
	list<GunShot*>::iterator itr;

	list<GunShot*> notBullet;
	list<GunShot*>::iterator notItr;


	int modelHandle;

	VECTOR velocity;
	int bulletCount;
	int bukketNumber;

	SoundEffect *se;
};