#pragma once
#include "Common.h"
#include <math.h>

const float PI = 3.14159265359f;
const float TWOPI = 6.2818530718f;

float lerp(float a, float b, float s);
float lerpRadian(float a, float b, float s);

// 2�̃x�N�g���Ԃ̊p�x�����߂�
float vec2Radian(const VECTOR *in_baseVec, const VECTOR* in_v);

// ���W�A���Ԋ�
float DegToRad(float _in);

//
VECTOR DirectionToRadian(VECTOR _pos, float _rad);

// ����
void Swap(int x[], int i, int j);

// �N�C�b�N�\�[�g
void QSort(int x[], int _big, int _small);

float GetDistance(VECTOR _self, VECTOR _target);

void DrawLifeBoxBoss(CharacterBase *_player , Camera *_camera);
void DrawLifeBoxMediumBoss(CharacterBase *_player, Camera *_camera);
void DrawLifeBoxSmallEnemy(CharacterBase *_player, Camera *_camera);