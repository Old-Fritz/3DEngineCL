#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <CL/cl.h>

/// Buffer in graphic devices that contains data about vertex indicies

typedef struct _grIndexBuffer
{
	cl_mem clBuffer;
	int indexCount;
} grIndexBuffer;

// Create buffer
int grCreateIndexBuffer(grIndexBuffer** buffer, int indexCount);
// Release buffer
int grShutdownIndexBuffer(grIndexBuffer* buffer);
// Write data to buffer from ptr
int grWriteIndexBuffer(grIndexBuffer* buffer, void* ptr);
// Read data from buffer to *ptr
int grReadIndexxBuffer(grIndexBuffer* buffer, void** ptr);

#endif