#include "HitCheck.h"

HitCheck::HitCheck()
{

}

HitCheck::~HitCheck()
{

}

// �v���C���[�Ƃق��̃v���C���[�Ƃ̃{�b�N�X�̓����蔻��
void HitCheck::HitCheckBoxPlayerToOtherPlayer(CharacterBase * _player1, CharacterBase * _player2)
{
	// ����̋������ɓ����
	if (AskObjectLength(_player1->GetPos(), _player2->GetPos()))
	{
		bool isHitX = _player1->GetPos().x - PLAYER_X  < _player2->GetPos().x + PLAYER_X  && _player1->GetPos().x + PLAYER_X	> _player2->GetPos().x - PLAYER_X;
		bool isHitY = _player1->GetPos().y - PLAYER_H  < _player2->GetPos().y + PLAYER_Y     && _player1->GetPos().y + PLAYER_Y	> _player2->GetPos().y - PLAYER_H;
		bool isHitZ = _player1->GetPos().z - PLAYER_Z  < _player2->GetPos().z + PLAYER_Z  && _player1->GetPos().z + PLAYER_Z	> _player2->GetPos().z - PLAYER_Z;


		// �v���C���[�ƃG�l�~�[�̓����蔻��
		if (isHitX && isHitY && isHitZ)
		{
			if (!_player1->GetDamage() && !_player1->GetDeathBlow())
			{
				_player1->SetDamage(true);
			}
		}
	}
}

// �v���C���[�ƃv���C���[���m�̓����蔻��
void HitCheck::HitCheckCirclePlayerToOtherPlayer(CharacterBase * _player1, CharacterBase * _player2)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _player1->GetPos();
	bool isHit = true;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		isHit = false;
		VECTOR yZeroOtherPlayer = _player2->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _player1->GetRadius() + _player2->GetRadius())
		{
			//printfDx("Hit!\n");
			_player1->OnHit(_player2);
			isHit = true;
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _player1->GetPos();
		}
	}
}

