#include "KernelManager.h"


int clCreateAllKernels()
{
	int result;
	
	result = clCreateTestKernel("testKernel.cl");
	if (!result)
		return 0;

	result = clCreateClearKernel("clearKernel.cl");
	if (!result)
		return 0;
}

void clShutdownAllKernels()
{
	clShutdownClearKernel();
	clShutdownTestKernel();
}

