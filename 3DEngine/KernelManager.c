#include "KernelManager.h"


int clCreateAllKernels()
{
	int result = clCreateTestKernel("testKernel.cl");
	if (!result)
		return 0;
}

void clShutdownAllKernels()
{
	clShutdownTestKernel();
}