// �v���C���[�̕K�E�Z�̓����蔻��
void HitCheck::HitCheckCirclePlayerDeathBlowToEnemy(CharacterBase * _player1, CharacterBase * _player2)
{
	// ����̋������ɓ����
	if (AskObjectLength(_player1->GetPos(), _player2->GetPos()))
	{
		// �E�܂����
		if (Player::GetCharacterCount() == 0) {
			bool isHitX = _player1->GetPos().x - PLAYER_X * 12 < _player2->GetPos().x + PLAYER_X * 6 && _player1->GetPos().x + PLAYER_X * 12 > _player2->GetPos().x - PLAYER_X * 6;
			bool isHitY = _player1->GetPos().y - PLAYER_H * 4 < _player2->GetPos().y + PLAYER_H * 4 && _player1->GetPos().y + PLAYER_H * 4 > _player2->GetPos().y - PLAYER_H * 4;
			bool isHitZ = _player1->GetPos().z - PLAYER_Z * 12 < _player2->GetPos().z + PLAYER_Z * 6 && _player1->GetPos().z + PLAYER_Z * 12 > _player2->GetPos().z - PLAYER_Z * 6;

			// �e�̋ʂƃG�l�~�[�̓����蔻��
			if (isHitX && isHitY && isHitZ)
			{
				if (!_player2->GetDamage())
				{
					_player2->SetDeathBlowDamage(true);
				}
			}
		}


		// Ruby
		if (Player::GetCharacterCount() == 1) {
			bool isHitX = _player1->GetPos().x - PLAYER_X * 12 < _player2->GetPos().x + PLAYER_X * 6 && _player1->GetPos().x + PLAYER_X * 12 > _player2->GetPos().x - PLAYER_X * 6;
			bool isHitY = _player1->GetPos().y - PLAYER_H * 4 < _player2->GetPos().y + PLAYER_H * 4 && _player1->GetPos().y + PLAYER_H * 4 > _player2->GetPos().y - PLAYER_H * 4;
			bool isHitZ = _player1->GetPos().z - PLAYER_Z * 12 < _player2->GetPos().z + PLAYER_Z * 6 && _player1->GetPos().z + PLAYER_Z * 12 > _player2->GetPos().z - PLAYER_Z * 6;

			// �e�̋ʂƃG�l�~�[�̓����蔻��
			if (isHitX && isHitY && isHitZ)
			{
				if (!_player2->GetDamage())
				{
					_player2->SetDeathBlowDamage(true);
				}
			}
		}


		// ���Ȃ�
		if (Player::GetCharacterCount() == 2) {
			bool isHitX = _player1->GetPos().x - PLAYER_X * 12 < _player2->GetPos().x + PLAYER_X * 6 && _player1->GetPos().x + PLAYER_X * 12 > _player2->GetPos().x - PLAYER_X * 6;
			bool isHitY = _player1->GetPos().y - PLAYER_H * 4 < _player2->GetPos().y + PLAYER_H * 4 && _player1->GetPos().y + PLAYER_H * 4 > _player2->GetPos().y - PLAYER_H * 4;
			bool isHitZ = _player1->GetPos().z - PLAYER_Z * 12 < _player2->GetPos().z + PLAYER_Z * 6 && _player1->GetPos().z + PLAYER_Z * 12 > _player2->GetPos().z - PLAYER_Z * 6;

			// �e�̋ʂƃG�l�~�[�̓����蔻��
			if (isHitX && isHitY && isHitZ)
			{
				if (!_player2->GetDamage())
				{
					_player2->SetDeathBlowDamage(true);
				}
			}
		}


		// ��
		if (Player::GetCharacterCount() == 3) {
			bool isHitX = _player1->GetPos().x - PLAYER_X * 12 < _player2->GetPos().x + PLAYER_X * 6 && _player1->GetPos().x + PLAYER_X * 12 > _player2->GetPos().x - PLAYER_X * 6;
			bool isHitY = _player1->GetPos().y - PLAYER_H * 4 < _player2->GetPos().y + PLAYER_H * 4 && _player1->GetPos().y + PLAYER_H * 4 > _player2->GetPos().y - PLAYER_H * 4;
			bool isHitZ = _player1->GetPos().z - PLAYER_Z * 12 < _player2->GetPos().z + PLAYER_Z * 6 && _player1->GetPos().z + PLAYER_Z * 12 > _player2->GetPos().z - PLAYER_Z * 6;

			// �e�̋ʂƃG�l�~�[�̓����蔻��
			if (isHitX && isHitY && isHitZ)
			{
				if (!_player2->GetDamage())
				{
					_player2->SetDeathBlowDamage(true);
				}
			}
		}

		// �J���X
		if (Player::GetCharacterCount() == 4) {
			bool isHitX = _player1->GetPos().x - PLAYER_X * 12 < _player2->GetPos().x + PLAYER_X * 6 && _player1->GetPos().x + PLAYER_X * 12 > _player2->GetPos().x - PLAYER_X * 6;
			bool isHitY = _player1->GetPos().y - PLAYER_H * 4 < _player2->GetPos().y + PLAYER_H * 4 && _player1->GetPos().y + PLAYER_H * 4 > _player2->GetPos().y - PLAYER_H * 4;
			bool isHitZ = _player1->GetPos().z - PLAYER_Z * 12 < _player2->GetPos().z + PLAYER_Z * 6 && _player1->GetPos().z + PLAYER_Z * 12 > _player2->GetPos().z - PLAYER_Z * 6;

			// �e�̋ʂƃG�l�~�[�̓����蔻��
			if (isHitX && isHitY && isHitZ)
			{
				if (!_player2->GetDamage())
				{
					_player2->SetDeathBlowDamage(true);
				}
			}
		}

	}
}

// �G�l�~�[�ƃv���C���[�̉~�̓����蔻��
bool HitCheck::HitCheckCirclePlayerToEnemy(CharacterBase * _player1, CharacterBase * _player2)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _player1->GetPos();
	bool isHit = true;
	int count = 0;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		count++;
		isHit = false;
		VECTOR yZeroOtherPlayer = _player2->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _player1->GetRadius() * 5 + _player2->GetRadius() * 5)
		{
			isHit = true;
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _player1->GetPos();
		}


		if (count >= 30)
		{
			break;
		}
	}

	return isHit;
}

