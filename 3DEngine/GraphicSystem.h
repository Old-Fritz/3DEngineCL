#ifndef GRAPHIC_SYSTEM_H
#define GRAPHIC_SYSTEM_H
#include "OpenCL.h"
#include "Math3D.h"

/// Control of graphic global settings

int grInitGraphicSystem();
void grShutdownGraphicSystem();

m3dMatrix* grGetWorldMatrix(m3dMatrix* outMatrix);
m3dMatrix* grGetProjectionMatrix(m3dMatrix* outMatrix);

cl_mem grGetDepthBuffer();
cl_mem grGetAccessBuffer();
int grClearBuffers(m3dVector4 color);
int grClearAccessBuffer();
int grClearDepthBuffer();
int grClearBackBuffer(m3dVector4 color);

float grGetNearZ();
float grGetFarZ();

#endif
