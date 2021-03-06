#ifndef BASE_MODEL_H
#define BASE_MODEL_H
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Math3D.h"

/// Base model that must be part of all other models

typedef struct _mdBaseModel {
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;

	m3dVector3 position;
	m3dVector3 rotation;
} mdBaseModel;

int mdBaseModelInit(mdBaseModel* model, void* vertexData, void* indexData, int vertexCount, int indexCount, size_t vertexSize, grPrimitiveTopology topology);

// Set params
void mdSetPosition(mdBaseModel* model, const m3dVector3* position);
void mdSetRotation(mdBaseModel* model, const m3dVector3* rotation);

// Change params
void mdMove(mdBaseModel* model, float x, float y, float z);
void mdRotate(mdBaseModel* model, float yaw, float pitch, float roll);

// Get params
m3dVector3* mdGetPosition(mdBaseModel* model, m3dVector3* outVector);
m3dVector3* mdGetRotation(mdBaseModel* model, m3dVector3* outVector);
void mdGetBuffers(mdBaseModel* model,  grVertexBuffer* vertexBuffer, grIndexBuffer* indexBuffer);

void mdShutdown(mdBaseModel* model);

#endif