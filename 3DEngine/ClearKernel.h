#ifndef CLEAR_KERNEL_H
#define CLEAR_KERNEL_H
#include <CL/cl.h>

/// Kernel to fill buffer with one value for each element

int clCreateClearKernel(const char* filename);
int clExecuteClearKernel(cl_mem buffer, int width, int height, int bufferElementSize, int valuesCount, float* values[4]);
void clShutdownClearKernel();

#endif
