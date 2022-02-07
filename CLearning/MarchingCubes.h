#pragma once

#include "Noise.h"
int8_t triTable[256][16] =
{
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
	{ 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, 4 },
	{ 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, 4 },
	{ 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, 4 },
	{ 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, 4 },
	{ 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, 3 },
	{ 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, 4 },
	{ 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, 4 },
	{ 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, 3 },
	{ 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, 4 },
	{ 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, 4 },
	{ 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, 4 },
	{ 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, 4 },
	{ 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, 4 },
	{ 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, 4 },
	{ 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, 4 },
	{ 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, 5 },
	{ 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, 5 },
	{ 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, 4 },
	{ 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, 4 },
	{ 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, 4 },
	{ 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, 4 },
	{ 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, 4 },
	{ 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, 4 },
	{ 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, 4 },
	{ 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, 5 },
	{ 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, 4 },
	{ 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, 4 },
	{ 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, 5 },
	{ 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, 4 },
	{ 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, 5 },
	{ 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, 5 },
	{ 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, 4 },
	{ 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, 3 },
	{ 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, 4 },
	{ 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, 4 },
	{ 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, 4 },
	{ 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, 4 },
	{ 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, 5 },
	{ 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, 4 },
	{ 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, 5 },
	{ 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, 3 },
	{ 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, 4 },
	{ 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, 4 },
	{ 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, 4 },
	{ 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, 5 },
	{ 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, 3 },
	{ 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, 4 },
	{ 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, 5 },
	{ 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, 5 },
	{ 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, 4 },
	{ 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, 5 },
	{ 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, 4 },
	{ 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, 4 },
	{ 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, 3 },
	{ 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, 4 },
	{ 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, 4 },
	{ 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, 4 },
	{ 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, 3 },
	{ 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, 4 },
	{ 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, 4 },
	{ 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, 4 },
	{ 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, 5 },
	{ 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, 4 },
	{ 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, 4 },
	{ 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, 3 },
	{ 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, 5 },
	{ 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, 4 },
	{ 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, 4 },
	{ 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, 4 },
	{ 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, 5 },
	{ 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, 4 },
	{ 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, 4 },
	{ 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, 5 },
	{ 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, 4 },
	{ 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, 5 },
	{ 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, 5 },
	{ 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, 4 },
	{ 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, 4 },
	{ 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, 4 },
	{ 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, 4 },
	{ 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, 5 },
	{ 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, 5 },
	{ 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, 4 },
	{ 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, 4 },
	{ 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, 3 },
	{ 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, 5 },
	{ 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, 5 },
	{ 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, 4 },
	{ 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, 3 },
	{ 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, 4 },
	{ 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, 4 },
	{ 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, 4 },
	{ 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, 5 },
	{ 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, 4 },
	{ 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, 4 },
	{ 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, 5 },
	{ 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, 3 },
	{ 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, 4 },
	{ 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, 4 },
	{ 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, 5 },
	{ 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, 4 },
	{ 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, 5 },
	{ 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, 5 },
	{ 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, 4 },
	{ 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, 5 },
	{ 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, 4 },
	{ 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, 4 },
	{ 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, 4 },
	{ 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, 4 },
	{ 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, 5 },
	{ 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, 4 },
	{ 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, 5 },
	{ 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, 3 },
	{ 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, 4 },
	{ 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, 4 },
	{ 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, 5 },
	{ 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, 5 },
	{ 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, 3 },
	{ 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, 4 },
	{ 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, 3 },
	{ 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, 3 },
	{ 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, 4 },
	{ 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, 3 },
	{ 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, 4 },
	{ 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2 },
	{ 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 },
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0 }
};


	Vertex VertInterp(vec3 aPos, float aVal, vec3 aCol, vec3 bPos, float bVal, vec3 bCol);

	void GenerateChunkMesh1(Chunk* chunk)
	{
		int triCount = 0, activeVert = 0;

		HelperCube cubes[chunkWidth][chunkWidth][chunkWidth];

		for (int x = 0; x < chunkWidth; x++)
			for (int y = 0; y < chunkWidth; y++)
				for (int z = 0; z < chunkWidth; z++)
				{
					chunk->indices[x][y][z] = 0;
					if (chunk->tiles[x][y][z] >= isoLevel) chunk->indices[x][y][z] |= 1u;
					if (chunk->tiles[x + 1][y][z] >= isoLevel) chunk->indices[x][y][z] |= 2u;
					if (chunk->tiles[x + 1][y][z + 1] >= isoLevel) chunk->indices[x][y][z] |= 4u;
					if (chunk->tiles[x][y][z + 1] >= isoLevel) chunk->indices[x][y][z] |= 8u;
					if (chunk->tiles[x][y + 1][z] >= isoLevel) chunk->indices[x][y][z] |= 16u;
					if (chunk->tiles[x + 1][y + 1][z] >= isoLevel) chunk->indices[x][y][z] |= 32u;
					if (chunk->tiles[x + 1][y + 1][z + 1] >= isoLevel) chunk->indices[x][y][z] |= 64u;
					if (chunk->tiles[x][y + 1][z + 1] >= isoLevel) chunk->indices[x][y][z] |= 128u;
					//printf("%i, ", cubes[x][y][z].index);

					triCount += triTable[chunk->indices[x][y][z]][15];
				}

		chunk->verts = CreateVertexList(triCount * 3);
	}

	void GenerateChunkMesh2(Chunk* chunk)
	{
		int activeVert = 0;
		float currentValues[8];
		vec3 currentColors[8];
		vec3 currentPos;

		HelperCube cubes[chunkWidth][chunkWidth][chunkWidth];

		for (int x = 0; x < chunkWidth; x++)
		{
			currentPos[0] = x + chunk->pos[0] * chunkWidth - (chunkWidth / 2.0f);

			for (int y = 0; y < chunkWidth; y++)
			{
				currentPos[1] = y + chunk->pos[1] * chunkWidth - (chunkWidth / 2.0f);

				for (int z = 0; z < chunkWidth; z++)
				{
					currentPos[2] = z + chunk->pos[2] * chunkWidth - (chunkWidth / 2.0f);

					currentValues[0] = chunk->tiles[x][y][z];
					glm_vec3_copy(chunk->colors[x][y][z], currentColors[0]);

					currentValues[1] = chunk->tiles[x + 1][y][z];
					glm_vec3_copy(chunk->colors[x + 1][y][z], currentColors[1]);

					currentValues[2] = chunk->tiles[x + 1][y][z + 1];
					glm_vec3_copy(chunk->colors[x + 1][y][z + 1], currentColors[2]);

					currentValues[3] = chunk->tiles[x][y][z + 1];
					glm_vec3_copy(chunk->colors[x][y][z + 1], currentColors[3]);

					currentValues[4] = chunk->tiles[x][y + 1][z];
					glm_vec3_copy(chunk->colors[x][y + 1][z], currentColors[4]);

					currentValues[5] = chunk->tiles[x + 1][y + 1][z];
					glm_vec3_copy(chunk->colors[x + 1][y + 1][z], currentColors[5]);

					currentValues[6] = chunk->tiles[x + 1][y + 1][z + 1];
					glm_vec3_copy(chunk->colors[x + 1][y + 1][z + 1], currentColors[6]);

					currentValues[7] = chunk->tiles[x][y + 1][z + 1];
					glm_vec3_copy(chunk->colors[x][y + 1][z + 1], currentColors[7]);



#pragma region Find vertices

					cubes[x][y][z].verts[0] = VertInterp(currentPos, currentValues[0], currentColors[0], (vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] }, currentValues[1], currentColors[1]);
					cubes[x][y][z].verts[1] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] }, currentValues[1], currentColors[1], (vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] + 1 }, currentValues[2], currentColors[2]);
					cubes[x][y][z].verts[2] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] + 1 }, currentValues[2], currentColors[2], (vec3) { currentPos[0], currentPos[1], currentPos[2] + 1 }, currentValues[3], currentColors[3]);
					cubes[x][y][z].verts[3] = VertInterp((vec3) { currentPos[0], currentPos[1], currentPos[2] + 1 }, currentValues[3], currentColors[3], currentPos, currentValues[0], currentColors[0]);

					cubes[x][y][z].verts[4] = VertInterp((vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] }, currentValues[4], currentColors[4], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] }, currentValues[5], currentColors[5]);
					cubes[x][y][z].verts[5] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] }, currentValues[5], currentColors[5], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] + 1 }, currentValues[6], currentColors[6]);
					cubes[x][y][z].verts[6] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] + 1 }, currentValues[6], currentColors[6], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] + 1 }, currentValues[7], currentColors[7]);
					cubes[x][y][z].verts[7] = VertInterp((vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] + 1 }, currentValues[7], currentColors[7], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] }, currentValues[4], currentColors[4]);

					cubes[x][y][z].verts[8] = VertInterp(currentPos, currentValues[0], currentColors[0], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] }, currentValues[4], currentColors[4]);
					cubes[x][y][z].verts[9] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] }, currentValues[1], currentColors[1], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] }, currentValues[5], currentColors[5]);
					cubes[x][y][z].verts[10] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] + 1 }, currentValues[2], currentColors[2], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] + 1 }, currentValues[6], currentColors[6]);
					cubes[x][y][z].verts[11] = VertInterp((vec3) { currentPos[0], currentPos[1], currentPos[2] + 1 }, currentValues[3], currentColors[3], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] + 1 }, currentValues[7], currentColors[7]);

