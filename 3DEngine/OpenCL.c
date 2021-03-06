#include "OpenCL.h"
#include "LogManager.h"
#include <stdlib.h>
#include "GetGPUPtrKernel.h"

#define USED_DEVICE 0

static cl_context context;
static cl_command_queue mainQueue;
static cl_device_id deviceId;
static cl_mem backBuffer, frontBuffer, getPtrBuffer;
static void *backBufferPtr, *frontBufferPtr;
static size_t outBufferSize;

static int getDeviceId()
{
	cl_int result;
	cl_platform_id* platformIDs;
	cl_uint platformCount;

	cl_device_id* deviceIDs;
	cl_uint deviceCount;
	cl_uint maxDeviceCount = 5;
	int i;

	// get list of platforms
	result = clGetPlatformIDs(5, NULL, &platformCount);
	if (result != CL_SUCCESS)
	{
		logs("can't get list of OpenCL platforms");
		return 0;
	}
	platformIDs = malloc(platformCount * sizeof(cl_platform_id));
	if (!platformIDs)
		return 0;
	result = clGetPlatformIDs(platformCount, platformIDs, NULL);
	if (result != CL_SUCCESS)
	{
		logs("can't get list of all OpenCL platforms");
		return 0;
	}

	// Choose platform
	//...

	// get list of devices
	//result = clGetDeviceIDs(platformIDs[0], CL_DEVICE_TYPE_ALL, 5, NULL, &deviceCount);
	//if (result != CL_SUCCESS)
	//	return false;
	deviceIDs = malloc(maxDeviceCount * sizeof(cl_device_id));
	if (!deviceIDs)
		return 0;
	result = clGetDeviceIDs(platformIDs[0], CL_DEVICE_TYPE_GPU, maxDeviceCount, deviceIDs, &deviceCount);
	if (result != CL_SUCCESS)
	{
		logs("can't get list of all OpenCL devices");
		return 0;
	}
	// save needed device id
	deviceId = deviceIDs[USED_DEVICE];

	// free all used
	free(platformIDs);
	for (i = 0;i < deviceCount;i++)
	{
		if (i != USED_DEVICE)
		{
			result = clReleaseDevice(deviceIDs[i]);
			if (result != CL_SUCCESS)
			{
				logs("can't release temp device");
				return 0;
			}
		}
	}
	free(deviceIDs);

	return 1;
}

static int createContextAndQueue()
{
	cl_int result;

	result = getDeviceId();
	if(!result)
	{
		logs("can't select any openCL device");
		return 0;
	}
	// create context
	context = clCreateContext(NULL, 1, &deviceId, NULL, NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create context");
		return 0;
	}

	// create command queue
	result = clCreateQueue(&mainQueue);
	if (!result)
	{
		logs("can't create main queue");
		return 0;
	}

	return 1;
}

static int createOutBuffers()
{
	int result;

	result = clCreateRWBuffer(&backBuffer, outBufferSize);
	if (!result)
		return 0;

	result = clCreateRWBuffer(&frontBuffer, outBufferSize);
	if (!result)
		return 0;

	return 1;
}

int clInit(int width, int height, size_t pixelSize)
{
	int result;

	result = createContextAndQueue();
	if (!result)
		return 0;

	outBufferSize = width*height*pixelSize;
	result = createOutBuffers();
	if (!result)
	{
		logs("can't create out buffers");
		return 0;
	}

	result = clCreateRWBuffer(&getPtrBuffer, sizeof(void*));
	if(!result)
	{
		logs("can't create buffer for getting pointer");
		return 0;
	}

	return 1;
}

// Get components of device
cl_mem clGetOutBuffer()
{
	return backBuffer;
}
void* clGetOutBufferPtr()
{
	return backBufferPtr;
}
cl_context clGetContext()
{
	return context;
}
cl_command_queue clGetMainQueue()
{
	return mainQueue;
}

int clSetOutBufferPtrs()
{
	backBufferPtr = clGetGPUPtr(backBuffer);
	if (!backBufferPtr)
		return 0;
	frontBufferPtr = clGetGPUPtr(frontBuffer);
	if (!frontBufferPtr)
		return 0;

	return 1;
}

int clCreateQueue(cl_command_queue* queue)
{
	cl_int result;

	// create command queue
	*queue = clCreateCommandQueueWithProperties(context, deviceId, NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create queue");
		return 0;
	}

	return 1;
}

int clCreateRWBuffer(cl_mem* buffer, size_t size)
{
	cl_int result;

	*buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create open cl buffer");
		return 0;
	}

	return 1;
}

int clReadRWBuffer(cl_mem buffer, size_t size, void* ptr)
{
	cl_int result;

	result = clEnqueueReadBuffer(mainQueue, buffer, CL_BLOCKING, 0, size, ptr, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		logs("can't read OpenCL buffer");
		return 0;
	}

	return 1;
}

int clWriteRWBuffer(cl_mem buffer, size_t size, void* ptr)
{
	cl_int result;

	result = clEnqueueWriteBuffer(mainQueue, buffer, CL_BLOCKING, 0, size, ptr, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		logs("can't write in OpenCL buffer");
		return 0;
	}

	return 1;
}

void* clGetGPUPtr(cl_mem buffer)
{
	int result;
	void* ptr;

	result = clExecuteGetGPUPtrKernel(buffer, getPtrBuffer);
	if(!result)
	{
		logs("can't get buffer pointer");
		return 0;
	}

	result = clReadRWBuffer(getPtrBuffer, sizeof(void*), &ptr);
	if(!result)
	{
		logs("can't read buffer pointer");
		return 0;
	}

	return ptr;
}


int clSwapBuffers()
{
	void* tempPtr;
	cl_mem temp = backBuffer;
	backBuffer = frontBuffer;
	frontBuffer = temp;

	tempPtr = backBufferPtr;
	backBufferPtr = frontBufferPtr;
	frontBufferPtr = tempPtr;

	return  1;
}

int clReadInBuffer(void* buffer)
{
	cl_int result;
	// write to output
	result = clEnqueueReadBuffer(mainQueue, backBuffer, CL_NON_BLOCKING, 0, outBufferSize, buffer, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		logs("can't read OpenCL out buffer");
		return 0;
	}

	return 1;
}


int clFinishEx()
{
	cl_int result;

	result = clFinish(mainQueue);
	if (result != CL_SUCCESS)
	{
		logs("can't finish queue");
		return 0;
	}

	return 1;
}

void clShutdown()
{
	clReleaseMemObject(getPtrBuffer);
	clReleaseContext(context);
	clReleaseCommandQueue(mainQueue);
	clReleaseMemObject(backBuffer);
	clReleaseMemObject(frontBuffer);
}