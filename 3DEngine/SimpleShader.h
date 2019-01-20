#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "Shader.h"
#include "vector3.h"

/// Simple shader that draw verticies in provided color

typedef struct grSimpleShaderParams
{
	m3dVector3 color;
} grSimpleShaderParams;

int grCreateSimpleShader(char* vsShader, char* psShader);
void grShutdownSimpleShader();
int grRenderSimpleShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grSimpleShaderParams params);
int grExexuteSimpleShader();

#endif