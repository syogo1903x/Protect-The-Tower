#pragma once
#include <DxLib.h>

class CharacterBase;
class SoundEffect;

class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

	virtual void Update(CharacterBase *_enemy);
	virtual void UpdatePlayerToItem(CharacterBase *_player);
	virtual void Draw();
	virtual void Release();

	virtual void Init(int model) = 0;
	virtual void ItemUpdate(CharacterBase *_enemy) = 0;

	// セッター
	// ポジションセット
	void SetPos(const VECTOR _pos) { itemPos = _pos; }
	// 半径セット
	void SetRadius(const float _radius) { radius = _radius; }
	// なくなっている
	void SetLost(const bool _isSet) { isLost = _isSet; }
	// なくなっている
	void SetItemGet(const bool _isSet) { isGet = _isSet; }

	// ゲッター
	// ポジション取得
	const VECTOR &GetPos() const { return itemPos; }
	// 半径取得
	const float &GetRadius() const { return radius; }
	// モデル取得
	const int &GetModel() const { return itemModelHandle; }
	// なくなっているかの取得
	const bool &GetLost() const { return isLost; }
	// とった取得
	const bool &GetItemGet() const { return isGet; }

protected:
	int itemModelHandle;
	bool isLost;
	bool isGet;

	VECTOR itemPos;
	float radius;

	SoundEffect *se;

};