#ifndef BASE_MODEL_H
#define BASE_MODEL_H
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Math3D.h"

/// Base model that must be part of all other models

typedef struct _mdBaseModel mdBaseModel;

int mdBaseModelInit(mdBaseModel* model, void* vertexData, void* indexData, int vertexCount, int indexCount);

// Set params
int mdSetPosition(mdBaseModel* model, const m3dVector3* position);
int mdSetRotation(mdBaseModel* model, const m3dVector3* rotation);

// Change params
int mdMove(mdBaseModel* model, float x, float y, float z);
int mdRotate(mdBaseModel* model, float yaw, float pitch, float row);

// Get params
m3dVector3* mdGetPosition(mdBaseModel* model, m3dVector3* outVector);
m3dVector3* mdGetRotation(mdBaseModel* model, m3dVector3* outVector);
int mdGetBuffers(grVertexBuffer* vertexBuffer, grIndexBuffer* indexBuffer);

void mdShutdown(mdBaseModel* model);

#endif