#include "IndexBuffer.h"
#include "OpenCL.h"
#include "LogManager.h"
#include <stdlib.h>



// Create buffer
int grCreateIndexBuffer(grIndexBuffer* buffer, int indexCount)
{
	int result;
	struct _grIndexBuffer* bufferStruct = malloc(sizeof(struct _grIndexBuffer));

	// fill new structure
	result = clCreateRWBuffer(&(bufferStruct->clBuffer), indexCount*sizeof(int));
	if (!result)
	{
		logs("Can't get memory for index buffer");
		free(bufferStruct);
		return 0;
	}
	bufferStruct->indexCount = indexCount;
	if (!bufferStruct->bufferPtr)
	{
		logs("can't get gpu pointer to buffer");
		return 0;
	}

	// set new structure to output buffer
	*buffer = bufferStruct;

	return 1;
}

// Release buffer
void grShutdownIndexBuffer(grIndexBuffer buffer)
{
	clReleaseMemObject(buffer->clBuffer);
	free(buffer);
}

// Write data to buffer from ptr
int grWriteIndexBuffer(grIndexBuffer buffer, void* ptr)
{
	int result;

	result = clWriteRWBuffer(buffer->clBuffer, buffer->indexCount * sizeof(int), ptr);
	if (!result)
	{
		logs("Can't write to index buffer");
		return 0;
	}

	return 1;
}

// Read data from buffer to *ptr
int grReadIndexBuffer(grIndexBuffer buffer, void* ptr)
{
	int result;

	result = clReadRWBuffer(buffer->clBuffer, buffer->indexCount*sizeof(int), ptr);
	if (!result)
	{
		logs("Can't read from index buffer");
		return 0;
	}

	return 1;
}

// Get count of indicies in buffer
int grGetIndexCount(grIndexBuffer buffer)
{
	return buffer->indexCount;
}