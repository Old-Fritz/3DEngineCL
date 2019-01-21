#include "Graphic.h"
#include "LogManager.h"
#include "Settings.h"
#include "Window.h"
#include "OpenCL.h"
#include "KernelManager.h"
#include "GraphicSystem.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "SimpleModel.h"
#include "SSSMRenderer.h"

static int x = 0;
static int y;
static int r;
static mdSimpleModel model;
static mdSimpleModel model2;

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

	result = grInitGraphicSystem();
	if(!result)
	{
		logs("can't init graphic system");
		return 0;
	}

	result = grCameraInit();
	if(!result)
	{
		logs("can't init camera");
		return 0;
	}

	result = clCreateAllKernels();
	if (!result)
	{
		logs("can't create kernels");
		return 0;
	}
	logs("init all kernels");

	result = grCreateAllShaders();
	if(!result)
	{
		logs("can't create shaders");
		return 0;
	}

	y = setsGetScreenHeight() / 2;
	r = setsGetScreenHeight() / 4;

	result = mdSimpleCreate(&model);
	if (!result)
		return 0;

	model.color.y = 255;

	result = mdSimpleCreate(&model2);
	if (!result)
		return 0;

	model2.color.x = 255;

	return 1;
}

static int render()
{
	int result;
	m3dVector4 color = { 30,30,30,0 };

	x++;
	if (x > setsGetScreenWidth())
		x = 0;

	
	result = grClearBuffers(color);
	if(!result)
		return  0;

	//result = clExecuteTestKernel(&x, &y, &r);
	result = renderSSSM(&model);
	if(!result)
		return  0;

	//result = renderSSSM(&model2);
	//if (!result)
	//	return  0;

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

	// finish all sub job
	result = clFinishEx();
	if (!result)
		return 0;

	result = grExecuteAllShaders();
	if (!result)
		return 0;

	// show old back buffer
	result = winRender();
	if (!result)
		return 0;

	result = grFinishAllShaders();
	if (!result)
		return 0;

	return 1;
}

void grShutdown()
{
	grShutdownAllShaders();
	grShutdownGraphicSystem();
	clShutdownAllKernels();
	clShutdown();
	winShutdown();
}