// �^���[�ƃG�l�~�[�̓����蔻��
bool HitCheck::HitCheckCircleTowerToEnemy(Tower * _tower, CharacterBase * _enemy, float _size)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _tower->GetPos();
	bool isHit = true;
	int count = 0;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		count++;
		isHit = false;
		VECTOR yZeroOtherPlayer = _enemy->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _enemy->GetRadius() * _size + _enemy->GetRadius() * _size)
		{
			isHit = true;
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _enemy->GetPos();
		}


		if (count >= 30)
		{
			break;
		}
	}

	return isHit;
}

// ���{�X�ƃv���C���[�̉~�̓����蔻��
bool HitCheck::HitCheckCirclePlayerToMediumBoss(CharacterBase * _player1, CharacterBase * _player2, float _size)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _player1->GetPos();
	bool isHit = true;
	int count = 0;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		count++;
		isHit = false;
		VECTOR yZeroOtherPlayer = _player2->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _player1->GetRadius() * _size + _player2->GetRadius() * _size)
		{
			isHit = true;
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _player1->GetPos();
		}


		if (count >= 30)
		{
			break;
		}
	}

	return isHit;
}

// �{�X�ƃv���C���[�̃{�b�N�X�̓����蔻��
void HitCheck::HitCheckBoxPlayerToBoss(CharacterBase * _player1, CharacterBase * _player2)
{
	// ����̋������ɓ����
	if (AskObjectLength(_player1->GetPos(), _player2->GetPos()))
	{
		bool isHitX = _player1->GetPos().x - PLAYER_X * 4 < _player2->GetPos().x + PLAYER_X * 4 && _player1->GetPos().x + PLAYER_X * 4 > _player2->GetPos().x - PLAYER_X * 4;
		bool isHitY = _player1->GetPos().y - PLAYER_H * 2 < _player2->GetPos().y + PLAYER_Y * 2 && _player1->GetPos().y + PLAYER_Y * 2 > _player2->GetPos().y - PLAYER_H * 2;
		bool isHitZ = _player1->GetPos().z - PLAYER_Z * 4 < _player2->GetPos().z + PLAYER_Z * 4 && _player1->GetPos().z + PLAYER_Z * 4 > _player2->GetPos().z - PLAYER_Z * 4;

		bool isHitX2 = _player1->GetPos().x - PLAYER_X * 5 < _player2->GetPos().x + PLAYER_X * 5 && _player1->GetPos().x + PLAYER_X * 5 > _player2->GetPos().x - PLAYER_X * 5;
		bool isHitY2 = _player1->GetPos().y - PLAYER_H * 2 < _player2->GetPos().y + PLAYER_Y * 2 && _player1->GetPos().y + PLAYER_Y * 2 > _player2->GetPos().y - PLAYER_H * 2;
		bool isHitZ2 = _player1->GetPos().z - PLAYER_Z * 7 < _player2->GetPos().z + PLAYER_Z * 6 && _player1->GetPos().z + PLAYER_Z * 7 > _player2->GetPos().z - PLAYER_Z * 10;

		// �v���C���[�ƃ{�X�̓����蔻��
		if (isHitX && isHitY && isHitZ)
		{
			if (!_player1->GetDamage() && !_player1->GetDeathBlow())
			{
				_player1->SetDamage(true);
			}
		}

		// �{�X�ƃv���C���[�̍U���̓����蔻��
		if (isHitX2 && isHitY2 && isHitZ2)
		{
			if (!_player2->GetDamage())
			{
				if (_player1->GetDeathBlow())
				{
					_player2->SetDeathBlowDamage(true);
				}
				else if (_player1->GetAtack())
				{
					_player2->SetDamage(true);
					_player1->SetDeathBlowCount(5.0f);
				}
			}
		}
	}
}

