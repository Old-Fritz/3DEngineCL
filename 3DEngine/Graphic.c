#include "Graphic.h"
#include "LogManager.h"
#include "Settings.h"
#include "Window.h"

int grInit()
{
	if (!winInit(setsGetScreenWidth(), setsGetScreenHeight()))
	{
		logs("cant't create window");
		return 0;
	}
	logs("create window");

	return 1;
}

int grFrame()
{
	if (!winSwapBuffers())
		return  0;
	if (!winRender())
		return 0;

	return 1;
}

void grShutdown()
{
	winShutdown();
}