#pragma endregion

					Tri value;
					//printf("a");
					for (uint8_t i = 0; i < triTable[chunk->indices[x][y][z]][15] * 3; i += 3)
					{
						//printf("%i : ", cubes[x][y][z].index);
						value.a = triTable[chunk->indices[x][y][z]][i];
						value.b = triTable[chunk->indices[x][y][z]][i + 1];
						value.c = triTable[chunk->indices[x][y][z]][i + 2];


						vec3 tempVecs[3];

						glm_vec3_sub(cubes[x][y][z].verts[value.b].pos, cubes[x][y][z].verts[value.a].pos, tempVecs[0]);
						glm_vec3_sub(cubes[x][y][z].verts[value.c].pos, cubes[x][y][z].verts[value.a].pos, tempVecs[1]);

						glm_cross(tempVecs[0], tempVecs[1], tempVecs[2]);
						glm_vec3_normalize(tempVecs[2]);


						glm_vec3_copy(tempVecs[2], cubes[x][y][z].verts[value.a].normal);
						glm_vec3_copy(tempVecs[2], cubes[x][y][z].verts[value.b].normal);
						glm_vec3_copy(tempVecs[2], cubes[x][y][z].verts[value.c].normal);


						chunk->verts.l[activeVert] = cubes[x][y][z].verts[value.a];
						chunk->verts.l[activeVert + 1] = cubes[x][y][z].verts[value.b];
						chunk->verts.l[activeVert + 2] = cubes[x][y][z].verts[value.c];

						activeVert += 3;
					}
				}
			}
		}

		chunk->mesh = CreateMesh2(chunk->verts.l, chunk->verts.count * sizeof(Vertex), GL_DYNAMIC_DRAW);
	}

	Vertex VertInterp(vec3 aPos, float aVal, vec3 aCol, vec3 bPos, float bVal, vec3 bCol)
	{
		Vertex result;

		if (bVal - aVal == 0)
		{
			result.pos[0] = (aPos[0] + bPos[0]) * 0.5f;
			result.pos[1] = (aPos[1] + bPos[1]) * 0.5f;
			result.pos[2] = (aPos[2] + bPos[2]) * 0.5f;
		}
		else
		{
			float mu = (isoLevel - aVal) / (bVal - aVal);


			result.pos[0] = aPos[0] + mu * (bPos[0] - aPos[0]);
			result.pos[1] = aPos[1] + mu * (bPos[1] - aPos[1]);
			result.pos[2] = aPos[2] + mu * (bPos[2] - aPos[2]);

			result.color[0] = aCol[0] + mu * (bCol[0] - aCol[0]);
			result.color[1] = aCol[1] + mu * (bCol[1] - aCol[1]) + 0.5f;
			result.color[2] = aCol[2] + mu * (bCol[2] - aCol[2]);
		}
		return result;
	}

	void GenerateChunk(Chunk* chunk, CaveNoise c)
	{
		//float _min = 0.0f, _max = 0.0f, average = 0.0f;
		float height;

		for (int x = 0; x < (chunkWidth + 1); x++)
			for (int y = 0; y < (chunkWidth + 1); y++)
				for (int z = 0; z < (chunkWidth + 1); z++)
				{
					height = -(((float)y / chunkWidth) + chunk->pos[1]);
					chunk->tiles[x][y][z] = max(0, min(1, max(0, min(1, GenerateCaveNoiseValue(c, 0.025f, 0.0f, 0, 2, (vec3) { x + chunk->pos[0] * chunkWidth - (chunkWidth / 2), y + chunk->pos[1] * chunkWidth - (chunkWidth / 2), z + chunk->pos[2] * chunkWidth - (chunkWidth / 2) }) - height / 10.0f)) + GenerateCaveNoiseValue(c, 0.0125f, /*max(0, glm_signf(-height + 1) * (-height / (-height + 1)))*/0.25f, 4, 2, (vec3) { x + chunk->pos[0] * chunkWidth - (chunkWidth / 2), y + chunk->pos[1] * chunkWidth - (chunkWidth / 2), z + chunk->pos[2] * chunkWidth - (chunkWidth / 2) })));
					chunk->colors[x][y][z][0] = max(0, min(1, GenerateCaveNoiseValue(c, 0.01f, 0.0f, 1, 1, (vec3) { x + chunk->pos[0] * chunkWidth - (chunkWidth / 2), y + chunk->pos[1] * chunkWidth - (chunkWidth / 2), z + chunk->pos[2] * chunkWidth - (chunkWidth / 2) })));
					chunk->colors[x][y][z][1] = max(0, min(1, GenerateCaveNoiseValue(c, 0.01f, 0.0f, 2, 1, (vec3) { x + chunk->pos[0] * chunkWidth - (chunkWidth / 2), y + chunk->pos[1] * chunkWidth - (chunkWidth / 2), z + chunk->pos[2] * chunkWidth - (chunkWidth / 2) })));
					chunk->colors[x][y][z][2] = max(0, min(1, GenerateCaveNoiseValue(c, 0.01f, 0.0f, 3, 1, (vec3) { x + chunk->pos[0] * chunkWidth - (chunkWidth / 2), y + chunk->pos[1] * chunkWidth - (chunkWidth / 2), z + chunk->pos[2] * chunkWidth - (chunkWidth / 2) })));
					//_min = min(_min, chunk->tiles[x][y][z]);
					//_max = max(_max, chunk->tiles[x][y][z]);
					//average += chunk->tiles[x][y][z];
					//printf("%f  ", chunk->tiles[x][y][z]);
				}
		//average /= (chunkWidth + 1) * (chunkWidth + 1) * (chunkWidth + 1);
		//printf("%f, ", average);
		//printf("(%f, %f, %f)", min, max, average);
		//printf("%f, ", height);
	}

	void CreateWorld(World* world, Camera camera, float chunkRenderDist)
	{
		// Prepare for multithreading:
		// Setup OpenCL.
		cl_device_id device;
		cl_platform_id platform = NULL;
		cl_uint ret_num_devices;
		cl_uint ret_num_platforms;
		cl_int ret = clGetPlatformIDs(1, &platform, &ret_num_platforms);
		ret = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &ret_num_devices);
		world->context = clCreateContext(NULL, 1, &device, NULL, NULL, &ret);
		world->queue = clCreateCommandQueueWithProperties(world->context, device, (cl_queue_properties)0, NULL);

		// Create memory buffers on the device for each vector.
		world->memObjWorld = clCreateBuffer(world->context, CL_MEM_READ_WRITE, sizeof(World), NULL, &ret);
		world->memObjOffset = clCreateBuffer(world->context, CL_MEM_READ_ONLY, sizeof(unsigned int), NULL, &ret);

		// Copy the world into it's respective place.
		ret = clEnqueueWriteBuffer(world->queue, world->memObjWorld, CL_TRUE, 0, sizeof(World), world, 0, NULL, NULL);
		unsigned int zero = 0;
		ret = clEnqueueWriteBuffer(world->queue, world->memObjOffset, CL_TRUE, 0, sizeof(unsigned int), &zero, 0, NULL, NULL);

		// Load the kernel source code into the array source_str.
		FILE* fp;
		char* source;
		size_t source_size;

		fp = fopen("kernels/MarchingCubes.txt", "r");
		if (!fp) {
			fprintf(stderr, "Failed to load kernel.\n");
			exit(1);
		}
		#define MAX_SOURCE_SIZE (0x11111111)
		source = (char*)malloc(MAX_SOURCE_SIZE);
		source_size = fread(source, 1, MAX_SOURCE_SIZE, fp);
		fclose(fp);

		// Compile the kernel.
		world->program = clCreateProgramWithSource(world->context, 1, (const char**)&source, NULL, NULL);
		clBuildProgram(world->program, 0, NULL, NULL, NULL, NULL);
		world->kernel = clCreateKernel(world->program, "GenerateChunkMesh", NULL);

		// Set the arguments of the kernel
		ret = clSetKernelArg(world->kernel, 0, sizeof(cl_mem), (void*)&world->memObjWorld);
		ret = clSetKernelArg(world->kernel, 1, sizeof(cl_mem), (void*)&world->memObjOffset);

			// Do actual marching cubes stuff now:
		vec3 localizedCamPos;
		ivec3 minPos, maxPos;

		localizedCamPos[0] = camera.pos[0] / chunkWidth;
		localizedCamPos[1] = camera.pos[1] / chunkWidth;
		localizedCamPos[2] = camera.pos[2] / chunkWidth;

		minPos[0] = roundf(localizedCamPos[0] - chunkRenderDist);
		minPos[1] = roundf(localizedCamPos[1] - chunkRenderDist);
		minPos[2] = roundf(localizedCamPos[2] - chunkRenderDist);

		maxPos[0] = roundf(localizedCamPos[0] + chunkRenderDist);
		maxPos[1] = roundf(localizedCamPos[1] + chunkRenderDist);
		maxPos[2] = roundf(localizedCamPos[2] + chunkRenderDist);

		//int i = 0;
		for (int x = minPos[0]; x <= maxPos[0]; x++)
			for (int y = minPos[1]; y <= maxPos[1]; y++)
				for (int z = minPos[2]; z <= maxPos[2]; z++)
					if (glm_vec3_distance2(localizedCamPos, (vec3) { x, y, z }) < chunkRenderDist* chunkRenderDist)
					{
						IncreaseChunkList(&world->chunks, 1);
						world->chunks.l[world->chunks.count - 1].pos[0] = x;
						world->chunks.l[world->chunks.count - 1].pos[1] = y;
						world->chunks.l[world->chunks.count - 1].pos[2] = z;
						GenerateChunk(&world->chunks.l[world->chunks.count - 1], world->noise);
						GenerateChunkMesh1(&world->chunks.l[world->chunks.count - 1]);
					}

		size_t global_dimensions[] = { world->chunks.count, 0, 0 };

		clEnqueueNDRangeKernel(world->queue, world->kernel, 1, NULL, global_dimensions, NULL, 0, NULL, NULL);

		// Read back the results.
		ret = clEnqueueReadBuffer(world->queue, world->memObjWorld, CL_TRUE, 0,
			sizeof(World), world, 0, NULL, NULL);

		ret = clFlush(world->queue);
		ret = clFinish(world->queue);
	}

