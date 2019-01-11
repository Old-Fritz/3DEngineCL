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
	int result;

	result = winInit(setsGetScreenWidth(), setsGetScreenHeight());
	if (!result)
	{
		logs("cant't create window");
		return 0;
	}
	logs("create window");

	result = clInit(setsGetScreenWidth(), setsGetScreenHeight(), 3);
	if (!result)
	{
		logs("cant't init OpenCL");
		return 0;
	}
	logs("init openCL context");

	result = clCreateAllKernels();
	if (!result)
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
	int result;

	x++;
	if (x > setsGetScreenWidth())
		x = 0;

	result = clExecuteTestKernel(&x, &y, &r);
	if(!result)
		return  0;

	return 1;
}

int grFrame()
{
	int result;
	char* outBuffer;

	// prepare old back buffer for render
	result = winGetBuffer(&outBuffer);
	if (!result)
		return 0;
	result = clReadInBuffer(outBuffer);
	if (!result)
		return 0;
	// swap buffer and set new back buffer
	result = clSwapBuffers();
	if (!result)
		return 0;
	result = winSwapBuffers();
	if (!result)
		return  0;

	// render to new back buffer
	result = render();
	if (!result)
	{
		logs("can't render graphics");
		return 0;
	}

	// show old back buffer
	result = winRender();
	if (!result)
		return 0;
	// finish all render job
	result = clFinishEx();
	if (!result)
		return 0;

	return 1;
}

void grShutdown()
{
	clShutdownAllKernels();
	clShutdown();
	winShutdown();
}

