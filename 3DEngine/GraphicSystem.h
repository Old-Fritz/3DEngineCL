#ifndef GRAPHIC_SYSTEM_H
#define GRAPHIC_SYSTEM_H
#include "OpenCL.h"
#include "Math3D.h"

/// Control of graphic global settings

int grInitGraphicSystem();

m3dMatrix* grGetWorldMatrix(m3dMatrix* outMatrix);
m3dMatrix* grGetProjectionMatrix(m3dMatrix* outmatrix);

cl_mem grGetDepthBuffer();
int grClearDepthBuffer();
int grClearBackBuffer(m3dVector4 color);

float grGetNearZ();
float grGetFarZ();

#endif
