#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <CL/cl.h>


typedef struct _grVertexBuffer
{
	cl_mem clBuffer;
	int vertexCount;
	size_t vertexSize;
} grVertexBuffer;

int grCreateVertexBuffer(grVertexBuffer** buffer, int vertexCount, size_t vertexSize);
int grShutdownVertexBuffer(grVertexBuffer* buffer);
int grWriteVertexBuffer(grVertexBuffer* buffer, void* data);
int grReadVertexBuffer(grVertexBuffer* buffer, void** data);

#endif