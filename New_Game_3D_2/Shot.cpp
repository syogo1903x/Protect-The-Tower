#include "Shot.h"

// �R���X�g���N�^
Shot::Shot()
{
	// �v���C���[�Œe�̃��f����ς���
	if (SceneMenu::GetPlayer() == "character/original/Ruby_Gun/Ruby.pmx")
	{
		modelHandle = MV1LoadModel("Item/�p���[�X�g�[��/�p���[�X�g�[��.pmx");
	}
	else
	{
		modelHandle = MV1DuplicateModel(NowLoad::GetModelHandle(MODEL_HANDLE::BULLET_SHOT));
		MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));
	}

	se = new SoundEffect("Music/SE/short_punch1.mp3");
}

// �f�X�g���N�^
Shot::~Shot()
{
	// ���
	for (itr = bullet.begin(); itr != bullet.end(); itr++)
	{
		bullet.erase(itr);
	}

	// ������Ă��Ȃ��e�̍폜
	for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
	{
		notBullet.erase(notItr);
		MV1DeleteModel((*notItr)->modelHandle);
		(*notItr)->modelHandle = NULL;
	}

	// �e�̃��f���J��
	MV1DeleteModel(modelHandle);
	modelHandle = NULL;

	if (se)
	{
		se->StopSoundEffect();
		se->Release();
		se = NULL;
		delete(se);
	}
}

// ������
void Shot::CreateShot(int _creater)
{

	// �������@���g�p���X�g�ǉ�
	for (int i = 0; i < _creater; i++)
	{
		bul[i] = new GunShot();
		notBullet.push_back(bul[i]);
	}


	// ���g�p���X�g
	if (!notBullet.empty())
	{
		for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
		{
			(*notItr)->pos = VGet(0, 100, 0);
			(*notItr)->dir = ZEROCLEAR;
			(*notItr)->life = 6;
			(*notItr)->isActive = false;
			(*notItr)->modelHandle = MV1DuplicateModel(modelHandle);

			MV1SetDifColorScale((*notItr)->modelHandle, GetColorF(0.f, 0.f, 0.f, 1.0f));

			//if (SceneMenu::GetPlayer() == "character/original/Ruby_Gun/Ruby.pmx") { MV1SetScale((*notItr)->modelHandle, VGet(1, 1, 1)); }
			//else { MV1SetScale((*notItr)->modelHandle, VGet(1, 1, 1)); }


			// �|�W�V�����X�V
			MV1SetPosition((*notItr)->modelHandle, (*notItr)->pos);
		}
	}

	// 
	bukketNumber = _creater;
	bulletCount = 0;
}

// �e�̍X�V
void Shot::BulletShot(VECTOR _dir, VECTOR _pos)
{
	// ��������
	if (!notBullet.empty())
	{
		for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
		{
			// ������
			(*notItr)->pos = VGet(_pos.x, _pos.y + 6, _pos.z);
			(*notItr)->dir = _dir;
			(*notItr)->life = 6;
		}
	}



	if (!bullet.empty())
	{
		// �e���o�Ă����
		for (itr = bullet.begin(); itr != bullet.end(); itr++)
		{
			// �e�̏���
			(*itr)->life -= 0.1f;

			// �e�̃��C�t�����炷
			if ((*itr)->life < 0.0f)
			{
				notBullet.push_back(*itr);
				bullet.remove(*itr);
				break;
			}

			// �x���V�e�B
			velocity = VScale((*itr)->dir, 60.0f);

			// �ړ��X�V
			(*itr)->pos = VAdd((*itr)->pos, velocity);

			// �|�W�V�����X�V
			MV1SetPosition((*itr)->modelHandle, (*itr)->pos);

			// ��]�X�V
			MV1SetRotationXYZ((*itr)->modelHandle, _dir);
		}
	}
}

// �ꔭ�����o��
void Shot::OneBulletPlay()
{
	bulletCount = 0;
	//
	se->PlaySoundEffect();
	// ��������
	if (!notBullet.empty())
	{
		//
		for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
		{
			bullet.push_back(*notItr);
			notBullet.remove(*notItr);
			break;
		}
	}
}

// �e�𑱂��ďo��
void Shot::BulletPlay()
{
	// �e�̔��ː�
	bulletCount++;

	// �e��A���ŏo��
	if(bulletCount % 6 == 0)
	{
		//
		se->PlaySoundEffect();
		// ��������
		if (!notBullet.empty())
		{
			//
			for (notItr = notBullet.begin(); notItr != notBullet.end(); notItr++)
			{
				bullet.push_back(*notItr);
				notBullet.remove(*notItr);
				break;
			}
		}
	}
}

// �e�̕\��
void Shot::Draw()
{
	// �`��
	if (!bullet.empty())
	{
		for (itr = bullet.begin(); itr != bullet.end(); itr++)
		{
			MV1DrawModel((*itr)->modelHandle);
		}
	}
}
