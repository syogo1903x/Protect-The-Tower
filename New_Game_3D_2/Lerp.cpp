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

	// 基準方向ベクトルからの角度を求める
	float dot, angle;
	VNorm(base);
	VNorm(v1);
	dot = VDot(base, v1);
	angle = acosf(dot);
	//右回りか左回りか？で回転符号を計算
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
	// 一番小さい配列の要素
	i = _small;
	// 一番多き配列の要素
	// 配列の中心
	pivot = x[(_big + _small) / 2];
	while (1)
	{
		// 中心より大きい値が出るまで増加
		while (x[i] < pivot)
			i++;
		// 中心より小さい値が出れば減少
		while (pivot < x[j])
			j--;
		// 小さい値がデカい値より大きくなればループを抜ける
		if (i >= j)
			break;

		Swap(x, i, j);
		i++;
		j--;
	}

	// 基本値の左に2以上の要素があれば左にクイックソート
	if (_big < i - 1)
		QSort(x, _big, i - 1);
	// 基本値の右に2以上の要素があれば右にクイックソート
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

//. UIに後で移動
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
