#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "Shader.h"
#include "VectorTransform.h"

/// Simple shader that draw verticies in provided color

typedef struct grSimpleShaderParams
{
	m3dVector4 color;
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
} grSimpleShaderParams;

int grCreateSimpleShader(char* vsShader, char* psShader);
void grShutdownSimpleShader();
int grRenderSimpleShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grSimpleShaderParams params);
int grExecuteSimpleShader(void* outBuffer);
int grFinishSimpleShader();

#endif