// �v���C���[�ƃG�l�~�[�̉~�̓����蔻��
VECTOR HitCheck::HitCheckCirclePlayerToEnemy(CharacterBase * _player1, CharacterBase * _player2, Camera *_camera)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _player1->GetPos();
	bool isHit = true;
	int count = 0;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		count++;
		isHit = false;
		VECTOR yZeroOtherPlayer = _player2->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _player1->GetRadius() * 6 + _player2->GetRadius() * 6)
		{
			isHit = true;
			return _player2->GetPos();
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _player1->GetPos();
		}


		if (count >= 30)
		{
			break;
		}
	}

	return _camera->GetPos();
}

// �񕜂ƃv���C���[�̓����蔻��
void HitCheck::HitCheckBoxPlayerToItem(CharacterBase * _player1, ItemBase * _item)
{
	// ����̋������ɓ����
	if (AskObjectLength(_item->GetPos(), _player1->GetPos()))
	{
		bool isX = _player1->GetPos().x - PLAYER_X * 1.5f < _item->GetPos().x + PLAYER_X * 1.5f && _player1->GetPos().x + PLAYER_X * 1.5f > _item->GetPos().x - PLAYER_X * 1.5f;
		bool isY = _player1->GetPos().y - PLAYER_H     < _item->GetPos().y + PLAYER_Y     && _player1->GetPos().y + PLAYER_Y     > _item->GetPos().y - PLAYER_H;
		bool isZ = _player1->GetPos().z - PLAYER_Z * 1.5f < _item->GetPos().z + PLAYER_Z * 1.5f && _player1->GetPos().z + PLAYER_Z * 1.5f > _item->GetPos().z - PLAYER_Z * 1.5f;

		// �v���C���[�ƃG�l�~�[�̓����蔻��
		if (isX && isY && isZ)
		{
			if (!_item->GetLost() && !_item->GetItemGet())
			{
				if (_player1->GetLife() >= 10)
				{
					Tower::SetLife(-2);
				}
				else
				{
					_player1->SetLife(1);
				}


				_item->SetItemGet(true);
				_item->SetLost(true);
			}
		}
	}
}

// �R�C���ƃv���C���[�̓����蔻��
void HitCheck::HitCheckBoxPlayerToCoin(CharacterBase * _player1, ItemBase * _item)
{
	// ����̋������ɓ����
	if (AskObjectLength(_item->GetPos(), _player1->GetPos()))
	{
		bool isX = _player1->GetPos().x - PLAYER_X * 1.5f < _item->GetPos().x + PLAYER_X * 1.5f && _player1->GetPos().x + PLAYER_X * 1.5f > _item->GetPos().x - PLAYER_X * 1.5f;
		bool isY = _player1->GetPos().y - PLAYER_H     < _item->GetPos().y + PLAYER_Y     && _player1->GetPos().y + PLAYER_Y     > _item->GetPos().y - PLAYER_H;
		bool isZ = _player1->GetPos().z - PLAYER_Z * 1.5f < _item->GetPos().z + PLAYER_Z * 1.5f && _player1->GetPos().z + PLAYER_Z * 1.5f > _item->GetPos().z - PLAYER_Z * 1.5f;

		// �v���C���[�ƃG�l�~�[�̓����蔻��
		if (isX && isY && isZ)
		{
			if (!_item->GetLost() && !_item->GetItemGet())
			{
				_player1->SetMoney(200);
				_item->SetItemGet(true);
				_item->SetLost(true);
			}
		}
	}
}

// �A�C�e���ƃv���C���[���߂���Έ����񂹂�
bool HitCheck::HitCheckCirclePlayerToItemAttract(CharacterBase * _player1, ItemBase * _item, float _scale)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _player1->GetPos();
	bool isHit = true;
	int count = 0;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		count++;
		isHit = false;
		VECTOR yZeroOtherPlayer = _item->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _player1->GetRadius() * _scale + _item->GetRadius() *_scale)
		{
			isHit = true;
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _player1->GetPos();
		}


		if (count >= 30)
		{
			break;
		}
	}

	return isHit;
}

