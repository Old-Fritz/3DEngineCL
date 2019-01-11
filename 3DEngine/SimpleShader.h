#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "Shader.h"
/// Simple shader that draw verticies in provided color

typedef struct _grSimpleShaderParams* grSimpleShaderParams;

int grCreateSimpleShader(char* psShader, char* vsShader);
void grShutdownSimpleShader();
int grCreateSimpleShaderParams(grSimpleShaderParams* params, float color);
int grRenderSimpleShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grSimpleShaderParams params);
int grExexuteSimpleShader();

#endif