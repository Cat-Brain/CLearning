/*#pragma once

#include <errno.h>
#include <stdio.h>
#include <string.h>

void OpenFile(FILE* result, char* filePath, char* mode)
{
	errno_t err;

	if ((err = fopen_s(&result, filePath, mode)) != 0)
	{
		printf(stderr);
		printf("\nCannot open file ");
		printf(filePath);
		printf("\n");
	}

	return;
}*/