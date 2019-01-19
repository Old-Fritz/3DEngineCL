#include "VertexBuffer.h"
#include "OpenCL.h"
#include "LogManager.h"
#include <stdlib.h>

struct _grVertexBuffer
{
	cl_mem clBuffer;
	int vertexCount;
	size_t vertexSize;
	grPrimitiveTopology topology;
};

// Create buffer
int grCreateVertexBuffer(grVertexBuffer* buffer, int vertexCount, size_t vertexSize, grPrimitiveTopology topology)
{
	int result;
	struct _grVertexBuffer* bufferStruct = malloc(sizeof(struct _grVertexBuffer));

	// fill new structure
	result = clCreateRWBuffer(&(bufferStruct->clBuffer), vertexCount*vertexSize);
	if(!result)
	{
		logs("Can't get memory for vertex buffer");
		free(bufferStruct);
		return 0;
	}
	bufferStruct->vertexCount = vertexCount;
	bufferStruct->vertexSize = vertexSize;
	bufferStruct->topology = topology;

	// set new structure to output buffer
	*buffer = bufferStruct;

	return 1;
}

// Release buffer
void grShutdownVertexBuffer(grVertexBuffer buffer)
{
	clReleaseMemObject(buffer->clBuffer);
	free(buffer);
}

// Write data to buffer from ptr
int grWriteVertexBuffer(grVertexBuffer buffer, void* ptr)
{
	int result;

	result = clWriteRWBuffer(buffer->clBuffer, buffer->vertexCount*buffer->vertexSize, ptr);
	if(!result)
	{
		logs("can't write in Vertex buffer");
		return 0;
	}

	return 1;
}

// Read data from buffer to *ptr
int grReadVertexBuffer(grVertexBuffer buffer, void* ptr)
{
	int result;

	result = clReadRWBuffer(buffer->clBuffer, buffer->vertexCount*buffer->vertexSize, ptr);
	if(!result)
	{
		logs("Can't read from vertex buffer");
		return 0;
	}

	return 1;
}

// Get count of vertex in buffer
int grGetVertexCount(grVertexBuffer buffer)
{
	return buffer->vertexCount;
}

grPrimitiveTopology grGetVertexPrimitive(grVertexBuffer buffer)
{
	return buffer->topology;
}
