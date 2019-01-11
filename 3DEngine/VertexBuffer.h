#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <CL/cl.h>

/// Buffer in graphic devices that contains data about verticies

typedef enum grPrimitiveTopology{
	GR_PRIMITIVE_TOPOLOGY_POINT,
	GR_PRIMITIVE_TOPOLOGY_LINE,
	GR_PRIMITIVE_TOPOLOGY_TRIANGLE
} grPrimitiveTopology;

typedef struct _grVertexBuffer* grVertexBuffer;

// Create buffer
int grCreateVertexBuffer(grVertexBuffer* buffer, int vertexCount, size_t vertexSize, grPrimitiveTopology topology);
// Release buffer
int grShutdownVertexBuffer(grVertexBuffer buffer);
// Write data to buffer from ptr
int grWriteVertexBuffer(grVertexBuffer buffer, void* ptr);
// Read data from buffer to *ptr
int grReadVertexBuffer(grVertexBuffer buffer, void** ptr);

#endif