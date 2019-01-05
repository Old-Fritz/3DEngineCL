#include "LogManager.h"
#include "Settings.h"
#include "Graphic.h"

int sysInit()
{
	int result;

	if(!logInit())
		return 0;
	logs("log init");

	if (!setsInit("Settings.txt"))
		return 0;
	logs("set init");

	if (!grInit())
		return 0;
	logs("graphic init");

	return 1;
}

void sysRun()
{
	int result = 1;

	while(result)
	{
		if (!grFrame())
			result = 0;
	}
}

void sysShutdown()
{
	logShutdown();
}