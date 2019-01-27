#ifndef LIGHT_MODEL_H
#define LIGHT_MODEL_H
#include "BaseModel.h"

typedef struct mdLightModelVertex
{
	m3dVector3 position;
	m3dVector3 normal;
} mdLightModelVertex;

typedef struct mdLightModel
{
	mdBaseModel model;
	m3dVector4 color;
} mdLightModel;

int mdLightCreate(mdLightModel* model, const char* filename);
void mdLightShutdown(mdLightModel* model);

#endif