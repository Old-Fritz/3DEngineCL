#include "BaseModel.h"
#include "LogManager.h"

struct _mdBaseModel {
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;

	m3dVector3 position;
	m3dVector3 rotation;
};

int mdBaseModelInit(mdBaseModel* model, void* vertexData, void* indexData, int vertexCount, int indexCount, size_t vertexSize, grPrimitiveTopology topology)
{
	int result;

	// create vertex buffer with data
	result = grCreateVertexBuffer(&(model->vertexBuffer), vertexCount, vertexSize, topology);
	if(!result)
	{
		logs("can't create vertex buffer for model");
		return 0;
	}
	result = grWriteVertexBuffer(model->vertexBuffer, vertexData);
	if(!result)
	{
		logs("can't write to model vertex buffer");
		return 0;
	}

	// create index buffer with data
	result = grCreateIndexBuffer(&(model->indexBuffer), indexCount);
	if (!result)
	{
		logs("can't create index buffer for model");
		return 0;
	}
	result = grWriteIndexBuffer(model->indexBuffer, indexData);
	if (!result)
	{
		logs("can't write to model vertex buffer");
		return 0;
	}

	// set default 0 position and rotaion
	model->position.x = model->position.y = model->position.z = 0;
	model->rotation.x = model->rotation.y = model->rotation.z = 0;

	return 1;
}

// Set params
void mdSetPosition(mdBaseModel* model, const m3dVector3* position)
{
	m3dVec3Copy(&(model->position), position);
}
void mdSetRotation(mdBaseModel* model, const m3dVector3* rotation)
{
	m3dVec3Copy(&(model->rotation), rotation);
}

// Change params
void mdMove(mdBaseModel* model, float x, float y, float z)
{
	model->position.x += x;
	model->position.y += y;
	model->position.z += z;
}
void mdRotate(mdBaseModel* model, float yaw, float pitch, float roll)
{
	model->rotation.x += pitch;
	model->rotation.y += yaw;
	model->rotation.z += roll;
}

// Get params
m3dVector3* mdGetPosition(mdBaseModel* model, m3dVector3* outVector)
{
	return m3dVec3Copy(outVector, &(model->position));
}

m3dVector3* mdGetRotation(mdBaseModel* model, m3dVector3* outVector)
{
	return m3dVec3Copy(outVector, &(model->rotation));
}

void mdGetBuffers(mdBaseModel* model,  grVertexBuffer* vertexBuffer, grIndexBuffer* indexBuffer)
{
	*vertexBuffer = model->vertexBuffer;
	*indexBuffer = model->indexBuffer;
}

void mdShutdown(mdBaseModel* model)
{
	grShutdownIndexBuffer(model->indexBuffer);
	grShutdownVertexBuffer(model->vertexBuffer);
}