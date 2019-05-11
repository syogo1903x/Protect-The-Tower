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

	// �Z�b�^�[
	// �|�W�V�����Z�b�g
	void SetPos(const VECTOR _pos) { itemPos = _pos; }
	// ���a�Z�b�g
	void SetRadius(const float _radius) { radius = _radius; }
	// �Ȃ��Ȃ��Ă���
	void SetLost(const bool _isSet) { isLost = _isSet; }
	// �Ȃ��Ȃ��Ă���
	void SetItemGet(const bool _isSet) { isGet = _isSet; }

	// �Q�b�^�[
	// �|�W�V�����擾
	const VECTOR &GetPos() const { return itemPos; }
	// ���a�擾
	const float &GetRadius() const { return radius; }
	// ���f���擾
	const int &GetModel() const { return itemModelHandle; }
	// �Ȃ��Ȃ��Ă��邩�̎擾
	const bool &GetLost() const { return isLost; }
	// �Ƃ����擾
	const bool &GetItemGet() const { return isGet; }

protected:
	int itemModelHandle;
	bool isLost;
	bool isGet;

	VECTOR itemPos;
	float radius;

	SoundEffect *se;

};