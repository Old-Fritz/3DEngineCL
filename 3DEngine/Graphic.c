#include "Graphic.h"
#include "LogManager.h"
#include "Settings.h"
#include "Window.h"
#include "OpenCL.h"

int grInit()
{
	if (!winInit(setsGetScreenWidth(), setsGetScreenHeight()))
	{
		logs("cant't create window");
		return 0;
	}
	logs("create window");

	if(!clInit(setsGetScreenWidth(), setsGetScreenHeight(),3))
	{
		logs("cant't init OpenCL");
		return 0;
	}
	logs("init openCL context");

	return 1;
}

int grFrame()
{
	if (!clSwapBuffers())
		return 0;
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

