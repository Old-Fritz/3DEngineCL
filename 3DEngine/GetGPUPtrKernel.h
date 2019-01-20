#ifndef GET_GPU_PTR_KERNEL_H
#define GET_GPU_PTR_KERNEL_H
#include <CL/cl.h>

/// Store pointer in GPU memory space from first buffer to second

int clCreateGetGPUPtrKernel(const char* filename);
int clExecuteGetGPUPtrKernel(cl_mem sourceBuffer, cl_mem dest_buffer);
void clShutdownGetGPUPtrKernel();

#endif
