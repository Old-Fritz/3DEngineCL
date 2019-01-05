#include "KernelManager.h"

int clCreateAllKernels()
{
	clCreateTestKernel("testKernel.cl");
}

void clShutdownAllKernels()
{
	clShutdownTestKernel();
}
