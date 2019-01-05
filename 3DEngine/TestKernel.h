#ifndef TEST_KERNEL_H
#define TEST_KERNEL_H

/// Simple test kernel that display circle

int clCreateTestKernel(const char* filename);
int clExecuteTestKernel(int* x, int* y, int* r);
void clShutdownTestKernel();

#endif