// �V���b�v�ƃv���C���|�̓����蔻��
bool HitCheck::HitCheckBoxPlayerToBuyItemObject(CharacterBase * _player1, DefenseBase * _defense1)
{
	// ����̋������ɓ����
	if (AskObjectLength(_defense1->GetPos(), _player1->GetPos()))
	{
		bool isX = _player1->GetPos().x - PLAYER_X * 5 < _defense1->GetPos().x + PLAYER_X * 5 && _player1->GetPos().x + PLAYER_X * 5 > _defense1->GetPos().x - PLAYER_X * 5;
		bool isY = _player1->GetPos().y - PLAYER_H     < _defense1->GetPos().y + PLAYER_Y     && _player1->GetPos().y + PLAYER_Y     > _defense1->GetPos().y - PLAYER_H;
		bool isZ = _player1->GetPos().z - PLAYER_Z * 3 < _defense1->GetPos().z + PLAYER_Z * 3 && _player1->GetPos().z + PLAYER_Z * 3 > _defense1->GetPos().z - PLAYER_Z * 3;

		// �v���C���[�ƃI�u�W�F�N�g�𔃂����̂̓����蔻��
		if (isX && isY && isZ)
		{
			return true;
		}
	}

	return false;
}

// �L�����N�^�[�ƒn�ʂƂ̓����蔻��
void HitCheck::HitCheckPlayerToGound(CharacterBase * _player, Stage * _stage, float _scale)
{
	MV1_COLL_RESULT_POLY hitPoly;
	MV1_COLL_RESULT_POLY hitWallPoly[5];

	VECTOR startPos;
	VECTOR endPos;

	VECTOR wallStartPos[5];
	VECTOR wallEndPos[5];


	// �����̓����蔻��
	startPos = VGet(_player->GetPos().x, _player->GetPos().y, _player->GetPos().z);
	endPos = VGet(_player->GetPos().x, _player->GetPos().y - PLAYER_H * _scale, _player->GetPos().z);
	// ���̓����蔻��
	wallStartPos[WALL_UP] = VGet(_player->GetPos().x, _player->GetPos().y, _player->GetPos().z);
	wallEndPos[WALL_UP] = VGet(_player->GetPos().x, _player->GetPos().y + PLAYER_Y * _scale, _player->GetPos().z);

	// �E�̓����蔻���
	wallStartPos[WALL_RIGHT] = VGet(_player->GetPos().x, _player->GetPos().y, _player->GetPos().z);
	wallEndPos[WALL_RIGHT] = VGet(_player->GetPos().x - PLAYER_X * _scale, _player->GetPos().y + PLAYER_Y * _scale, _player->GetPos().z);
	// ���̓����蔻���	
	wallStartPos[WALL_LEFT] = VGet(_player->GetPos().x, _player->GetPos().y, _player->GetPos().z);
	wallEndPos[WALL_LEFT] = VGet(_player->GetPos().x + PLAYER_X * _scale, _player->GetPos().y + PLAYER_Y * _scale, _player->GetPos().z);
	// �O�̓����蔻���
	wallStartPos[WALL_FRONT] = VGet(_player->GetPos().x, _player->GetPos().y, _player->GetPos().z);
	wallEndPos[WALL_FRONT] = VGet(_player->GetPos().x, _player->GetPos().y + PLAYER_Y * _scale, _player->GetPos().z - PLAYER_Z * _scale);
	// ���̓����蔻���
	wallStartPos[WALL_BACK] = VGet(_player->GetPos().x, _player->GetPos().y, _player->GetPos().z);
	wallEndPos[WALL_BACK] = VGet(_player->GetPos().x, _player->GetPos().y + PLAYER_Y * _scale, _player->GetPos().z + PLAYER_Z * _scale);


	// �����蔻��`�F�b�N�֐�
	hitPoly = MV1CollCheck_Line(_stage->GetModel(), -1, startPos, endPos);

	for (int i = 0; i < 5; i++)
	{
		hitWallPoly[i] = MV1CollCheck_Line(_stage->GetModel(), -1, wallStartPos[i], wallEndPos[i]);
	}

	// ���������ꍇ�͂��̈ʒu��`�悷������̏I�_�Ƃ���
	// ��
	if (hitWallPoly[WALL_UP].HitFlag == 1)
	{
		_player->SetPosY(hitWallPoly[WALL_BACK].HitPosition.y - PLAYER_Y *_scale);
	}
	// ����
	if (hitPoly.HitFlag == 1)
	{
		_player->SetPosY(hitPoly.HitPosition.y + PLAYER_H * _scale);
		_player->SetJump(false);
		_player->SetJumpPower(1.0f);
		_player->SetJumpCount(0);
	}
	// �E
	if (hitWallPoly[WALL_RIGHT].HitFlag == 1)
	{
		_player->SetPosX(hitWallPoly[WALL_RIGHT].HitPosition.x + PLAYER_X * _scale);
	}
	// ��
	if (hitWallPoly[WALL_LEFT].HitFlag == 1)
	{
		_player->SetPosX(hitWallPoly[WALL_LEFT].HitPosition.x - PLAYER_X * _scale);
	}
	// �O
	if (hitWallPoly[WALL_FRONT].HitFlag == 1)
	{
		_player->SetPosZ(hitWallPoly[WALL_FRONT].HitPosition.z + PLAYER_Z * _scale);
	}
	// ���
	if (hitWallPoly[WALL_BACK].HitFlag == 1)
	{
		_player->SetPosZ(hitWallPoly[WALL_BACK].HitPosition.z - PLAYER_Z * _scale);
	}
}

