#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H
#include "BaseModel.h"

struct mdSimpleModelVertex
{
	m3dVector3 position;
};

typedef struct mdSimpleModel
{
	mdBaseModel* model;
	m3dVector4 color;
} mdSimpleModel;

int mdSimpleCreate(mdSimpleModel* model, const char* filename);
void mdSimpleShutdown(mdSimpleModel* model);

#endif