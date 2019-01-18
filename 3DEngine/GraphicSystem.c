#include "GraphicSystem.h"
#include "LogManager.h"
#include "Settings.h"
#include "ClearKernel.h"

static cl_mem depthBuffer;
static const float farZ = 1000;
static const float nearZ = 1;
static m3dMatrix worldMatrix;
static m3dMatrix projectionMatrix;

int grInitGraphicSystem()
{
	int result;

	// Create depth buffer
	result = clCreateRWBuffer(&depthBuffer, setsGetScreenWidth()*setsGetScreenHeight() * sizeof(float));
	if(!result)
	{
		logs("can't create depth buffer");
		return 0;
	}

	// Create world matrix
	m3dMatrixIdentity(&worldMatrix);

	// Crate projection matrix
	m3dMatrixPerspectiveFov(&projectionMatrix, setGetFieldOfView(), setsGetScreenWidth() / (float)setsGetScreenHeight(), nearZ, farZ);


	return 1;
}

void grShutdownGraphicSystem()
{
	clReleaseMemObject(depthBuffer);
}

m3dMatrix* grGetWorldMatrix(m3dMatrix* outMatrix)
{
	return m3dMatrixCopy(outMatrix, &worldMatrix);
}

m3dMatrix* grGetProjectionMatrix(m3dMatrix* outMatrix)
{
	return m3dMatrixCopy(outMatrix, &projectionMatrix);
}


cl_mem grGetDepthBuffer()
{
	return depthBuffer;
}
int grClearDepthBuffer()
{
	int result;
	float values[4] = { 1 / farZ,0,0,0 };

	result = clExecuteClearKernel(depthBuffer, setsGetScreenWidth(), setsGetScreenHeight(), sizeof(float), 1, values);
	if (!result)
	{
		logs("can't clear depth bufer");
		return 0;
	}


	return 1;
}
int grClearBackBuffer(m3dVector4 color)
{
	int result;

	result = clExecuteClearKernel(clGetOutBuffer(), setsGetScreenWidth(), setsGetScreenHeight(), sizeof(char), 3, &color);
	if(!result)
	{
		logs("can't clear back bufer");
		return 0;
	}

	return 1;
}

float grGetNearZ()
{
	return nearZ;
}
float grGetFarZ()
{
	return farZ;
}