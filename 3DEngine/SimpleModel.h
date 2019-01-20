#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H
#include "BaseModel.h"

typedef struct mdSimpleModelVertex
{
	m3dVector3 position;
} mdSimpleModelVertex;

typedef struct mdSimpleModel
{
	mdBaseModel model;
	m3dVector4 color;
} mdSimpleModel;

int mdSimpleCreate(mdSimpleModel* model);
void mdSimpleShutdown(mdSimpleModel* model);

#endif