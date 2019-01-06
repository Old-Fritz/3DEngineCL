#include "OpenCL.h"
#include "LogManager.h"
#include <stdlib.h>

#define USED_DEVICE 0

static cl_context context;
static cl_command_queue queue;
static cl_mem backBuffer, frontBuffer;
static size_t outBufferSize;

static int createContextAndQueue()
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

	// create context
	context = clCreateContext(NULL, 1, &deviceIDs[USED_DEVICE], NULL, NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create context");
		return 0;
	}

	// create command queue
	queue = clCreateCommandQueueWithProperties(context, deviceIDs[USED_DEVICE], NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create queue");
		return 0;
	}

	// release all
	free(platformIDs);
	for ( i = 0;i < deviceCount;i++)
	{
		result = clReleaseDevice(deviceIDs[i]);
		if (result != CL_SUCCESS)
		{
			logs("can't release temp device");
			return 0;
		}
	}
	free(deviceIDs);

	return 1;
}

static int createOutBuffers()
{
	cl_int result;

	backBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, outBufferSize, NULL, &result);
	if (result != CL_SUCCESS)
		return 0;

	frontBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, outBufferSize, NULL, &result);
	if (result != CL_SUCCESS)
		return 0;

	return 1;
}

int clInit(int width, int height, size_t pixelSize)
{
	if (!createContextAndQueue())
		return 0;

	outBufferSize = width*height*pixelSize;
	if(!createOutBuffers())
	{
		logs("can't create out buffers");
		return 0;
	}

	return 1;
}

// Get components of device
cl_mem clGetOutBuffer()
{
	return backBuffer;
}
cl_context clGetContext()
{
	return context;
}
cl_command_queue clGetQueue()
{
	return queue;
}


int clSwapBuffers()
{
	cl_mem temp = backBuffer;
	backBuffer = frontBuffer;
	frontBuffer = backBuffer;

	return  1;
}

int clReadInBuffer(void* buffer)
{
	cl_int result;
	// write to output
	result = clEnqueueReadBuffer(queue, backBuffer, CL_NON_BLOCKING, 0, outBufferSize, buffer, 0, NULL, NULL);
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

	result = clFinish(queue);
	if (result != CL_SUCCESS)
	{
		logs("can't finish queue");
		return 0;
	}

	return 1;
}

void clShutdown()
{
	clReleaseContext(context);
	clReleaseCommandQueue(queue);
	clReleaseMemObject(backBuffer);
	clReleaseMemObject(frontBuffer);
}