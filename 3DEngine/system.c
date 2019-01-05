#include "LogManager.h"
#include "Settings.h"

int sysInit()
{
	int result;

	result = logInit();
	if (!result)
		return 0;
	log("log init");

	result = setsInit("Settings.txt");
	if (!result)
		return 0;
	log("set init");

	return 1;
}

void sysRun()
{
	int result = 1;

	while(result)
	{

	}
}

void sysShutdown()
{
	logShutdown();
}