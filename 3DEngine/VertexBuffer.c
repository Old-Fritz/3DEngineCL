#include "VertexBuffer.h"

struct _grVertexBuffer
{
	cl_mem clBuffer;
	int vertexCount;
	size_t vertexSize;
};