#include "Shader.h"
#include "OpenCL.h"
#include <stdlib.h>
#include "LogManager.h"
#include "Kernel.h"
#include "Settings.h"
#include "GraphicSystem.h"
#include <string.h>


static struct ShaderElement
{
	struct _grVertexBuffer vertexBuffer;
	struct _grIndexBuffer indexBuffer;
	int primitiveCountEnd;
};

typedef struct ShaderElement ShaderElement;

struct _grShader
{
	cl_command_queue queue;
	cl_kernel kernel;
	cl_mem shaderGlobalBuffer;
	cl_mem elementsBuffer;
	cl_mem paramsBuffer;
	ShaderElement* shaderElements;
	void* params;
	size_t paramsSize;
	int elementsCapacity;
	int elementsCount;
};

// Create shader and initialize it from files with functions for vertex and pixel shaders
int grCreateShader(grShader* shader, const char* vsFilename, const  char* psFilename)
{
	int result;
	struct _grShader* shaderStruct = malloc(sizeof(struct _grShader));
	const char* filenames[7];

	// Create queue
	result = clCreateQueue(&(shaderStruct->queue));
	if(!result)
	{
		logs("can't create queue for shader");
		return 0;
	}

	// create kernel
	// fill filenames with parts of shader kernel
	filenames[0] = "kernels/libs/math3d.cl";
	filenames[1] = "kernels/libs/shaderBase.cl";
	filenames[2] = vsFilename;
	filenames[3] = psFilename;
	filenames[4] = "kernels/shaderBase/rasterization.cl";
	filenames[5] = "kernels/shaderBase/clipping.cl";
	filenames[6] = "kernels/shaderBase/shaderKernel.cl";

	// init kernel
	result = clCreateKernelFromFiles(&(shaderStruct->kernel), "shaderKernel", filenames, 7);
	if(!result)
	{
		logs("can't create kernel for shader");
		return 0;
	}

	// create queue of shader elements
	shaderStruct->elementsCount = 0;
	shaderStruct->elementsCapacity = 16;
	shaderStruct->paramsSize = 1;
	shaderStruct->shaderElements = malloc(sizeof(ShaderElement) * shaderStruct->elementsCapacity);
	if(!shaderStruct->shaderElements)
	{
		logs("can't craete list of shader elements");
		return 0;
	}
	shaderStruct->params = malloc(shaderStruct->paramsSize * shaderStruct->elementsCapacity);
	if (!shaderStruct->params)
	{
		logs("can't craete list of shader params");
		return 0;
	}

	// create opencl buffers for elements
	result = clCreateRWBuffer(&(shaderStruct->elementsBuffer), sizeof(ShaderElement) * shaderStruct->elementsCapacity);
	if(!result)
	{
		logs("can't create buffer for shader elements");
		return 0;
	}
	result = clCreateRWBuffer(&(shaderStruct->paramsBuffer), shaderStruct->paramsSize * shaderStruct->elementsCapacity);
	if (!result)
	{
		logs("can't create buffer for shader params");
		return 0;
	}

	// create shader global buffer
	result = clCreateRWBuffer(&(shaderStruct->shaderGlobalBuffer), sizeof(grShaderGlobal));
	if (!result)
	{
		logs("can't create shader global");
		return 0;
	}
	result = grSetDefaultShaderGlobal(shaderStruct);
	if (!result)
		return 0;

	// set new structure to output shader
	*shader = shaderStruct;

	return 1;
}

// Release shader
void grShutdownShader(grShader shader)
{
	int i;
	clReleaseMemObject(shader->shaderGlobalBuffer);
	clReleaseMemObject(shader->paramsBuffer);
	clReleaseMemObject(shader->elementsBuffer);
	free(shader->params);
	free(shader->shaderElements);
	clReleaseKernel(shader->kernel);
	clReleaseCommandQueue(shader->queue);
}

static int changeParamsArray(grShader shader, size_t newSize)
{
	int i, result;
	char* newParams = malloc(sizeof(newSize*shader->elementsCapacity));
	// change list
	if (!newParams)
	{
		logs("can't change params array");
		return 0;
	}
	for(i = 0; i<shader->elementsCount; i++)
		memcpy_s(newParams + i*newSize, newSize, shader->params, shader->paramsSize);
	free(shader->params);
	shader->paramsSize = newSize;
	shader->params = newParams;

	// change buffer
	clReleaseMemObject(shader->paramsBuffer);
	result = clCreateRWBuffer(&(shader->paramsBuffer), newSize*shader->elementsCapacity);
	if(!result)
	{
		logs("can't change params buffer");
		return 0;
	}

	return 1;
}

