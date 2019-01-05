#include <stdio.h>
#include"Settings.h"
#include"LogManager.h"

static int screenWidth = 0;
static int screenHeight = 0;

int setsInit(const char* filename)
{
	int result;
	FILE* file;
	char parName[128];

	result = fopen_s(&file, filename, "r");
	if (result)
		return 0;

	// load screenWidth
	result = fscanf_s(file, "%s%d", parName, 128, &screenWidth);
	if (!result)
		return 0;
	logs("screenWidth is ");
	logsNum(screenWidth);

	// load screenHeight
	result = fscanf_s(file, "%s%d", parName, 128, &screenHeight);
	if (!result)
		return 0;
	logs("screenHeight is ");
	logsNum(screenHeight);

	return 1;
}

// get screen parameters
int setsGetScreenWidth()
{
	return screenWidth;
}

int setsGetScreenHeight()
{
	return screenHeight;
}