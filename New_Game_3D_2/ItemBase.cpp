#include "Common.h"

ItemBase::ItemBase()
{
	radius = 3;

}

ItemBase::~ItemBase()
{



}

void ItemBase::Update(CharacterBase * _enemy)
{
	ItemUpdate(_enemy);

	MV1SetPosition(itemModelHandle, itemPos);
}

void ItemBase::UpdatePlayerToItem(CharacterBase * _player)
{
	// �����蔻����ɂ���Ί���Ă���
	if (HitCheck::HitCheckCirclePlayerToItemAttract(_player, this, 10.0f))
	{
		VECTOR tmpPos = VSub(_player->GetPos(), itemPos);

		itemPos = VAdd(itemPos, VScale(VNorm(tmpPos), 5));
	}

	// ���ʉ��Đ�
	if (isGet) se->OnePlaySoundEffect();
	else se->StopSoundEffect();
}

void ItemBase::Draw()
{
	// �Ƃ�Δ�\��
	if (!isLost && !isGet)
	{
		MV1DrawModel(itemModelHandle);
	}
}

// ���
void ItemBase::Release()
{
	MV1DeleteModel(itemModelHandle);
	itemModelHandle = NULL;

	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		se = NULL;
		delete(se);
	}
}
