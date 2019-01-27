#ifndef COLOR_SHADER_H
#define COLOR_SHADER_H

#include "Shader.h"
#include "VectorTransform.h"

/// Simple shader that draw verticies in provided color

typedef struct grColorShaderParams
{
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
} grColorShaderParams;

int grCreateColorShader(char* vsShader, char* psShader);
void grShutdownColorShader();
int grRenderColorShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grColorShaderParams params);
int grExecuteColorShader(void* outBuffer);
int grFinishColorShader();

#endif