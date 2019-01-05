#include <stdio.h>
#include "LogManager.h"
#include <direct.h>
#include <string.h>
#include <time.h>

static const char* logDirName = "log/";
static FILE* file;


static int getTimeStr(char* str)
{
	int result;
	char dateStr[9];
	char timeStr[9];

	//get time and data from system
	result = _strdate_s(dateStr, 9);
	if (result)
		return 0;

	result = _strtime_s(timeStr, 9);
	if (result)
		return 0;

	// format string
	dateStr[2] = '-';
	dateStr[5] = '-';
	timeStr[2] = '-';
	timeStr[5] = '-';

	strcat_s(str, 128, dateStr);
	strcat_s(str, 128, "_");
	strcat_s(str, 128, timeStr);

	return 1;
}

static int createLogDir()
{
	return _mkdir(logDirName);
}

int logInit()
{
	int result;
	char filename[256] = "";
	char timeStr[128] = "";

	result = createLogDir();
	if (!result)
		return 0;

	result = getTimeStr(timeStr);
	if (!result)
		return 0;

	// form filename for log file
	strcat_s(filename, 256, logDirName);
	strcat_s(filename, 256, "log");
	strcat_s(filename, 256,  timeStr);
	strcat_s(filename, 256, ".txt");

	result = fopen_s(&file, filename, "w");
	if (result)
		return 0;

	return 1;
}

int logs(const char* text)
{
	char logStr[130] = "";
	char timeStr[128] = "";
	int result;

	result = getTimeStr(timeStr);
	if (!result)
		return 0;

	strcat_s(logStr, 130, "\n");
	strcat_s(logStr, 130, timeStr);
	strcat_s(logStr, 130, " ");


	if (file)
	{
		fprintf(file, logStr);
		fprintf(file, text);
	}
	else
		return 0;

	return 1;

}


int logsNum(double number)
{
	char numStr[64];
	int result;

	result = sprintf_s(numStr, 64, "%.10f", number);
	if (!result)
		return 0;

	return logs(numStr);
}

void logShutdown()
{
	fclose(file);
}