static int expandElementsArray(grShader shader)
{
	int result;
	// expand elements list
	ShaderElement* newElements = malloc(sizeof(ShaderElement)*shader->elementsCapacity * 2);
	if (!newElements)
	{
		logs("can't expand shader elements array");
		return 0;
	}
	memcpy_s(newElements, sizeof(ShaderElement)*shader->elementsCapacity * 2, shader->shaderElements, sizeof(ShaderElement)*shader->elementsCapacity);
	free(shader->shaderElements);
	shader->shaderElements = newElements;
	shader->elementsCapacity *= 2;

	//expand params list
	result = changeParamsArray(shader, shader->paramsSize);
	if (!result)
		return 0;

	// expand elements buffer
	clReleaseMemObject(shader->elementsBuffer);
	result = clCreateRWBuffer(&(shader->elementsBuffer), sizeof(struct ShaderElement)*shader->elementsCapacity);
	if (!result)
	{
		logs("can't expand elements buffer");
		return 0;
	}

	return  1;
}

// Add model element before execution of shader (with all models in one time)
int grAddToShaderQueue(grShader shader, grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, void* params, size_t paramsSize)
{
	int result;
	ShaderElement* newShaderElement;
	void* newParams;
	int primitiveEnd = 0;
	// double size of elemetnts array if it was filled
	if(shader->elementsCapacity==shader->elementsCount)
	{
		result = expandElementsArray(shader);
		if (!result)
			return 0;
	}

	// calculate new end of primitives
	if (shader->elementsCount)
		primitiveEnd = shader->shaderElements[shader->elementsCount - 1].primitiveCountEnd;
	// calculate count of primitives
	primitiveEnd += grGetVertexPrimitive(vertexBuffer)*grGetIndexCount(indexBuffer);

	newShaderElement = &(shader->shaderElements[shader->elementsCount]);
	newShaderElement->indexBuffer = *indexBuffer;
	newShaderElement->vertexBuffer = *vertexBuffer;
	newShaderElement->primitiveCountEnd = primitiveEnd;

	// add params
	if(shader->paramsSize!=paramsSize)
	{
		result = changeParamsArray(shader, paramsSize);
		if (!result)
			return 0;
	}
	newParams = (char*)params + paramsSize*shader->elementsCount;
	memcpy_s(newParams, paramsSize, params, paramsSize);

	shader->elementsCount++;

	return 1;
}

// Execute shader and clear shader queue
int grExecuteShader(grShader shader)
{
	int result;
	size_t globalWorkSize[1];

	// fill buffers
	result = clWriteRWBuffer(shader->elementsBuffer, sizeof(ShaderElement)*shader->elementsCount, shader->shaderElements);
	if(!result)
	{
		logs("can't set elements to shader");
		return 0;
	}
	result = clWriteRWBuffer(shader->paramsBuffer, shader->paramsSize*shader->elementsCount, shader->params);
	if (!result)
	{
		logs("can't set params to shader");
		return 0;
	}

	// set global work size
	globalWorkSize[0] = shader->shaderElements[shader->elementsCount - 1].primitiveCountEnd;

	// execute shader kernel
	result = clExecuteKernel(shader->kernel, shader->queue, globalWorkSize, 1, 4,
		shader->elementsBuffer, sizeof(cl_mem), shader->paramsBuffer, sizeof(cl_mem), shader->elementsCount, sizeof(int), shader->shaderGlobalBuffer, sizeof(cl_mem));
	if(!result)
	{
		logs("can't execute shader");
		return 0;
	}

	// clear queue
	shader->elementsCount = 0;

	return 1;
}

int grGetShaderGlobal(grShader shader, grShaderGlobal*shaderGlobal)
{
	int result;

	result = clReadRWBuffer(shader->shaderGlobalBuffer, sizeof(grShaderGlobal), shaderGlobal);
	if (!result)
	{
		logs("can't read shader global");
		return 0;
	}

	return 1;
}
int grSetShaderGlobal(grShader shader, grShaderGlobal* shaderGlobal)
{
	int result;

	result = clWriteRWBuffer(shader->shaderGlobalBuffer, sizeof(grShaderGlobal), shaderGlobal);
	if(!result)
	{
		logs("can't write shader global");
		return 0;
	}

	return 1;
}
int grSetDefaultShaderGlobal(grShader shader)
{
	int result;
	grShaderGlobal shaderGlobal;

	shaderGlobal.screenWidth = setsGetScreenWidth();
	shaderGlobal.screenHegiht = setsGetScreenHeight();
	shaderGlobal.accessBuffer = grGetAccessBuffer();
	shaderGlobal.depthBuffer = grGetDepthBuffer();
	shaderGlobal.outBuffer = clGetOutBuffer();
	shaderGlobal.farZ = grGetFarZ();
	shaderGlobal.nearZ = grGetNearZ();
	shaderGlobal.left = -setsGetScreenWidth() / 2 + 1;
	shaderGlobal.right = setsGetScreenWidth() / 2;
	shaderGlobal.top = setsGetScreenHeight() / 2;
	shaderGlobal.bottom = -setsGetScreenHeight() / 2 + 1;

	result = grSetShaderGlobal(shader, &shaderGlobal);
	if (!result)
	{
		logs("can't default shader global");
		return 0;
	}

	return  1;
}
