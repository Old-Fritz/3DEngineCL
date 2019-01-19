#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <CL/cl.h>

/// Buffer in graphic devices that contains data about verticies

typedef enum grPrimitiveTopology{
	GR_PRIMITIVE_TOPOLOGY_POINT = 1,
	GR_PRIMITIVE_TOPOLOGY_LINE = 2,
	GR_PRIMITIVE_TOPOLOGY_TRIANGLE = 3
} grPrimitiveTopology;

typedef struct _grVertexBuffer* grVertexBuffer;

// Create buffer
int grCreateVertexBuffer(grVertexBuffer* buffer, int vertexCount, size_t vertexSize, grPrimitiveTopology topology);
// Release buffer
void grShutdownVertexBuffer(grVertexBuffer buffer);
// Write data to buffer from ptr
int grWriteVertexBuffer(grVertexBuffer buffer, void* ptr);
// Read data from buffer to *ptr
int grReadVertexBuffer(grVertexBuffer buffer, void* ptr);
// Get count of vertex in buffer
int grGetVertexCount(grVertexBuffer buffer);
// Get primitive of buffer
grPrimitiveTopology grGetVertexPrimitive(grVertexBuffer buffer);

#endif