void UpdateWorld(World* world, Camera camera, float chunkRenderDist)
{
	int i = 0;

	#pragma region Delete out of range chunks
	while (true)
	{
		if (i >= world->chunks.count)
			break;

		if (glm_vec3_distance((vec3) { world->chunks.l[i].pos[0] * chunkWidth, world->chunks.l[i].pos[1] * chunkWidth, world->chunks.l[i].pos[2] * chunkWidth }, camera.pos) > chunkRenderDist * chunkWidth)
			RemoveFromChunkList(&world->chunks, i);
		else
			i++;
	}
	#pragma endregion

	#pragma region Add new chunks that are in range

	vec3 localizedCamPos;
	ivec3 minPos, maxPos;

	localizedCamPos[0] = camera.pos[0] / chunkWidth;
	localizedCamPos[1] = camera.pos[1] / chunkWidth;
	localizedCamPos[2] = camera.pos[2] / chunkWidth;

	minPos[0] = roundf(localizedCamPos[0] - chunkRenderDist);
	minPos[1] = roundf(localizedCamPos[1] - chunkRenderDist);
	minPos[2] = roundf(localizedCamPos[2] - chunkRenderDist);

	maxPos[0] = roundf(localizedCamPos[0] + chunkRenderDist);
	maxPos[1] = roundf(localizedCamPos[1] + chunkRenderDist);
	maxPos[2] = roundf(localizedCamPos[2] + chunkRenderDist);

	//int i = 0;
	for (int x = minPos[0]; x <= maxPos[0]; x++)
		for (int y = minPos[1]; y <= maxPos[1]; y++)
			for (int z = minPos[2]; z <= maxPos[2]; z++)
				if (glm_vec3_distance2(localizedCamPos, (vec3) { x, y, z }) < chunkRenderDist * chunkRenderDist) // Chunk render distance is squared because glm_vec3_distanc2 squares the distance.
				{
					bool skip = false;
					for (i = 0; i < world->chunks.count; i++)
						skip = (glm_vec3_eqv((vec3) { x, y, z }, (vec3) { world->chunks.l[i].pos[0], world->chunks.l[i].pos[1], world->chunks.l[i].pos[2] }) ? true : skip);

					if (!skip)
					{
						//printf("(%i, %i, %i, %i) : %f, ", x, y, z, i, dist);
						IncreaseChunkList(&world->chunks, 1);
						world->chunks.l[world->chunks.count - 1].pos[0] = x;
						world->chunks.l[world->chunks.count - 1].pos[1] = y;
						world->chunks.l[world->chunks.count - 1].pos[2] = z;
						GenerateChunk(&world->chunks.l[world->chunks.count - 1], world->noise);
						GenerateChunkMesh(&world->chunks.l[world->chunks.count - 1]);
						return;
						//printf("%i, ", world->chunks.count);
					}
				}
	#pragma endregion
}