// �e�e�ƓG�̓����蔻��
void HitCheck::HitCheckGun(VECTOR _gunPos, CharacterBase * _player2, float _scale)
{
	// ����̋������ɓ����
	if (AskObjectLength(_gunPos, _player2->GetPos()))
	{
		bool isHitX = _gunPos.x - PLAYER_X * _scale  < _player2->GetPos().x + PLAYER_X  && _gunPos.x + PLAYER_X	* _scale > _player2->GetPos().x - PLAYER_X;
		bool isHitY = _gunPos.y - PLAYER_H * _scale < _player2->GetPos().y + PLAYER_H  && _gunPos.y + PLAYER_H * _scale	 > _player2->GetPos().y - PLAYER_H;
		bool isHitZ = _gunPos.z - PLAYER_Z * _scale < _player2->GetPos().z + PLAYER_Z  && _gunPos.z + PLAYER_Z	* _scale > _player2->GetPos().z - PLAYER_Z;


		// �e�̋ʂƃG�l�~�[�̓����蔻��
		if (isHitX && isHitY && isHitZ)
		{
			if (!_player2->GetDamage() && _player2->GetLife() > 0)
			{
				_player2->SetDamage(true);
			}
		}
	}
}

// �ǂƂ̓����蔻��
void HitCheck::HitCheckDefenseWall(DefenseBase *_defense, CharacterBase * _player, float _scale, int _hitDamage)
{
	// ����̋������ɓ����
	if (AskObjectLength(_defense->GetPos(), _player->GetPos()))
	{
		bool isFront = _player->GetPos().z > _defense->GetPos().z && _player->GetPos().z < _defense->GetPos().z + 5 && _player->GetPos().y < _defense->GetPos().y + 20;
		bool isBack = _player->GetPos().z < _defense->GetPos().z && _player->GetPos().z > _defense->GetPos().z - 5 && _player->GetPos().y < _defense->GetPos().y + 20;
		bool isRight = _player->GetPos().x > _defense->GetPos().x && _player->GetPos().x < _defense->GetPos().x + 20;
		bool isLeft = _player->GetPos().x < _defense->GetPos().x && _player->GetPos().x > _defense->GetPos().x - 20;

		if (isBack && (isLeft || isRight))
		{
			_player->SetPos(VGet(_player->GetPos().x, _player->GetPos().y, _defense->GetPos().z - 5));

			if (!_defense->GetDamage() && _player->GetLife() > 0)
			{
				_defense->SetDamageDecrease(_hitDamage);
				_defense->SetDamage(true);
			}
		}

		if (isFront && (isLeft || isRight))
		{
			_player->SetPos(VGet(_player->GetPos().x, _player->GetPos().y, _defense->GetPos().z + 5));

			if (!_defense->GetDamage() && _player->GetLife() > 0)
			{
				_defense->SetDamageDecrease(_hitDamage);
				_defense->SetDamage(true);
			}
		}
	}
}

