#ifndef LIGHT_SHADER_H
#define LIGHT_SHADER_H

#include "Shader.h"
#include "VectorTransform.h"

/// Simple shader that draw verticies with providied color

typedef struct grLightShaderParams
{
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
	m3dVector4 modelColor;
	m3dVector3 lightPos;
	m3dVector4 lightColor;
	float lightIntensity;
} grLightShaderParams;

int grCreateLightShader(char* vsShader, char* psShader);
void grShutdownLightShader();
int grRenderLightShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grLightShaderParams params);
int grExecuteLightShader(void* outBuffer);
int grFinishLightShader();

#endif