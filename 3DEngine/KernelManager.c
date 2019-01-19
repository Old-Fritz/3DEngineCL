#include "KernelManager.h"


int clCreateAllKernels()
{
	int result;
	
	result = clCreateTestKernel("kernels/testKernel.cl");
	if (!result)
		return 0;

	result = clCreateClearKernel("kernels/clearKernel.cl");
	if (!result)
		return 0;

	return 1;
}

void clShutdownAllKernels()
{
	clShutdownClearKernel();
	clShutdownTestKernel();
}

