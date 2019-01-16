#ifndef SS_SM_RENDERER_H
#define SS_SM_RENDERER_H
#include "SimpleModel.h"

/// Class for render simple model with simple shader

struct renderSSSMParams
{
	m3dMatrix worldMatrix;
	m3dMatrix viewMatrix;
	m3dMatrix projectionMatrix;
	m3dVector4 color;
};

int renderSSSM(mdSimpleModel* simpleModel);

#endif