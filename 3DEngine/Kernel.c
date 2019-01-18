#include "Kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "LogManager.h"

static int readFile(const char* filename, char** source, int* size)
{
	int result;
	FILE* file;
	*size = 0;

	result = fopen_s(&file, filename, "r");
	if (result)
	{
		logs("can't open kernel file with name:");
		logs(filename);
		return 0;
	}

	while (fgetc(file) != EOF)
		(*size)++;
	//fseek(file, 0L, SEEK_END);
	//size = ftell(file);
	fseek(file, 0L, SEEK_SET);

	*source = malloc((*size + 1) * sizeof(char));
	if (!*source)
		return 0;
	fread(*source, sizeof(char), *size, file);
	(*source)[*size] = 0;

	return 1;
}

static char* createBuildLog(cl_program program)
{
	cl_int result;

	// get device
	cl_device_id* devices = malloc(sizeof(cl_device_id));
	result = clGetContextInfo(clGetContext(), CL_CONTEXT_DEVICES, sizeof(cl_device_id), devices, NULL);
	if (result != CL_SUCCESS)
	{
		free(devices);
		logs("can't get open cl context info to create build log");
		return 0;
	}
	// Determine the size of the log
	size_t log_size;
	result = clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	if (result != CL_SUCCESS)
	{
		free(devices);
		logs("can't get program build info");
		return 0;
	}

	// Allocate memory for the log
	char *log = (char *)malloc(log_size);

	// Get the log
	result = clGetProgramBuildInfo(program, devices[0], CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	if (result != CL_SUCCESS)
	{
		free(devices);
		free(log);
		logs("can't get log from program");
		return 0;
	}

	free(devices);
	return log;
}

static const char* createSource(const char** filenames, int filesCount)
{
	int result;
	int i, j;
	int sourcesSize = 0;
	char** sources = malloc(filesCount * sizeof(char*));
	char* source;

	for (i = 0;i<filesCount;i++)
	{
		int size;
		result = readFile(filenames[i], sources + i, &size);
		if (!result)
		{
			for (j = 0;j<i;j++)
				free(sources[j]);
			return 0;
		}
		sourcesSize += size;
	}

	source = malloc((sourcesSize + 1) * sizeof(char));
	source[0] = 0;

	for (i = 0;i<filesCount;i++)
	{
		result = strcat_s(source, sourcesSize + 1, sources[i]);
		if (result)
		{
			for (j = i;j<filesCount;j++)
				free(sources[i]);
			free(sources);
			free(source);
			return 0;
		}
		free(sources[i]);
	}
	free(sources);

	return source;
}

int clCreateKernelFromFiles(cl_kernel* kernel, const char* kernelName, const char** filenames, int filesCount)
{
	cl_int result;
	cl_program program;
	cl_context context = clGetContext();
	const char* source;
	const char* log;

	source = createSource(filenames, filesCount);
	if (!source)
	{
		logs("can't load source for kernel:");
		logs(kernelName);
		return 0;
	}

	// create and build program
	program = clCreateProgramWithSource(clGetContext(), 1, &source, NULL, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create program with source for kernel:");
		logs(kernelName);
		return 0;
	}

	result = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		// Print the log
		logs("can't build program from sorce for kernel:");
		logs(kernelName);

		log = createBuildLog(program);
		if (!log)
		{
			logs("can't get build log");
			return 0;
		}
		logs(log);

		free(log);

		return 0;
	}

	// create kernel
	*kernel = clCreateKernel(program, kernelName, &result);
	if (result != CL_SUCCESS)
	{
		logs("can't create kernel:");
		logs(kernelName);
		return  0;
	}

	// releases
	clReleaseProgram(program);
	free(source);

	return 1;
}

int clExecuteKernel(cl_kernel kernel, cl_command_queue queue, size_t* globalWorkSize, int globalWorkDimensions, int argsCount, ...)
{
	int ind = 0;
	int i, argSize;
	void* arg;
	cl_int result;
	va_list args;

	va_start(args, argsCount);

	for (i = 0;i<argsCount;i++)
	{
		arg = va_arg(args, void*);
		argSize = va_arg(args, int);

		result = clSetKernelArg(kernel, ind++, argSize, arg);
		if (result != CL_SUCCESS)
		{
			logs("can't set argumet to kernel. Argument number:");
			logsNum(i);
			return 0;
		}
	}

	// add in queue and  execute
	result = clEnqueueNDRangeKernel(queue, kernel, globalWorkDimensions, NULL, globalWorkSize, NULL, 0, NULL, NULL);
	if (result != CL_SUCCESS)
	{
		logs("can't add in queue and execute kernel");
		return 0;
	}

	return 1;
}