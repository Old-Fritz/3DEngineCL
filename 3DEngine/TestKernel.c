#include "TestKernel.h"
#include "OpenCL.h"
#include <stdio.h>
#include <stdlib.h>
#include "LogManager.h"
#include "Settings.h"

static cl_kernel kernel;

static const char* readFile(const char* filename)
{
	FILE* file;
	int size = 0;
	char* source;

	if(fopen_s(&file, filename, "r"))
	{
		logs("can't open kernel file with name:");
		logs(filename);
		return 0;
	}

	while (fgetc(file) != EOF)
		size++;
	//fseek(file, 0L, SEEK_END);
	//size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	source = malloc((size + 1) * sizeof(char));
	if(!source)
		return 0;
	fread(source, sizeof(char), size, file);
	source[size] = 0;

	return source;
}

int clCreateTestKernel(const char* filename)
{
	cl_int result;
	cl_program program;
	cl_context context = clGetContext();
	const char* source;
	source = readFile(filename);
	if (!source)
	{
		logs("can't read source file:");
		logs(filename);
		return 0;
	}

	// create and build program
	program = clCreateProgramWithSource(clGetContext(), 1, &source, NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create program with source:");
		logs(filename);
		return 0;
	}

	result = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		// get device
		cl_device_id* devices = malloc(sizeof(cl_device_id));
		clGetContextInfo(context, CL_CONTEXT_DEVICES, sizeof(cl_device_id), devices, NULL);
		// Determine the size of the log
		size_t log_size;
		clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

		// Allocate memory for the log
		char *log = (char *)malloc(log_size);

		// Get the log
		clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

		// Print the log
		logs("can't build program from sorce:");
		logs(filename);
		logs(log);

		free(log);
		free(devices);
		return 0;
	}

	// create kernel
	kernel = clCreateKernel(program, "testKernel", &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create testKernel");
	}

	// releases
	clReleaseProgram(program);
	free(source);

	return 1;
}

int clExecuteTestKernel(int* x, int* y, int* r)
{
	int ind = 0;
	cl_int result;
	size_t globalWorkSize[2];
	cl_mem outBuffer = clGetOutBuffer();

	// set args x, y, r, outBuffer
	result = clSetKernelArg(kernel, ind++, sizeof(int), x);
	if (result != CL_SUCCESS)
		return 0;
	result = clSetKernelArg(kernel, ind++, sizeof(int), y);
	if (result != CL_SUCCESS)
		return 0;
	result = clSetKernelArg(kernel, ind++, sizeof(int), r);
	if (result != CL_SUCCESS)
		return 0;
	result = clSetKernelArg(kernel, ind, sizeof(cl_mem), &outBuffer);
	if (result != CL_SUCCESS)
		return 0;

	// put work size
	globalWorkSize[0] = setsGetScreenWidth();
	globalWorkSize[1] = setsGetScreenHeight();


	// add in queue and  execute
	result = clEnqueueNDRangeKernel(clGetQueue(), kernel, 2, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		logs("can't add in queue and execute test kernel");
		return 0;
	}

	return 1;
}

void clShutdownTestKernel()
{
	clReleaseKernel(kernel);
}