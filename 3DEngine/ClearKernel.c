#include "ClearKernel.h"
#include "Kernel.h"
#include "LogManager.h"

static cl_kernel kernel;

int clCreateClearKernel(const char* filename)
{
	int result;
	const char* filenames[1];
	filenames[0] = filename;

	result = clCreateKernelFromFiles(&kernel, "clearKernel", filenames, 1);
	if (!result)
	{
		logs("can't create clear kernel");
		return 0;
	}

	return 1;
}

int clExecuteClearKernel(cl_mem buffer, int width, int height, int bufferElementSize, int valuesCount, float values[4])
{
	int result;
	size_t globalWorkSize[3];

	// put work size
	globalWorkSize[0] = width;
	globalWorkSize[1] = height;
	globalWorkSize[2] = valuesCount;


	result = clExecuteKernel(kernel, clGetMainQueue(), globalWorkSize, 3, 3, &buffer, sizeof(cl_mem), &bufferElementSize, sizeof(int), values,  sizeof(float)*4);
	if (!result)
	{
		logs("can't execute clear kernel");
		return 0;
	}


	return 1;
}

void clShutdownClearKernel()
{
	clReleaseKernel(kernel);
}