#include "Shader.h"
#include "OpenCL.h"
#include <stdlib.h>
#include "LogManager.h"
#include "Kernel.h"

static struct ShaderElement
{
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;
	void* params;
	long primitiveCountEnd;
};
typedef struct ShaderElement ShaderElement;

struct _grShader
{
	cl_command_queue queue;
	cl_kernel kernel;
	struct ShaderElement* shaderElements;
	int elementsCapacity;
	int elementsCount;
};

// Create shader and initialize it from files with functions for vertex and pixel shaders
int grCreateShader(grShader* shader, char* vsFilename, char* psFilename)
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
	filenames[0] = "kernels/math3d.cl";
	filenames[1] = vsFilename;
	filenames[2] = psFilename;
	filenames[3] = "kernels/shaderBase/clipping.cl";
	filenames[4] = "kernels/shaderBase/depth.cl";
	filenames[5] = "kernels/shaderBase/rasterization.cl";
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
	shaderStruct->shaderElements = malloc(sizeof(ShaderElement) * shaderStruct->elementsCapacity);
	if(!shaderStruct->shaderElements)
	{
		logs("can't craete list of shader elements");
		return 0;
	}

	// set new structure to output shader
	*shader = shaderStruct;

	return 1;
}

// Release shader
void grShutdownShader(grShader shader)
{
	int i;
	for (i = 0;i < shader->elementsCount;i++)
		free(shader->shaderElements[i].params);
	free(shader->shaderElements);
	clReleaseKernel(shader->kernel);
	clReleaseCommandQueue(shader->queue);
}

static int expandElementsArray(grShader shader)
{
	int i;
	ShaderElement* newElements = malloc(sizeof(ShaderElement)*shader->elementsCapacity * 2);
	if (!newElements)
	{
		logs("can't expand shader elements array");
		return 0;
	}
	for (i = 0;i < shader->elementsCount;i++)
		newElements[i] = shader->shaderElements[i];
	free(shader->shaderElements);
	shader->shaderElements = newElements;
	shader->elementsCapacity *= 2;
}

// Add model element before execution of shader (with all models in one time)
int grAddToShaderQueue(grShader shader, grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, void* params)
{
	ShaderElement* newShaderElement;
	int primitiveEnd = 0;
	// double size of elemetnts array if it was filled
	if(shader->elementsCapacity==shader->elementsCount)
		expandElementsArray(shader);

	// calculate new end of primitives
	if (shader->elementsCount)
		primitiveEnd = shader->shaderElements[shader->elementsCount - 1].primitiveCountEnd;
	// calculate count of primitives
	primitiveEnd += grGetVertexPrimitive(vertexBuffer)*grGetIndexCount(indexBuffer);

	newShaderElement = &(shader->shaderElements[shader->elementsCount++]);
	newShaderElement->params = params;
	newShaderElement->indexBuffer = indexBuffer;
	newShaderElement->vertexBuffer = vertexBuffer;
	newShaderElement->primitiveCountEnd = primitiveEnd;

	return 1;
}

// Execute shader and clear shader queue
int grExecuteShader(grShader shader)
{
	
}