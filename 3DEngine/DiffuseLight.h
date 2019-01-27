#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H
#include "BaseModel.h"

typedef struct mdDiffuseLightVertex
{
	m3dVector3 position;
} mdDiffuseLightVertex;

typedef struct mdDiffuseLight
{
	mdBaseModel model;
	m3dVector4 color;
	float intencity;
} mdDiffuseLight;

int mdDiffuseLightCreate(mdDiffuseLight* model);
void mdDiffuseLightShutdown(mdDiffuseLight* model);

#endif