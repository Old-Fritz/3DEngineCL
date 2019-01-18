#ifndef KERNEL_H
#define KERNEL_H
#include "OpenCL.h"

/// Control of simple work with kernels

// Create kernel from file
int clCreateKernelFromFiles(cl_kernel* kernel, const char* kernelName, const char** filenames, int filesCount);
// Execute kernel with set of arguments (after every argement size is required)
int clExecuteKernel(cl_kernel kernel, cl_command_queue queue, size_t* globalWorkSize, int globalWorkDimensions, int argsCount, ...);

#endif