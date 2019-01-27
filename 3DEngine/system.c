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
	int result, i, k;
	int runProgram = 1;

	while(runProgram)
	{
		for(k = 0; k < 1000;k++)
		{
			for(i = 0; i < 60;i++)
			{
				tmFrame();
				result = grFrame();
				if (!result)
					runProgram = 0;
			}
		}
	}
	runProgram = k;
}

void sysShutdown()
{
	logShutdown();
}