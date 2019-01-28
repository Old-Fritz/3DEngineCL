#include "LogManager.h"
#include "Settings.h"
#include "Graphic.h"
#include "Timer.h"

int sysInit()
{
	int result;

	result = logInit();
	if(!result)
		return 0;
	logs("log init");

	result = setsInit("Settings.txt");
	if (!result)
		return 0;
	logs("set init");

	result = grInit();
	if (!result)
		return 0;
	logs("graphic init");

	result = tmInit();
	if (!result)
		return 0;

	return 1;
}

void sysRun()
{
	int result;
	int runProgram = 1;

	while(runProgram)
	{
		tmFrame();
		result = grFrame();
		if (!result)
			runProgram = 0;
	}
}

void sysShutdown()
{
	logShutdown();
}