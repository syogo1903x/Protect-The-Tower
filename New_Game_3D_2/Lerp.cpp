#include "Lerp.h"

float lerp(float a, float b, float s)
{
	float result = ((1.f - s) * a) + (s * b);
	return result;
}

float lerpRadian(float a, float b, float s)
{
	float result;
	float diff = b - a;

	if (diff < -PI)
	{
		b += TWOPI;
		result = lerp(a, b, s);
		if (result >= TWOPI)
		{
			result -= TWOPI;
		}
	}
	else if (diff > PI)
	{
		b -= TWOPI;
		result = lerp(a, b, s);
		if (result < 0.f)
		{
			result += TWOPI;
		}
	}
	else
	{
		result = lerp(a, b, s);
	}
	return result;
}

float vec2Radian(const VECTOR * in_baseVec, const VECTOR * in_v)
{
	VECTOR base, v1;
	base = *in_baseVec;
	v1 = *in_v;

	// ������x�N�g������̊p�x�����߂�
	float dot, angle;
	VNorm(base);
	VNorm(v1);
	dot = VDot(base, v1);
	angle = acosf(dot);
	//�E��肩����肩�H�ŉ�]�������v�Z
	VECTOR tmp;
	tmp = VCross(base, v1);

	if (tmp.y < 0)
	{
		angle *= -1.0f;
	}

	return angle;
}

float DegToRad(float _in)
{
	return _in *(DX_PI_F / 180.0f);
}

VECTOR DirectionToRadian(VECTOR _pos, float _rad)
{
	VECTOR tmpPos;
	float sinPram = sinf(_rad);
	float cosPram = cosf(_rad);

	tmpPos.x = _pos.z * sinPram - _pos.x * cosPram;
	tmpPos.y = 0;
	tmpPos.z = _pos.x * sinPram + _pos.z * cosPram;

	return tmpPos;
}

void Swap(int x[], int i, int j)
{
	int tmp;
	tmp = x[i];
	x[i] = x[j];
	x[j] = tmp;
}

void QSort(int x[], int _big, int _small)
{
	int i;
	int j;
	int pivot;
	j = _big;
	// ��ԏ������z��̗v�f
	i = _small;
	// ��ԑ����z��̗v�f
	// �z��̒��S
	pivot = x[(_big + _small) / 2];
	while (1)
	{
		// ���S���傫���l���o��܂ő���
		while (x[i] < pivot)
			i++;
		// ���S��菬�����l���o��Ό���
		while (pivot < x[j])
			j--;
		// �������l���f�J���l���傫���Ȃ�΃��[�v�𔲂���
		if (i >= j)
			break;

		Swap(x, i, j);
		i++;
		j--;
	}

	// ��{�l�̍���2�ȏ�̗v�f������΍��ɃN�C�b�N�\�[�g
	if (_big < i - 1)
		QSort(x, _big, i - 1);
	// ��{�l�̉E��2�ȏ�̗v�f������ΉE�ɃN�C�b�N�\�[�g
	if (j + 1 < _small)
		QSort(x, j + 1, _small);
}

float GetDistance(VECTOR _self, VECTOR _target)
{
	VECTOR distance;

	distance.x = _self.x - _target.x;
	
	distance.y = _self.y - _target.y;
	
	distance.z = _self.z - _target.z;
	
	return (float)sqrt((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));
}

//. UI�Ɍ�ňړ�
void DrawLifeBoxBoss(CharacterBase *_player, Camera *_camera)
{
	VECTOR stringPos = ConvWorldPosToScreenPos(_player->GetPos());

	DrawBoxAA(stringPos.x, stringPos.y - 10, stringPos.x + 100, stringPos.y + 5, GetColor(105, 105, 105), TRUE);
	DrawBoxAA(stringPos.x, stringPos.y - 5, stringPos.x + (_player->GetLife() * 10), stringPos.y, GetColor(0, 255, 0), TRUE);
}

void DrawLifeBoxMediumBoss(CharacterBase * _player, Camera *_camera)
{
	VECTOR stringPos = ConvWorldPosToScreenPos(_player->GetPos());

	DrawBoxAA(stringPos.x, stringPos.y - 10, stringPos.x + 60, stringPos.y + 5, GetColor(105, 105, 105), TRUE);
	DrawBoxAA(stringPos.x, stringPos.y - 5, stringPos.x + (_player->GetLife() * 10), stringPos.y, GetColor(0, 255, 0), TRUE);
}

void DrawLifeBoxSmallEnemy(CharacterBase * _player, Camera *_camera)
{
	VECTOR stringPos = ConvWorldPosToScreenPos(_player->GetPos());

	DrawBoxAA(stringPos.x, stringPos.y - 10, stringPos.x + 30, stringPos.y + 5, GetColor(105, 105, 105), TRUE);
	DrawBoxAA(stringPos.x, stringPos.y - 5, stringPos.x + (_player->GetLife() * 10), stringPos.y, GetColor(0, 255, 0), TRUE);

}