// �U���{�[���ƓG�̓����蔻��
void HitCheck::HitCheckDefenseAtackBall(DefenseBase * _defense, CharacterBase * _player, float _scale, int _atackDamage, int _hitDamage)
{
	// ����̋������ɓ����
	if (AskObjectLength(_defense->GetPos(), _player->GetPos()))
	{
		bool isX = _player->GetPos().x - PLAYER_X * _scale < _defense->GetPos().x + PLAYER_X * _scale && _player->GetPos().x + PLAYER_X * _scale > _defense->GetPos().x - PLAYER_X * _scale;
		bool isY = _player->GetPos().y - PLAYER_H     < _defense->GetPos().y + PLAYER_Y     && _player->GetPos().y + PLAYER_Y     > _defense->GetPos().y - PLAYER_H;
		bool isZ = _player->GetPos().z - PLAYER_Z * _scale < _defense->GetPos().z + PLAYER_Z * _scale && _player->GetPos().z + PLAYER_Z * _scale > _defense->GetPos().z - PLAYER_Z * _scale;

		// �G�l�~�[�ƃf�B�t�F���X�U���̓����蔻��
		if (isX && isY && isZ)
		{
			// �f�B�t�F���X�U���I�u�W�F�N�g���o�����Ă����
			if (_defense->GetDefense())
			{
				_player->FlutterCharacter();
				_player->SetLifeDecrease(_atackDamage);
				_player->SetDamage(true);

				if (!_defense->GetDamage() && _player->GetLife() > 0)
				{
					_defense->SetDamageDecrease(_hitDamage);
					_defense->SetDamage(true);
				}
			}
		}
	}
}

// ���ƓG�̓����蔻��
void HitCheck::HitCheckDefenseFire(DefenseBase * _defense, CharacterBase * _player, float _scale, int _atackDamage, int _hitDamage)
{
	// ����̋������ɓ����
	if (AskObjectLength(_defense->GetPos(), _player->GetPos()))
	{
		bool isX = _player->GetPos().x - PLAYER_X * _scale < _defense->GetPos().x + PLAYER_X * _scale && _player->GetPos().x + PLAYER_X * _scale > _defense->GetPos().x - PLAYER_X * _scale;
		bool isY = _player->GetPos().y - PLAYER_H     < _defense->GetPos().y + PLAYER_Y     && _player->GetPos().y + PLAYER_Y     > _defense->GetPos().y - PLAYER_H;
		bool isZ = _player->GetPos().z - PLAYER_Z * _scale < _defense->GetPos().z + PLAYER_Z * _scale && _player->GetPos().z + PLAYER_Z * _scale > _defense->GetPos().z - PLAYER_Z * _scale;

		// �G�l�~�[�ƃf�B�t�F���X�U���̓����蔻��
		if (isX && isY && isZ)
		{
			// �f�B�t�F���X�U���I�u�W�F�N�g���o�����Ă����
			if (_defense->GetDefense())
			{
				if (!_defense->GetDamage() && _player->GetLife() > 0)
				{
					_player->SetDamage(true);
					_player->SetLifeDecrease(_atackDamage);
					_defense->SetDamageDecrease(_hitDamage);
					_defense->SetDamage(true);
				}
			}
		}
	}
}

