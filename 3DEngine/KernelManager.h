#ifndef KERNEL_MANAGER_H
#define KERNEL_MANAGER_H
#include "TestKernel.h"
#include "OpenCL.h"

/// United control of creating and releasing all kernels

// Initialize all kernels
int clCreateAllKernels();
// Release all resources connected with kernels
void clShutdownAllKernels();
// Create kernel from file
int clCreateKernelFromFiles(cl_kernel* kernel, const char* kernelName, const char** filenames, int filesCount);
// Execute kernel with set of arguments (after every argement size is required)
int clExecuteKernel(cl_kernel kernel, cl_command_queue queue, size_t* globalWorkSize, int argsCount, ...);

#endif