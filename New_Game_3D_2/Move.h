#pragma once
#include "DxLib.h"

struct Move
{
	VECTOR pos;
	VECTOR dir;
	VECTOR angle;

	bool isMove;
};