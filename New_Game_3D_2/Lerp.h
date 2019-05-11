#pragma once
#include "Common.h"
#include <math.h>

const float PI = 3.14159265359f;
const float TWOPI = 6.2818530718f;

float lerp(float a, float b, float s);
float lerpRadian(float a, float b, float s);

// 2つのベクトル間の角度を求める
float vec2Radian(const VECTOR *in_baseVec, const VECTOR* in_v);

// ラジアン返還
float DegToRad(float _in);

//
VECTOR DirectionToRadian(VECTOR _pos, float _rad);

// 交換
void Swap(int x[], int i, int j);

// クイックソート
void QSort(int x[], int _big, int _small);

float GetDistance(VECTOR _self, VECTOR _target);

void DrawLifeBoxBoss(CharacterBase *_player , Camera *_camera);
void DrawLifeBoxMediumBoss(CharacterBase *_player, Camera *_camera);
void DrawLifeBoxSmallEnemy(CharacterBase *_player, Camera *_camera);