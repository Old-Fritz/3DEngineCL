#ifndef KERNEL_MANAGER_H
#define KERNEL_MANAGER_H
#include "TestKernel.h"
#include "ClearKernel.h"

/// United control of creating and releasing all kernels

// Initialize all kernels
int clCreateAllKernels();
// Release all resources connected with kernels
void clShutdownAllKernels();


#endif