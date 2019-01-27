#ifndef COLOR_MODEL_H
#define COLOR_MODEL_H
#include "BaseModel.h"

typedef struct mdColorModelVertex
{
	m3dVector3 position;
	m3dVector4 color;
} mdColorModelVertex;

typedef struct mdColorModel
{
	mdBaseModel model;
} mdColorModel;

int mdColorCreate(mdColorModel* model);
void mdColorShutdown(mdColorModel* model);

#endif