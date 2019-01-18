#include "TestKernel.h"
#include "OpenCL.h"
#include "LogManager.h"
#include "Settings.h"
#include "Kernel.h"

static cl_kernel kernel;



int clCreateTestKernel(const char* filename)
{
	int result;
	char* filenames[1];
	filenames[0] = filename;

	result = clCreateKernelFromFiles(&kernel, "testKernel", filenames, 1);
	if (!result)
	{
		logs("can't create test kernel");
		return 0;
	}

	return 1;
}

int clExecuteTestKernel(int* x, int* y, int* r)
{
	int result;
	size_t globalWorkSize[2];
	cl_mem outBuffer = clGetOutBuffer();

	// put work size
	globalWorkSize[0] = setsGetScreenWidth();
	globalWorkSize[1] = setsGetScreenHeight();


	result = clExecuteKernel(kernel, clGetMainQueue(), globalWorkSize, 2, 4, x, sizeof(int), y, sizeof(int), r, sizeof(int), &outBuffer, sizeof(cl_mem));
	if (!result)
	{
		logs("can't execute test kernel");
		return 0;
	}


	return 1;
}

void clShutdownTestKernel()
{
	clReleaseKernel(kernel);
}