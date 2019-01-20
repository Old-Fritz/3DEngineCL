#include "KernelManager.h"
#include "GraphicSystem.h"
#include "LogManager.h"


int clCreateAllKernels()
{
	int result;
	
	result = clCreateTestKernel("kernels/testKernel.cl");
	if (!result)
		return 0;

	result = clCreateClearKernel("kernels/clearKernel.cl");
	if (!result)
		return 0;

	result = clCreateGetGPUPtrKernel("kernels/getGPUPtr.cl");
	if (!result)
		return 0;

	result = clSetOutBufferPtrs();
	if (!result)
	{
		logs("can't get ptrs for openCL out buffers");
		return 0;
	}

	return 1;
}

void clShutdownAllKernels()
{
	clShutdownGetGPUPtrKernel();
	clShutdownClearKernel();
	clShutdownTestKernel();
}

