#ifndef TEST_KERNEL_H
#define TEST_KERNEL_H

/// Simple test kernel that display circle

int clCreateTestKernel();
int clExecuteTestKernel(int* x, int* y, int* r);
void clShutdownTestKernel();

#endif