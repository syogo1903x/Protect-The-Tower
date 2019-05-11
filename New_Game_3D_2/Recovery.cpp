#include "Common.h"

Recovery::Recovery()
{
}

// �폜
Recovery::~Recovery()
{
	MV1DeleteModel(itemModelHandle);
	itemModelHandle = NULL;
}

// ������
void Recovery::Init(int model)
{
	itemModelHandle = MV1DuplicateModel(model);
	isLost = true;
	itemPos = VGet(0, -200, 0);
	// ��������
	MV1SetDifColorScale(itemModelHandle, GetColorF(1, 0, 0, 1.0f));
	// �傫���O�{
	MV1SetScale(itemModelHandle, VGet(3, 3, 3));
	//
	isGet = false;

	rota = 0;
	// ���ʉ��ǂݍ���
	se = new SoundEffect("Music/SE/powerup03.mp3");
}

// �X�V
void Recovery::ItemUpdate(CharacterBase *_enemy)
{
	// �G���o�����Ă������\��
	if (_enemy->GetLife() > 0)
	{
		isGet = false;
	}

	// �G�����񂾂�\���@���@��]
	if (!_enemy->GetDead())
	{
		rota = 0;
		itemPos = _enemy->GetPos();
		isLost = true;
	}
	else
	{
		// ��]
		rota += 0.25f;
		
		if((int)rota % 2 == 0)itemPos.y += 0.1f;
		else itemPos.y -= 0.1f;

		isLost = false;
	}

	MV1SetRotationXYZ(itemModelHandle, VGet(0, rota, 0));
}
