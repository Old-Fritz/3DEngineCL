#ifndef OPENCL_H
#define OPENCL_H
#include <CL/cl.h>


/// Control of graphic device

// Initialize graphic context and command queue
int clInit(int width, int height, size_t pixelSize);

// Get components of device
cl_mem clGetOutBuffer();
cl_context clGetContext();
cl_command_queue clGetQueue();

// Swap current out buffer
int clSwapBuffers();
// Copy data from out buffer in simple buffer
int clReadInBuffer(void* buffer);
// Finish all commands in queue
int clFinishEx();

// Shutdown and delete all components of device
void clShutdown();

#endif