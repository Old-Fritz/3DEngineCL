#include "GetGPUPtrKernel.h"
#include "Kernel.h"
#include "LogManager.h"

static cl_kernel kernel;

int clCreateGetGPUPtrKernel(const char* filename)
{
	int result;
	const char* filenames[1];
	filenames[0] = filename;

	result = clCreateKernelFromFiles(&kernel, "getGPUPtrKernel", filenames, 1);
	if (!result)
	{
		logs("can't create getGPUPtr kernel");
		return 0;
	}

	return 1;
}

int clExecuteGetGPUPtrKernel(cl_mem sourceBuffer, cl_mem dest_buffer)
{
	int result;
	size_t globalWorkSize[3];

	// put work size
	globalWorkSize[0] = 1;

	result = clExecuteKernel(kernel, clGetMainQueue(), globalWorkSize, 1, 2, &sourceBuffer, sizeof(cl_mem), &dest_buffer, sizeof(cl_mem));
	if (!result)
	{
		logs("can't execute getGPUPtr kernel");
		return 0;
	}


	return 1;
}

void clShutdownGetGPUPtrKernel()
{
	clReleaseKernel(kernel);
}