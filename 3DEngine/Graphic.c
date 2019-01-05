#include "Graphic.h"
#include "LogManager.h"
#include "Settings.h"
#include "Window.h"
#include "OpenCL.h"
#include "KernelManager.h"

static int x = 0;
static int y;
static int r;

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

	if(!clCreateAllKernels())
	{
		logs("can't create kernels");
		return 0;
	}
	logs("init all kernels");

	y = setsGetScreenHeight() / 2;
	r = setsGetScreenHeight() / 4;

	return 1;
}

static int render()
{
	x++;
	if (x > setsGetScreenWidth())
		x = 0;

	if (!clExecuteTestKernel(&x, &y, &r))
		return  0;
}

int grFrame()
{
	// prepare old back buffer for render
	char* outBuffer;
	if (!winGetBuffer(&outBuffer))
		return 0;
	if (!clReadInBuffer(outBuffer))
		return 0;
	// swap buffer and set new back buffer
	if (!clSwapBuffers())
		return 0;
	if (!winSwapBuffers())
		return  0;

	// render to new back buffer
	if(!render())
	{
		logs("can't render graphics");
		return 0;
	}

	// show old back buffer
	if (!winRender())
		return 0;
	// finish all render job
	if (!clFinishEx())
		return 0;

	return 1;
}

void grShutdown()
{
	clShutdownAllKernels();
	clShutdown();
	winShutdown();
}