// ���m�ƓG�̓����蔻��
void HitCheck::HitCheckDefenseSoldier(DefenseBase * _defense, CharacterBase * _player, float _scale, int _hitDamage)
{
	// ����̋������ɓ����
	if (AskObjectLength(_defense->GetPos(), _player->GetPos()))
	{
		bool isX = _player->GetPos().x - PLAYER_X * _scale < _defense->GetPos().x + PLAYER_X * _scale && _player->GetPos().x + PLAYER_X * _scale > _defense->GetPos().x - PLAYER_X * _scale;
		bool isY = _player->GetPos().y - PLAYER_H     < _defense->GetPos().y + PLAYER_Y     && _player->GetPos().y + PLAYER_Y     > _defense->GetPos().y - PLAYER_H;
		bool isZ = _player->GetPos().z - PLAYER_Z * _scale < _defense->GetPos().z + PLAYER_Z * _scale && _player->GetPos().z + PLAYER_Z * _scale > _defense->GetPos().z - PLAYER_Z * _scale;

		// �G�l�~�[�ƃf�B�t�F���X�U���̓����蔻��
		if (isX && isY && isZ)
		{
			// �f�B�t�F���X�U���I�u�W�F�N�g���o�����Ă����
			if (_defense->GetDefense())
			{
				if (!_defense->GetDamage() && _player->GetLife() > 0)
				{
					_defense->SetDamageDecrease(_hitDamage);
					_defense->SetDamage(true);
				}
			}
		}
	}
}

// ���m�ƓG�͈͓̔������蔻��
bool HitCheck::HitCheckCircleEnemyToSoldier(CharacterBase * _enemy, DefenseBase * _soldier, float _scale)
{
	// �����蔻����s��.
	VECTOR yZeroPlayer = _enemy->GetPos();
	bool isHit = true;
	int count = 0;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		count++;
		isHit = false;
		VECTOR yZeroOtherPlayer = _soldier->GetPos();

		// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.
		VECTOR playerToObs = VSub(yZeroOtherPlayer, yZeroPlayer);

		if (VSize(playerToObs) < _enemy->GetRadius() * _scale + _soldier->GetRadius() *_scale)
		{
			isHit = true;
		}

		// �q�b�g���Ă���v�Z���Ȃ����ăv���C���[�̈ʒu���X�V.
		if (isHit)
		{
			yZeroPlayer = _enemy->GetPos();
		}


		if (count >= 30)
		{
			break;
		}
	}

	return isHit;
}

// ���m�̏e�e�ƓG�̓����蔻��
void HitCheck::HitCheckDefenseSoldierBullet(DefenseBase * _defense, CharacterBase * _player, float _scale, int _atackDamage)
{
	// ����̋������ɓ����
	if (AskObjectLength(_defense->GetPos(), _player->GetPos()))
	{
		bool isX = _player->GetPos().x - PLAYER_X * _scale < _defense->GetBulletPos().x + PLAYER_X * _scale && _player->GetPos().x + PLAYER_X * _scale > _defense->GetBulletPos().x - PLAYER_X * _scale;
		bool isY = _player->GetPos().y - PLAYER_H     < _defense->GetBulletPos().y + PLAYER_Y     && _player->GetPos().y + PLAYER_Y     > _defense->GetBulletPos().y - PLAYER_H;
		bool isZ = _player->GetPos().z - PLAYER_Z * _scale < _defense->GetBulletPos().z + PLAYER_Z * _scale && _player->GetPos().z + PLAYER_Z * _scale > _defense->GetBulletPos().z - PLAYER_Z * _scale;

		// �G�l�~�[�ƃf�B�t�F���X�U���̓����蔻��
		if (isX && isY && isZ)
		{
			// �f�B�t�F���X�U���I�u�W�F�N�g���o�����Ă����
			if (_defense->GetDefense())
			{
				if (!_player->GetDamage()) _player->SetLifeDecrease(_atackDamage);
				_player->SetDamage(true);
			}
		}
	}
}

// �����𑪂�
bool HitCheck::AskObjectLength(VECTOR _pos1, VECTOR _pos2)
{
	VECTOR tmpPos = VSub(_pos1, _pos2);

	float tmpLength = VSize(tmpPos);


	if (tmpLength <= 60)
	{
		return true;
	}

	return false;
}