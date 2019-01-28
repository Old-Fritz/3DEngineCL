#include "Graphic.h"
#include "LogManager.h"
#include "Settings.h"
#include "Window.h"
#include "OpenCL.h"
#include "KernelManager.h"
#include "GraphicSystem.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "LightModel.h"
#include "DiffuseLight.h"
#include "LSLMRenderer.h"
#include "PSPSRenderer.h"
#include "Timer.h"
#include "ParticlesSystem.h"

static mdLightModel model1, model2, model3;
static mdParticlesSystem particles;
static mdDiffuseLight light;
static int lightChangeSize = 1;
static float lightPos = 0;

static int createScene()
{
	int result;

	result = mdLightCreate(&model1, "models/cube.txt");
	if (!result)
		return 0;
	model1.color.x = 255;
	mdMove(&(model1.model), -0.5, 0.5, 5);
	mdRotate(&(model1.model), 1.3, 1.3, -0.5);

	result = mdLightCreate(&model2, "models/cube.txt");
	if (!result)
		return 0;
	model2.color.y = 255;
	mdMove(&(model2.model), 0.5, -0.5, 5);
	mdRotate(&(model2.model), 0, 1.3, -0.5);

	result = mdLightCreate(&model3, "models/cube.txt");
	if (!result)
		return 0;
	model3.color.z = 255;
	mdMove(&(model3.model), 1, 0.5, 6);
	mdRotate(&(model3.model),0.7, 0, -1.5);

	result = mdParticlesSystemCreate(&particles, 10000);
	if (!result)
		return 0;
	mdMove(&(particles.model), 1, 0.5, 6);

	result = mdDiffuseLightCreate(&light);
	if (!result)
		return 0;

	light.color.x = 255;
	light.intencity = 0.8;

	mdMove(&(light.model), 0, 8, -2);

	grCameraMove(0, 2.5, 0);
	grCameraRotate(0, 0.4, 0);

	return 1;
}

static int renderScene()
{
	int result;
	m3dVector3 lightPos;
	

	// move light
	mdGetPosition(&(light.model), &lightPos);
	lightPos.x += lightChangeSize*tmFrameTime()*20;
	if (lightPos.x > 60)
	{
		lightPos.x = 60;
		lightChangeSize = -1; 
	}
	else if (lightPos.x < -60)
	{
		lightPos.x = -60;
		lightChangeSize = 1;
	}
	mdSetPosition(&(light.model), &lightPos);
	mdRotate(&(model1.model), tmFrameTime()*0.3, 0,0);
	mdRotate(&(model2.model), 0, tmFrameTime()*0.3, 0);
	mdRotate(&(model3.model), 0,0,tmFrameTime()*0.3);

	// render models

	result = renderLSLM(&model1, &light);
	if (!result)
		return 0;

	result = renderLSLM(&model2, &light);
	if (!result)
		return 0;

	result = renderLSLM(&model3, &light);
	if (!result)
		return 0;

	result = renderPSPS(&particles, tmFrameTime()*0.3);
	if (!result)
		return 0;

	return 1;
}

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

	result = createScene();
	if(!result)
	{
		logs("can't create scene");
		return 0;
	}

	return 1;
}

static int render()
{
	int result;
	m3dVector4 color = { 30,30,30,0 };

	
	result = grClearBuffers(color);
	if(!result)
		return  0;

	result = renderScene();
	if (!result)
		return  0;

	return 1;
}

int grFrame()
{
	int result = 1;
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

	// finish old execution
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

